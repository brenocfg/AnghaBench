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
 int /*<<< orphan*/  os_free (char*) ; 
 int /*<<< orphan*/  os_memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* os_zalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wps_er_ap_learn (struct wps_er_ap*,char*) ; 

__attribute__((used)) static void wps_er_http_get_dev_info_cb(void *ctx, struct http_client *c,
					enum http_client_event event)
{
	struct wps_er_ap *ap = ctx;
	struct wpabuf *reply;
	char *dev_info = NULL;

	switch (event) {
	case HTTP_CLIENT_OK:
		wpa_printf(MSG_DEBUG, "WPS ER: GetDeviceInfo OK");
		reply = http_client_get_body(c);
		if (reply == NULL)
			break;
		dev_info = os_zalloc(wpabuf_len(reply) + 1);
		if (dev_info == NULL)
			break;
		os_memcpy(dev_info, wpabuf_head(reply), wpabuf_len(reply));
		break;
	case HTTP_CLIENT_FAILED:
	case HTTP_CLIENT_INVALID_REPLY:
	case HTTP_CLIENT_TIMEOUT:
		wpa_printf(MSG_DEBUG, "WPS ER: GetDeviceInfo failed");
		break;
	}
	http_client_free(ap->http);
	ap->http = NULL;

	if (dev_info) {
		wps_er_ap_learn(ap, dev_info);
		os_free(dev_info);
	}
}