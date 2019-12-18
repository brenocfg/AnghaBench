#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int enrollee; int part; int /*<<< orphan*/  peer_macaddr; } ;
union wps_event_data {TYPE_1__ pwd_auth_fail; } ;
typedef  int /*<<< orphan*/  u8 ;
struct wps_context {int /*<<< orphan*/  cb_ctx; int /*<<< orphan*/  (* event_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union wps_event_data*) ;} ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  WPS_EV_PWD_AUTH_FAIL ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memset (union wps_event_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union wps_event_data*) ; 

void wps_pwd_auth_fail_event(struct wps_context *wps, int enrollee, int part,
			     const u8 *mac_addr)
{
	union wps_event_data data;

	if (wps->event_cb == NULL)
		return;

	os_memset(&data, 0, sizeof(data));
	data.pwd_auth_fail.enrollee = enrollee;
	data.pwd_auth_fail.part = part;
	os_memcpy(data.pwd_auth_fail.peer_macaddr, mac_addr, ETH_ALEN);
	wps->event_cb(wps->cb_ctx, WPS_EV_PWD_AUTH_FAIL, &data);
}