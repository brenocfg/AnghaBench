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
 int WPS_CONFIG_DISPLAY ; 
 int WPS_CONFIG_ETHERNET ; 
 int WPS_CONFIG_EXT_NFC_TOKEN ; 
 int WPS_CONFIG_INT_NFC_TOKEN ; 
 int WPS_CONFIG_KEYPAD ; 
 int WPS_CONFIG_LABEL ; 
 int WPS_CONFIG_NFC_INTERFACE ; 
 int WPS_CONFIG_P2PS ; 
 int WPS_CONFIG_PHY_DISPLAY ; 
 int WPS_CONFIG_PHY_PUSHBUTTON ; 
 int WPS_CONFIG_PUSHBUTTON ; 
 int WPS_CONFIG_VIRT_DISPLAY ; 
 int WPS_CONFIG_VIRT_PUSHBUTTON ; 
 scalar_t__ os_strstr (char const*,char*) ; 

u16 wps_config_methods_str2bin(const char *str)
{
	u16 methods = 0;

	if (str == NULL || str[0] == '\0') {
		/* Default to enabling methods based on build configuration */
		methods |= WPS_CONFIG_DISPLAY | WPS_CONFIG_KEYPAD;
		methods |= WPS_CONFIG_VIRT_DISPLAY;
#ifdef CONFIG_WPS_NFC
		methods |= WPS_CONFIG_NFC_INTERFACE;
#endif /* CONFIG_WPS_NFC */
#ifdef CONFIG_P2P
		methods |= WPS_CONFIG_P2PS;
#endif /* CONFIG_P2P */
	} else {
		if (os_strstr(str, "ethernet"))
			methods |= WPS_CONFIG_ETHERNET;
		if (os_strstr(str, "label"))
			methods |= WPS_CONFIG_LABEL;
		if (os_strstr(str, "display"))
			methods |= WPS_CONFIG_DISPLAY;
		if (os_strstr(str, "ext_nfc_token"))
			methods |= WPS_CONFIG_EXT_NFC_TOKEN;
		if (os_strstr(str, "int_nfc_token"))
			methods |= WPS_CONFIG_INT_NFC_TOKEN;
		if (os_strstr(str, "nfc_interface"))
			methods |= WPS_CONFIG_NFC_INTERFACE;
		if (os_strstr(str, "push_button"))
			methods |= WPS_CONFIG_PUSHBUTTON;
		if (os_strstr(str, "keypad"))
			methods |= WPS_CONFIG_KEYPAD;
		if (os_strstr(str, "virtual_display"))
			methods |= WPS_CONFIG_VIRT_DISPLAY;
		if (os_strstr(str, "physical_display"))
			methods |= WPS_CONFIG_PHY_DISPLAY;
		if (os_strstr(str, "virtual_push_button"))
			methods |= WPS_CONFIG_VIRT_PUSHBUTTON;
		if (os_strstr(str, "physical_push_button"))
			methods |= WPS_CONFIG_PHY_PUSHBUTTON;
		if (os_strstr(str, "p2ps"))
			methods |= WPS_CONFIG_P2PS;
	}

	return methods;
}