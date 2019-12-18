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
struct wps_device_data {int /*<<< orphan*/ * device_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/ * dup_binstr (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int wps_process_dev_name(struct wps_device_data *dev, const u8 *str,
				size_t str_len)
{
	if (str == NULL) {
		wpa_printf(MSG_DEBUG, "WPS: No Device Name received");
		return -1;
	}

	wpa_hexdump_ascii(MSG_DEBUG, "WPS: Device Name", str, str_len);

	os_free(dev->device_name);
	dev->device_name = dup_binstr(str, str_len);
	if (dev->device_name == NULL)
		return -1;

	return 0;
}