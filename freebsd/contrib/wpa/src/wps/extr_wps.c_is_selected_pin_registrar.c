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
struct wps_parse_attr {scalar_t__* selected_registrar; int /*<<< orphan*/ * sel_reg_config_methods; int /*<<< orphan*/ * dev_password_id; } ;

/* Variables and functions */
 int DEV_PW_PUSHBUTTON ; 
 int WPA_GET_BE16 (int /*<<< orphan*/ *) ; 
 int WPS_CONFIG_DISPLAY ; 
 int WPS_CONFIG_KEYPAD ; 
 int WPS_CONFIG_LABEL ; 

__attribute__((used)) static int is_selected_pin_registrar(struct wps_parse_attr *attr)
{
	/*
	 * In theory, this could also verify that attr.sel_reg_config_methods
	 * includes WPS_CONFIG_LABEL, WPS_CONFIG_DISPLAY, or WPS_CONFIG_KEYPAD,
	 * but some deployed AP implementations do not set Selected Registrar
	 * Config Methods attribute properly, so it is safer to just use
	 * Device Password ID here.
	 */

	if (!attr->selected_registrar || *attr->selected_registrar == 0)
		return 0;

	if (attr->dev_password_id != NULL &&
	    WPA_GET_BE16(attr->dev_password_id) == DEV_PW_PUSHBUTTON)
		return 0;

#ifdef CONFIG_WPS_STRICT
	if (!attr->sel_reg_config_methods ||
	    !(WPA_GET_BE16(attr->sel_reg_config_methods) &
	      (WPS_CONFIG_LABEL | WPS_CONFIG_DISPLAY | WPS_CONFIG_KEYPAD)))
		return 0;
#endif /* CONFIG_WPS_STRICT */

	return 1;
}