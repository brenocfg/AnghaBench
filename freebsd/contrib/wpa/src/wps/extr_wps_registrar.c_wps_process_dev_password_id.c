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
struct wps_data {int /*<<< orphan*/  dev_pw_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WPA_GET_BE16 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int wps_process_dev_password_id(struct wps_data *wps, const u8 *pw_id)
{
	if (pw_id == NULL) {
		wpa_printf(MSG_DEBUG, "WPS: No Device Password ID received");
		return -1;
	}

	wps->dev_pw_id = WPA_GET_BE16(pw_id);
	wpa_printf(MSG_DEBUG, "WPS: Device Password ID %d", wps->dev_pw_id);

	return 0;
}