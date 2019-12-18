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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ const WPS_STATE_CONFIGURED ; 
 scalar_t__ const WPS_STATE_NOT_CONFIGURED ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int wps_validate_wps_state(const u8 *wps_state, int mandatory)
{
	if (wps_state == NULL) {
		if (mandatory) {
			wpa_printf(MSG_INFO, "WPS-STRICT: Wi-Fi Protected "
				   "Setup State attribute missing");
			return -1;
		}
		return 0;
	}
	if (*wps_state != WPS_STATE_NOT_CONFIGURED &&
	    *wps_state != WPS_STATE_CONFIGURED) {
		wpa_printf(MSG_INFO, "WPS-STRICT: Invalid Wi-Fi Protected "
			   "Setup State attribute value 0x%x", *wps_state);
		return -1;
	}
	return 0;
}