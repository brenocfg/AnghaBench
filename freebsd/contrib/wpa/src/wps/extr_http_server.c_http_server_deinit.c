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
struct http_server {scalar_t__ fd; int /*<<< orphan*/  requests; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_TYPE_READ ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  eloop_unregister_sock (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  http_request_free_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (struct http_server*) ; 

void http_server_deinit(struct http_server *srv)
{
	if (srv == NULL)
		return;
	if (srv->fd >= 0) {
		eloop_unregister_sock(srv->fd, EVENT_TYPE_READ);
		close(srv->fd);
	}
	http_request_free_all(srv->requests);

	os_free(srv);
}