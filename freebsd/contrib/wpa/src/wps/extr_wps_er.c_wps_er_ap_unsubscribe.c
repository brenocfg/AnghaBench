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
struct wps_er_ap {int /*<<< orphan*/  er; int /*<<< orphan*/ * http; int /*<<< orphan*/  sid; int /*<<< orphan*/ * event_sub_url; } ;
struct wps_er {int dummy; } ;
struct wpabuf {int dummy; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
typedef  int /*<<< orphan*/  sid ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/ * http_client_addr (struct sockaddr_in*,struct wpabuf*,int,int /*<<< orphan*/ ,struct wps_er_ap*) ; 
 char* http_client_url_parse (int /*<<< orphan*/ *,struct sockaddr_in*,char**) ; 
 int /*<<< orphan*/  inet_ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 scalar_t__ os_strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uuid_bin2str (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct wpabuf* wpabuf_alloc (scalar_t__) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_printf (struct wpabuf*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wps_er_ap_unsubscribed (int /*<<< orphan*/ ,struct wps_er_ap*) ; 
 int /*<<< orphan*/  wps_er_http_unsubscribe_cb ; 

__attribute__((used)) static void wps_er_ap_unsubscribe(struct wps_er *er, struct wps_er_ap *ap)
{
	struct wpabuf *req;
	struct sockaddr_in dst;
	char *url, *path;
	char sid[100];

	if (ap->event_sub_url == NULL) {
		wpa_printf(MSG_DEBUG, "WPS ER: No eventSubURL - cannot "
			   "subscribe");
		goto fail;
	}
	if (ap->http) {
		wpa_printf(MSG_DEBUG, "WPS ER: Pending HTTP request - cannot "
			   "send subscribe request");
		goto fail;
	}

	url = http_client_url_parse(ap->event_sub_url, &dst, &path);
	if (url == NULL) {
		wpa_printf(MSG_DEBUG, "WPS ER: Failed to parse eventSubURL");
		goto fail;
	}

	req = wpabuf_alloc(os_strlen(ap->event_sub_url) + 1000);
	if (req == NULL) {
		os_free(url);
		goto fail;
	}
	uuid_bin2str(ap->sid, sid, sizeof(sid));
	wpabuf_printf(req,
		      "UNSUBSCRIBE %s HTTP/1.1\r\n"
		      "HOST: %s:%d\r\n"
		      "SID: uuid:%s\r\n"
		      "\r\n",
		      path, inet_ntoa(dst.sin_addr), ntohs(dst.sin_port), sid);
	os_free(url);
	wpa_hexdump_ascii(MSG_MSGDUMP, "WPS ER: Unsubscription request",
			  wpabuf_head(req), wpabuf_len(req));

	ap->http = http_client_addr(&dst, req, 1000,
				    wps_er_http_unsubscribe_cb, ap);
	if (ap->http == NULL) {
		wpabuf_free(req);
		goto fail;
	}
	return;

fail:
	/*
	 * Need to get rid of the AP entry even when we fail to unsubscribe
	 * cleanly.
	 */
	wps_er_ap_unsubscribed(ap->er, ap);
}