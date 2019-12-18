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
struct TYPE_2__ {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
struct http_client {size_t req_pos; int /*<<< orphan*/  cb_ctx; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ ,struct http_client*,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * hread; int /*<<< orphan*/  max_response; int /*<<< orphan*/  sd; int /*<<< orphan*/ * req; TYPE_1__ dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_TYPE_WRITE ; 
 int /*<<< orphan*/  HTTP_CLIENT_FAILED ; 
 int /*<<< orphan*/  HTTP_CLIENT_TIMEOUT_SEC ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eloop_unregister_sock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  http_client_got_response ; 
 int /*<<< orphan*/ * httpread_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct http_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int send (int /*<<< orphan*/ ,size_t,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct http_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,struct http_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ *) ; 
 size_t wpabuf_head_u8 (int /*<<< orphan*/ *) ; 
 size_t wpabuf_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void http_client_tx_ready(int sock, void *eloop_ctx, void *sock_ctx)
{
	struct http_client *c = eloop_ctx;
	int res;
	size_t send_len;

	send_len = wpabuf_len(c->req) - c->req_pos;
	wpa_printf(MSG_DEBUG, "HTTP: Send client request to %s:%d (%lu of %lu "
		   "bytes remaining)",
		   inet_ntoa(c->dst.sin_addr), ntohs(c->dst.sin_port),
		   (unsigned long) wpabuf_len(c->req),
		   (unsigned long) send_len);

	res = send(c->sd, wpabuf_head_u8(c->req) + c->req_pos, send_len, 0);
	if (res < 0) {
		wpa_printf(MSG_DEBUG, "HTTP: Failed to send buffer: %s",
			   strerror(errno));
		eloop_unregister_sock(c->sd, EVENT_TYPE_WRITE);
		c->cb(c->cb_ctx, c, HTTP_CLIENT_FAILED);
		return;
	}

	if ((size_t) res < send_len) {
		wpa_printf(MSG_DEBUG, "HTTP: Sent %d of %lu bytes; %lu bytes "
			   "remaining",
			   res, (unsigned long) wpabuf_len(c->req),
			   (unsigned long) send_len - res);
		c->req_pos += res;
		return;
	}

	wpa_printf(MSG_DEBUG, "HTTP: Full client request sent to %s:%d",
		   inet_ntoa(c->dst.sin_addr), ntohs(c->dst.sin_port));
	eloop_unregister_sock(c->sd, EVENT_TYPE_WRITE);
	wpabuf_free(c->req);
	c->req = NULL;

	c->hread = httpread_create(c->sd, http_client_got_response, c,
				   c->max_response, HTTP_CLIENT_TIMEOUT_SEC);
	if (c->hread == NULL) {
		c->cb(c->cb_ctx, c, HTTP_CLIENT_FAILED);
		return;
	}
}