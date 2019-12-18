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
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,scalar_t__ const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int wps_validate_dev_name(const u8 *dev_name, size_t len,
				 int mandatory)
{
	if (dev_name == NULL) {
		if (mandatory) {
			wpa_printf(MSG_INFO, "WPS-STRICT: Device Name "
				   "attribute missing");
			return -1;
		}
		return 0;
	}
	if (len > 0 && dev_name[len - 1] == 0) {
		wpa_hexdump_ascii(MSG_INFO, "WPS-STRICT: Invalid Device Name "
			   "attribute value", dev_name, len);
		return -1;
	}
	return 0;
}