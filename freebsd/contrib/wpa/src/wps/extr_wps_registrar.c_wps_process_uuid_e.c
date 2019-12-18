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
struct wps_data {int /*<<< orphan*/  uuid_e; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WPS_UUID_LEN ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int wps_process_uuid_e(struct wps_data *wps, const u8 *uuid_e)
{
	if (uuid_e == NULL) {
		wpa_printf(MSG_DEBUG, "WPS: No UUID-E received");
		return -1;
	}

	os_memcpy(wps->uuid_e, uuid_e, WPS_UUID_LEN);
	wpa_hexdump(MSG_DEBUG, "WPS: UUID-E", wps->uuid_e, WPS_UUID_LEN);

	return 0;
}