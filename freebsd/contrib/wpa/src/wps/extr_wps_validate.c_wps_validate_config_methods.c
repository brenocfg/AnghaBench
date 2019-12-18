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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  WPA_GET_BE16 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  valid_config_methods (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int wps_validate_config_methods(const u8 *config_methods, int wps2,
				       int mandatory)
{
	u16 val;

	if (config_methods == NULL) {
		if (mandatory) {
			wpa_printf(MSG_INFO, "WPS-STRICT: Configuration "
				   "Methods attribute missing");
			return -1;
		}
		return 0;
	}

	val = WPA_GET_BE16(config_methods);
	if (!valid_config_methods(val, wps2)) {
		wpa_printf(MSG_INFO, "WPS-STRICT: Invalid Configuration "
			   "Methods attribute value 0x%04x", val);
		return -1;
	}
	return 0;
}