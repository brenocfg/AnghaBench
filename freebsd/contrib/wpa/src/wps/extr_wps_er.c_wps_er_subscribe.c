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
struct wps_er_ap {int /*<<< orphan*/ * http; int /*<<< orphan*/  id; TYPE_1__* er; int /*<<< orphan*/ * event_sub_url; } ;
struct wpabuf {int dummy; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  event_id; int /*<<< orphan*/  http_port; int /*<<< orphan*/  ip_addr_text; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/ * http_client_addr (struct sockaddr_in*,struct wpabuf*,int,int /*<<< orphan*/ ,struct wps_er_ap*) ; 
 char* http_client_url_parse (int /*<<< orphan*/ *,struct sockaddr_in*,char**) ; 
 int /*<<< orphan*/  inet_ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 scalar_t__ os_strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct wpabuf* wpabuf_alloc (scalar_t__) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_printf (struct wpabuf*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wps_er_http_subscribe_cb ; 

__attribute__((used)) static void wps_er_subscribe(struct wps_er_ap *ap)
{
	struct wpabuf *req;
	struct sockaddr_in dst;
	char *url, *path;

	if (ap->event_sub_url == NULL) {
		wpa_printf(MSG_DEBUG, "WPS ER: No eventSubURL - cannot "
			   "subscribe");
		return;
	}
	if (ap->http) {
		wpa_printf(MSG_DEBUG, "WPS ER: Pending HTTP request - cannot "
			   "send subscribe request");
		return;
	}

	url = http_client_url_parse(ap->event_sub_url, &dst, &path);
	if (url == NULL) {
		wpa_printf(MSG_DEBUG, "WPS ER: Failed to parse eventSubURL");
		return;
	}

	req = wpabuf_alloc(os_strlen(ap->event_sub_url) + 1000);
	if (req == NULL) {
		os_free(url);
		return;
	}
	wpabuf_printf(req,
		      "SUBSCRIBE %s HTTP/1.1\r\n"
		      "HOST: %s:%d\r\n"
		      "CALLBACK: <http://%s:%d/event/%u/%u>\r\n"
		      "NT: upnp:event\r\n"
		      "TIMEOUT: Second-%d\r\n"
		      "\r\n",
		      path, inet_ntoa(dst.sin_addr), ntohs(dst.sin_port),
		      ap->er->ip_addr_text, ap->er->http_port,
		      ap->er->event_id, ap->id, 1800);
	os_free(url);
	wpa_hexdump_ascii(MSG_MSGDUMP, "WPS ER: Subscription request",
			  wpabuf_head(req), wpabuf_len(req));

	ap->http = http_client_addr(&dst, req, 1000, wps_er_http_subscribe_cb,
				    ap);
	if (ap->http == NULL)
		wpabuf_free(req);
}