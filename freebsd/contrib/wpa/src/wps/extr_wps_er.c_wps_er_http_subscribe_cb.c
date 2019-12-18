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
struct wps_er_ap {int subscribed; int /*<<< orphan*/ * http; TYPE_1__* er; } ;
struct http_client {int dummy; } ;
typedef  enum http_client_event { ____Placeholder_http_client_event } http_client_event ;
struct TYPE_2__ {int /*<<< orphan*/  wps; } ;

/* Variables and functions */
#define  HTTP_CLIENT_FAILED 131 
#define  HTTP_CLIENT_INVALID_REPLY 130 
#define  HTTP_CLIENT_OK 129 
#define  HTTP_CLIENT_TIMEOUT 128 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WPS_EV_ER_AP_ADD ; 
 int /*<<< orphan*/  http_client_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  http_client_get_hdr_line (struct http_client*,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wps_er_ap_event (int /*<<< orphan*/ ,struct wps_er_ap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wps_er_ap_use_cached_settings (TYPE_1__*,struct wps_er_ap*) ; 
 int /*<<< orphan*/  wps_er_get_sid (struct wps_er_ap*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wps_er_http_subscribe_cb(void *ctx, struct http_client *c,
				     enum http_client_event event)
{
	struct wps_er_ap *ap = ctx;

	switch (event) {
	case HTTP_CLIENT_OK:
		wpa_printf(MSG_DEBUG, "WPS ER: Subscribed to events");
		ap->subscribed = 1;
		wps_er_get_sid(ap, http_client_get_hdr_line(c, "SID"));
		wps_er_ap_use_cached_settings(ap->er, ap);
		wps_er_ap_event(ap->er->wps, ap, WPS_EV_ER_AP_ADD);
		break;
	case HTTP_CLIENT_FAILED:
	case HTTP_CLIENT_INVALID_REPLY:
	case HTTP_CLIENT_TIMEOUT:
		wpa_printf(MSG_DEBUG, "WPS ER: Failed to subscribe to events");
		break;
	}
	http_client_free(ap->http);
	ap->http = NULL;
}