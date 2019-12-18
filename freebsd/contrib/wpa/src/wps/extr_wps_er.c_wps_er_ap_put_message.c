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
struct wps_er_ap {int /*<<< orphan*/ * wps; int /*<<< orphan*/ * http; int /*<<< orphan*/ * control_url; } ;
struct wpabuf {int dummy; } ;
struct sockaddr_in {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/ * http_client_addr (struct sockaddr_in*,struct wpabuf*,int,int /*<<< orphan*/ ,struct wps_er_ap*) ; 
 char* http_client_url_parse (int /*<<< orphan*/ *,struct sockaddr_in*,char**) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wps_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wps_er_http_put_message_cb ; 
 int /*<<< orphan*/  wps_er_soap_end (struct wpabuf*,char*,char*,char*) ; 
 struct wpabuf* wps_er_soap_hdr (struct wpabuf const*,char*,char*,char*,struct sockaddr_in*,char**,char**) ; 

__attribute__((used)) static void wps_er_ap_put_message(struct wps_er_ap *ap,
				  const struct wpabuf *msg)
{
	struct wpabuf *buf;
	char *len_ptr, *body_ptr;
	struct sockaddr_in dst;
	char *url, *path;

	if (ap->http) {
		wpa_printf(MSG_DEBUG, "WPS ER: Pending HTTP operation ongoing "
			   "with the AP - cannot continue learn");
		return;
	}

	if (ap->control_url == NULL) {
		wpa_printf(MSG_DEBUG, "WPS ER: No controlURL for AP");
		return;
	}

	url = http_client_url_parse(ap->control_url, &dst, &path);
	if (url == NULL) {
		wpa_printf(MSG_DEBUG, "WPS ER: Failed to parse controlURL");
		goto fail;
	}

	buf = wps_er_soap_hdr(msg, "PutMessage", "NewInMessage", path, &dst,
			      &len_ptr, &body_ptr);
	os_free(url);
	if (buf == NULL)
		goto fail;

	wps_er_soap_end(buf, "PutMessage", len_ptr, body_ptr);

	ap->http = http_client_addr(&dst, buf, 10000,
				    wps_er_http_put_message_cb, ap);
	if (ap->http == NULL) {
		wpabuf_free(buf);
		goto fail;
	}
	return;

fail:
	if (ap->wps) {
		wps_deinit(ap->wps);
		ap->wps = NULL;
	}
}