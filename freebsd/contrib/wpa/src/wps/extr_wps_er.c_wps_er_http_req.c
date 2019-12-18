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
struct wps_er {int dummy; } ;
struct wpabuf {int dummy; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
struct http_request {int dummy; } ;
typedef  enum httpread_hdr_type { ____Placeholder_httpread_hdr_type } httpread_hdr_type ;

/* Variables and functions */
#define  HTTPREAD_HDR_TYPE_NOTIFY 128 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  http_put_date (struct wpabuf*) ; 
 int /*<<< orphan*/  http_request_deinit (struct http_request*) ; 
 struct sockaddr_in* http_request_get_cli_addr (struct http_request*) ; 
 int http_request_get_type (struct http_request*) ; 
 int /*<<< orphan*/  http_request_get_uri (struct http_request*) ; 
 int /*<<< orphan*/  http_request_send_and_deinit (struct http_request*,struct wpabuf*) ; 
 int /*<<< orphan*/  inet_ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_put_str (struct wpabuf*,char*) ; 
 int /*<<< orphan*/  wps_er_http_notify (struct wps_er*,struct http_request*) ; 

__attribute__((used)) static void wps_er_http_req(void *ctx, struct http_request *req)
{
	struct wps_er *er = ctx;
	struct sockaddr_in *cli = http_request_get_cli_addr(req);
	enum httpread_hdr_type type = http_request_get_type(req);
	struct wpabuf *buf;

	wpa_printf(MSG_DEBUG, "WPS ER: HTTP request: '%s' (type %d) from "
		   "%s:%d",
		   http_request_get_uri(req), type,
		   inet_ntoa(cli->sin_addr), ntohs(cli->sin_port));

	switch (type) {
	case HTTPREAD_HDR_TYPE_NOTIFY:
		wps_er_http_notify(er, req);
		break;
	default:
		wpa_printf(MSG_DEBUG, "WPS ER: Unsupported HTTP request type "
			   "%d", type);
		buf = wpabuf_alloc(200);
		if (buf == NULL) {
			http_request_deinit(req);
			return;
		}
		wpabuf_put_str(buf,
			       "HTTP/1.1 501 Unimplemented\r\n"
			       "Connection: close\r\n");
		http_put_date(buf);
		wpabuf_put_str(buf, "\r\n");
		http_request_send_and_deinit(req, buf);
		break;
	}
}