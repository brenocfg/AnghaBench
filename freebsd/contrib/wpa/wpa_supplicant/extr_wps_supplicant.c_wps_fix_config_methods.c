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
 int WPS_CONFIG_PHY_DISPLAY ; 
 int WPS_CONFIG_PHY_PUSHBUTTON ; 
 int WPS_CONFIG_PUSHBUTTON ; 
 int WPS_CONFIG_VIRT_DISPLAY ; 
 int WPS_CONFIG_VIRT_PUSHBUTTON ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static u16 wps_fix_config_methods(u16 config_methods)
{
	if ((config_methods &
	     (WPS_CONFIG_DISPLAY | WPS_CONFIG_VIRT_DISPLAY |
	      WPS_CONFIG_PHY_DISPLAY)) == WPS_CONFIG_DISPLAY) {
		wpa_printf(MSG_INFO, "WPS: Converting display to "
			   "virtual_display for WPS 2.0 compliance");
		config_methods |= WPS_CONFIG_VIRT_DISPLAY;
	}
	if ((config_methods &
	     (WPS_CONFIG_PUSHBUTTON | WPS_CONFIG_VIRT_PUSHBUTTON |
	      WPS_CONFIG_PHY_PUSHBUTTON)) == WPS_CONFIG_PUSHBUTTON) {
		wpa_printf(MSG_INFO, "WPS: Converting push_button to "
			   "virtual_push_button for WPS 2.0 compliance");
		config_methods |= WPS_CONFIG_VIRT_PUSHBUTTON;
	}

	return config_methods;
}