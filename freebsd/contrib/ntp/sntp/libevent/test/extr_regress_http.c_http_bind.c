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
struct evhttp_bound_socket {int dummy; } ;
struct evhttp {int dummy; } ;
typedef  scalar_t__ ev_uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  event_errx (int,char*) ; 
 struct evhttp_bound_socket* evhttp_bind_socket_with_handle (struct evhttp*,char*,scalar_t__) ; 
 int /*<<< orphan*/  evhttp_bound_socket_get_fd (struct evhttp_bound_socket*) ; 
 int regress_get_socket_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
http_bind(struct evhttp *myhttp, ev_uint16_t *pport, int ipv6)
{
	int port;
	struct evhttp_bound_socket *sock;

	if (ipv6)
		sock = evhttp_bind_socket_with_handle(myhttp, "::1", *pport);
	else
		sock = evhttp_bind_socket_with_handle(myhttp, "127.0.0.1", *pport);

	if (sock == NULL) {
		if (ipv6)
			return -1;
		else
			event_errx(1, "Could not start web server");
	}

	port = regress_get_socket_port(evhttp_bound_socket_get_fd(sock));
	if (port < 0)
		return -1;
	*pport = (ev_uint16_t) port;

	return 0;
}