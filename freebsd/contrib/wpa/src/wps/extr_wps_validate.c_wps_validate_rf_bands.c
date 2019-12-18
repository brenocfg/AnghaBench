#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int const WPS_RF_24GHZ ; 
 int const WPS_RF_50GHZ ; 
 int const WPS_RF_60GHZ ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int wps_validate_rf_bands(const u8 *rf_bands, int mandatory)
{
	if (rf_bands == NULL) {
		if (mandatory) {
			wpa_printf(MSG_INFO, "WPS-STRICT: RF Bands "
				   "attribute missing");
			return -1;
		}
		return 0;
	}
	if (*rf_bands != WPS_RF_24GHZ && *rf_bands != WPS_RF_50GHZ &&
	    *rf_bands != WPS_RF_60GHZ &&
	    *rf_bands != (WPS_RF_24GHZ | WPS_RF_50GHZ | WPS_RF_60GHZ) &&
	    *rf_bands != (WPS_RF_24GHZ | WPS_RF_50GHZ)) {
		wpa_printf(MSG_INFO, "WPS-STRICT: Invalid Rf Bands "
			   "attribute value 0x%x", *rf_bands);
		return -1;
	}
	return 0;
}