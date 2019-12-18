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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int WPA_GET_BE16 (int /*<<< orphan*/  const*) ; 
 int WPS_CONFIG_PUSHBUTTON ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ wps_validate_config_methods (int /*<<< orphan*/  const*,int,int) ; 

__attribute__((used)) static int wps_validate_ap_config_methods(const u8 *config_methods, int wps2,
					  int mandatory)
{
	u16 val;

	if (wps_validate_config_methods(config_methods, wps2, mandatory) < 0)
		return -1;
	if (config_methods == NULL)
		return 0;
	val = WPA_GET_BE16(config_methods);
	if (val & WPS_CONFIG_PUSHBUTTON) {
		wpa_printf(MSG_INFO, "WPS-STRICT: Invalid Configuration "
			   "Methods attribute value 0x%04x in AP info "
			   "(PushButton not allowed for registering new ER)",
			   val);
		return -1;
	}
	return 0;
}