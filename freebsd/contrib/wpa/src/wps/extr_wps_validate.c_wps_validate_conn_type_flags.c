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
 int const WPS_CONN_ESS ; 
 int const WPS_CONN_IBSS ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int wps_validate_conn_type_flags(const u8 *flags, int mandatory)
{
	if (flags == NULL) {
		if (mandatory) {
			wpa_printf(MSG_INFO, "WPS-STRICT: Connection Type "
				   "Flags attribute missing");
			return -1;
		}
		return 0;
	}
	if ((*flags & ~(WPS_CONN_ESS | WPS_CONN_IBSS)) ||
	    !(*flags & WPS_CONN_ESS)) {
		wpa_printf(MSG_INFO, "WPS-STRICT: Invalid Connection Type "
			   "Flags attribute value 0x%02x", *flags);
		return -1;
	}
	return 0;
}