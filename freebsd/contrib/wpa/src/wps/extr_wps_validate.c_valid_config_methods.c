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
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int WPS_CONFIG_DISPLAY ; 
 int WPS_CONFIG_PUSHBUTTON ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int valid_config_methods(u16 val, int wps2)
{
	if (wps2) {
		if ((val & 0x6000) && !(val & WPS_CONFIG_DISPLAY)) {
			wpa_printf(MSG_INFO, "WPS-STRICT: Physical/Virtual "
				   "Display flag without old Display flag "
				   "set");
			return 0;
		}
		if (!(val & 0x6000) && (val & WPS_CONFIG_DISPLAY)) {
			wpa_printf(MSG_INFO, "WPS-STRICT: Display flag "
				   "without Physical/Virtual Display flag");
			return 0;
		}
		if ((val & 0x0600) && !(val & WPS_CONFIG_PUSHBUTTON)) {
			wpa_printf(MSG_INFO, "WPS-STRICT: Physical/Virtual "
				   "PushButton flag without old PushButton "
				   "flag set");
			return 0;
		}
		if (!(val & 0x0600) && (val & WPS_CONFIG_PUSHBUTTON)) {
			wpa_printf(MSG_INFO, "WPS-STRICT: PushButton flag "
				   "without Physical/Virtual PushButton flag");
			return 0;
		}
	}

	return 1;
}