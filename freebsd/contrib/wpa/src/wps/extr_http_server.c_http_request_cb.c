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
struct httpread {int dummy; } ;
struct http_server {int /*<<< orphan*/  cb_ctx; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ ,struct http_request*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
struct http_request {TYPE_1__ cli; struct http_server* srv; } ;
typedef  enum httpread_event { ____Placeholder_httpread_event } httpread_event ;

/* Variables and functions */
 int HTTPREAD_EVENT_FILE_READY ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  http_request_deinit (struct http_request*) ; 
 int /*<<< orphan*/  inet_ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct http_request*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void http_request_cb(struct httpread *handle, void *cookie,
			    enum httpread_event en)
{
	struct http_request *req = cookie;
	struct http_server *srv = req->srv;

	if (en == HTTPREAD_EVENT_FILE_READY) {
		wpa_printf(MSG_DEBUG, "HTTP: Request from %s:%d received",
			   inet_ntoa(req->cli.sin_addr),
			   ntohs(req->cli.sin_port));
		srv->cb(srv->cb_ctx, req);
		return;
	}
	wpa_printf(MSG_DEBUG, "HTTP: Request from %s:%d could not be received "
		   "completely", inet_ntoa(req->cli.sin_addr),
		   ntohs(req->cli.sin_port));
	http_request_deinit(req);
}