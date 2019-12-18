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
struct wpabuf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
struct http_request {int /*<<< orphan*/  fd; TYPE_1__ cli; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  inet_ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf*) ; 
 size_t wpabuf_len (struct wpabuf*) ; 

void http_request_send(struct http_request *req, struct wpabuf *resp)
{
	int res;

	wpa_printf(MSG_DEBUG, "HTTP: Send %lu byte response to %s:%d",
		   (unsigned long) wpabuf_len(resp),
		   inet_ntoa(req->cli.sin_addr),
		   ntohs(req->cli.sin_port));

	res = send(req->fd, wpabuf_head(resp), wpabuf_len(resp), 0);
	if (res < 0) {
		wpa_printf(MSG_DEBUG, "HTTP: Send failed: %s",
			   strerror(errno));
	} else if ((size_t) res < wpabuf_len(resp)) {
		wpa_printf(MSG_DEBUG, "HTTP: Sent only %d of %lu bytes",
			   res, (unsigned long) wpabuf_len(resp));
		/* TODO: add eloop handler for sending rest of the data */
	}

	wpabuf_free(resp);
}