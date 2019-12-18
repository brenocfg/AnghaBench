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
struct wpabuf {int dummy; } ;
struct http_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  http_put_date (struct wpabuf*) ; 
 int /*<<< orphan*/  http_request_deinit (struct http_request*) ; 
 int /*<<< orphan*/  http_request_send_and_deinit (struct http_request*,struct wpabuf*) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_put_str (struct wpabuf*,char*) ; 

__attribute__((used)) static void wps_er_http_resp_ok(struct http_request *req)
{
	struct wpabuf *buf;
	buf = wpabuf_alloc(200);
	if (buf == NULL) {
		http_request_deinit(req);
		return;
	}

	wpabuf_put_str(buf,
		       "HTTP/1.1 200 OK\r\n"
		       "Server: unspecified, UPnP/1.0, unspecified\r\n"
		       "Connection: close\r\n"
		       "Content-Length: 0\r\n");
	http_put_date(buf);
	wpabuf_put_str(buf, "\r\n");
	http_request_send_and_deinit(req, buf);
}