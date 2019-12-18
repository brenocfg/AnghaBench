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
struct wps_er_ap {int /*<<< orphan*/ * http; } ;
struct wpabuf {int dummy; } ;
struct http_client {int dummy; } ;
typedef  enum http_client_event { ____Placeholder_http_client_event } http_client_event ;

/* Variables and functions */
#define  HTTP_CLIENT_FAILED 131 
#define  HTTP_CLIENT_INVALID_REPLY 130 
#define  HTTP_CLIENT_OK 129 
#define  HTTP_CLIENT_TIMEOUT 128 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  http_client_free (int /*<<< orphan*/ *) ; 
 struct wpabuf* http_client_get_body (struct http_client*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wps_er_get_device_info (struct wps_er_ap*) ; 
 int /*<<< orphan*/  wps_er_parse_device_description (struct wps_er_ap*,struct wpabuf*) ; 

__attribute__((used)) static void wps_er_http_dev_desc_cb(void *ctx, struct http_client *c,
				    enum http_client_event event)
{
	struct wps_er_ap *ap = ctx;
	struct wpabuf *reply;
	int ok = 0;

	switch (event) {
	case HTTP_CLIENT_OK:
		reply = http_client_get_body(c);
		if (reply == NULL)
			break;
		wps_er_parse_device_description(ap, reply);
		ok = 1;
		break;
	case HTTP_CLIENT_FAILED:
	case HTTP_CLIENT_INVALID_REPLY:
	case HTTP_CLIENT_TIMEOUT:
		wpa_printf(MSG_DEBUG, "WPS ER: Failed to fetch device info");
		break;
	}
	http_client_free(ap->http);
	ap->http = NULL;
	if (ok)
		wps_er_get_device_info(ap);
}