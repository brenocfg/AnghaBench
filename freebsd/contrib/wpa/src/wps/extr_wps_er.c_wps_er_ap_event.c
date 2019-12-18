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
struct wps_event_er_ap {int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  wps_state; int /*<<< orphan*/  pri_dev_type; int /*<<< orphan*/  upc; int /*<<< orphan*/  serial_number; int /*<<< orphan*/  model_url; int /*<<< orphan*/  model_number; int /*<<< orphan*/  model_name; int /*<<< orphan*/  model_description; int /*<<< orphan*/  manufacturer_url; int /*<<< orphan*/  manufacturer; int /*<<< orphan*/  friendly_name; int /*<<< orphan*/  uuid; } ;
union wps_event_data {struct wps_event_er_ap ap; } ;
struct wps_er_ap {int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  wps_state; int /*<<< orphan*/  pri_dev_type; int /*<<< orphan*/  upc; int /*<<< orphan*/  serial_number; int /*<<< orphan*/  model_url; int /*<<< orphan*/  model_number; int /*<<< orphan*/  model_name; int /*<<< orphan*/  model_description; int /*<<< orphan*/  manufacturer_url; int /*<<< orphan*/  manufacturer; int /*<<< orphan*/  friendly_name; int /*<<< orphan*/  uuid; } ;
struct wps_context {int /*<<< orphan*/  cb_ctx; int /*<<< orphan*/  (* event_cb ) (int /*<<< orphan*/ ,int,union wps_event_data*) ;} ;
typedef  enum wps_event { ____Placeholder_wps_event } wps_event ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  os_memset (union wps_event_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,union wps_event_data*) ; 

__attribute__((used)) static void wps_er_ap_event(struct wps_context *wps, struct wps_er_ap *ap,
			    enum wps_event event)
{
	union wps_event_data data;
	struct wps_event_er_ap *evap = &data.ap;

	if (wps->event_cb == NULL)
		return;

	os_memset(&data, 0, sizeof(data));
	evap->uuid = ap->uuid;
	evap->friendly_name = ap->friendly_name;
	evap->manufacturer = ap->manufacturer;
	evap->manufacturer_url = ap->manufacturer_url;
	evap->model_description = ap->model_description;
	evap->model_name = ap->model_name;
	evap->model_number = ap->model_number;
	evap->model_url = ap->model_url;
	evap->serial_number = ap->serial_number;
	evap->upc = ap->upc;
	evap->pri_dev_type = ap->pri_dev_type;
	evap->wps_state = ap->wps_state;
	evap->mac_addr = ap->mac_addr;
	wps->event_cb(wps->cb_ctx, event, &data);
}