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
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int dummy; } ;
struct http_server {int /*<<< orphan*/  request_count; struct http_request* requests; int /*<<< orphan*/  fd; } ;
struct http_request {struct http_request* next; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int accept (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 struct http_request* http_request_init (struct http_server*,int,struct sockaddr_in*) ; 
 int /*<<< orphan*/  inet_ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void http_server_cb(int sd, void *eloop_ctx, void *sock_ctx)
{
	struct sockaddr_in addr;
	socklen_t addr_len = sizeof(addr);
	struct http_server *srv = eloop_ctx;
	int conn;
	struct http_request *req;

	conn = accept(srv->fd, (struct sockaddr *) &addr, &addr_len);
	if (conn < 0) {
		wpa_printf(MSG_DEBUG, "HTTP: Failed to accept new connection: "
			   "%s", strerror(errno));
		return;
	}
	wpa_printf(MSG_DEBUG, "HTTP: Connection from %s:%d",
		   inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));

	req = http_request_init(srv, conn, &addr);
	if (req == NULL) {
		close(conn);
		return;
	}

	req->next = srv->requests;
	srv->requests = req;
	srv->request_count++;
}