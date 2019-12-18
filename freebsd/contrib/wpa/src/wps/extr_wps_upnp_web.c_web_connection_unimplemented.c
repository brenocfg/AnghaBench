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
 int /*<<< orphan*/  HTTP_UNIMPLEMENTED ; 
 int /*<<< orphan*/  http_put_empty (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  http_request_deinit (struct http_request*) ; 
 int /*<<< orphan*/  http_request_send_and_deinit (struct http_request*,struct wpabuf*) ; 
 struct wpabuf* wpabuf_alloc (int) ; 

__attribute__((used)) static void web_connection_unimplemented(struct http_request *req)
{
	struct wpabuf *buf;
	buf = wpabuf_alloc(200);
	if (buf == NULL) {
		http_request_deinit(req);
		return;
	}
	http_put_empty(buf, HTTP_UNIMPLEMENTED);
	http_request_send_and_deinit(req, buf);
}