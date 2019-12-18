#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ uuid; int /*<<< orphan*/  state; } ;
union wps_event_data {TYPE_1__ set_sel_reg; } ;
struct wps_er_ap {TYPE_3__* er; int /*<<< orphan*/ * http; scalar_t__ uuid; } ;
struct http_client {int dummy; } ;
typedef  enum http_client_event { ____Placeholder_http_client_event } http_client_event ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_6__ {TYPE_2__* wps; } ;
struct TYPE_5__ {int /*<<< orphan*/  cb_ctx; int /*<<< orphan*/  (* event_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union wps_event_data*) ;} ;

/* Variables and functions */
#define  HTTP_CLIENT_FAILED 131 
#define  HTTP_CLIENT_INVALID_REPLY 130 
#define  HTTP_CLIENT_OK 129 
#define  HTTP_CLIENT_TIMEOUT 128 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WPS_ER_SET_SEL_REG_DONE ; 
 int /*<<< orphan*/  WPS_ER_SET_SEL_REG_FAILED ; 
 int /*<<< orphan*/  WPS_EV_ER_SET_SELECTED_REGISTRAR ; 
 int /*<<< orphan*/  http_client_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memset (union wps_event_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union wps_event_data*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void wps_er_http_set_sel_reg_cb(void *ctx, struct http_client *c,
				       enum http_client_event event)
{
	struct wps_er_ap *ap = ctx;
	union wps_event_data data;

	os_memset(&data, 0, sizeof(data));

	switch (event) {
	case HTTP_CLIENT_OK:
		wpa_printf(MSG_DEBUG, "WPS ER: SetSelectedRegistrar OK");
		data.set_sel_reg.state = WPS_ER_SET_SEL_REG_DONE;
		data.set_sel_reg.uuid = ap->uuid;
		break;
	case HTTP_CLIENT_FAILED:
	case HTTP_CLIENT_INVALID_REPLY:
	case HTTP_CLIENT_TIMEOUT:
		wpa_printf(MSG_DEBUG, "WPS ER: SetSelectedRegistrar failed");
		data.set_sel_reg.state = WPS_ER_SET_SEL_REG_FAILED;
		data.set_sel_reg.uuid = ap->uuid;
		break;
	}
	http_client_free(ap->http);
	ap->http = NULL;

	if (data.set_sel_reg.uuid)
		ap->er->wps->event_cb(ap->er->wps->cb_ctx,
				      WPS_EV_ER_SET_SELECTED_REGISTRAR, &data);
}