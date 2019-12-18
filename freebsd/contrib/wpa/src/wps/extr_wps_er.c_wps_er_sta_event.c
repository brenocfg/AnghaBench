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
struct wps_event_er_enrollee {int /*<<< orphan*/  serial_number; int /*<<< orphan*/  model_number; int /*<<< orphan*/  model_name; int /*<<< orphan*/  manufacturer; int /*<<< orphan*/  dev_name; int /*<<< orphan*/  pri_dev_type; int /*<<< orphan*/  dev_passwd_id; int /*<<< orphan*/  config_methods; int /*<<< orphan*/  m1_received; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  uuid; } ;
union wps_event_data {struct wps_event_er_enrollee enrollee; } ;
struct wps_er_sta {int /*<<< orphan*/  serial_number; int /*<<< orphan*/  model_number; int /*<<< orphan*/  model_name; int /*<<< orphan*/  manufacturer; int /*<<< orphan*/  dev_name; int /*<<< orphan*/  pri_dev_type; int /*<<< orphan*/  dev_passwd_id; int /*<<< orphan*/  config_methods; int /*<<< orphan*/  m1_received; int /*<<< orphan*/  addr; int /*<<< orphan*/  uuid; } ;
struct wps_context {int /*<<< orphan*/  cb_ctx; int /*<<< orphan*/  (* event_cb ) (int /*<<< orphan*/ ,int,union wps_event_data*) ;} ;
typedef  enum wps_event { ____Placeholder_wps_event } wps_event ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  os_memset (union wps_event_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,union wps_event_data*) ; 

__attribute__((used)) static void wps_er_sta_event(struct wps_context *wps, struct wps_er_sta *sta,
			     enum wps_event event)
{
	union wps_event_data data;
	struct wps_event_er_enrollee *ev = &data.enrollee;

	if (wps->event_cb == NULL)
		return;

	os_memset(&data, 0, sizeof(data));
	ev->uuid = sta->uuid;
	ev->mac_addr = sta->addr;
	ev->m1_received = sta->m1_received;
	ev->config_methods = sta->config_methods;
	ev->dev_passwd_id = sta->dev_passwd_id;
	ev->pri_dev_type = sta->pri_dev_type;
	ev->dev_name = sta->dev_name;
	ev->manufacturer = sta->manufacturer;
	ev->model_name = sta->model_name;
	ev->model_number = sta->model_number;
	ev->serial_number = sta->serial_number;
	wps->event_cb(wps->cb_ctx, event, &data);
}