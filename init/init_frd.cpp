/*
   Copyright (c) 2014, The Linux Foundation. All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.
   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <cstdlib>
#include <fstream>
#include <string>

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"

#include "init_hi3650.h"

void init_target_properties()
{
    std::ifstream fin;
    std::string buf;

    std::string platform = property_get("ro.board.platform");
    if (platform != ANDROID_TARGET) {
	return;
    }

    fin.open("/sys/firmware/devicetree/base/hisi,product_name");
    while (getline(fin, buf))
        if ((buf.find("FRD-L02") != std::string::npos) || (buf.find("FRD-L04") != std::string::npos) || (buf.find("FRD-L09") != std::string::npos) || (buf.find("FRD-L14") != std::string::npos) || (buf.find("FRD-L19") != std::string::npos))
            break;
    fin.close();

    if (buf.find("FRD-L02") != std::string::npos) {
        property_set("ro.product.model", "FRD-L02");
    }
    else if (buf.find("FRD-L04") != std::string::npos) {
        property_set("ro.product.model", "FRD-L04");
        property_set("ro.build.description", "FRD-L04-user 7.0 HUAWEIFRD-L04 C567B380 release-keys");
        property_set("ro.build.fingerprint", "HONOR/FRD-L04/HWFRD:7.0/HUAWEIFRD-L04/C567B380:user/release-keys");	
    }
    else if (buf.find("FRD-L09") != std::string::npos) {
        property_set("ro.product.model", "FRD-L09");
        property_set("ro.build.description", "FRD-L09-user 7.0 HUAWEIFRD-L09 C432B380 release-keys");
        property_set("ro.build.fingerprint", "HONOR/FRD-L09/HWFRD:7.0/HUAWEIFRD-L09/C432B380:user/release-keys");
    }
    else if (buf.find("FRD-L14") != std::string::npos) {
        property_set("ro.product.model", "FRD-L14");
    }
    else if (buf.find("FRD-L19") != std::string::npos) {
        property_set("ro.product.model", "FRD-L19");
    }
    else {
	property_set("ro.product.model", "UNKNOWN");
    }
}
