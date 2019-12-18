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
typedef  int /*<<< orphan*/  ev_uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  event_errx (int,char*) ; 
 struct evhttp_bound_socket* evhttp_bind_socket_with_handle (struct evhttp*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_bound_socket_get_fd (struct evhttp_bound_socket*) ; 
 struct evhttp* evhttp_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regress_get_socket_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct evhttp *
http_setup(ev_uint16_t *pport)
{
	struct evhttp *myhttp;
	ev_uint16_t port;
	struct evhttp_bound_socket *sock;

	myhttp = evhttp_new(NULL);
	if (!myhttp)
		event_errx(1, "Could not start web server");

	/* Try a few different ports */
	sock = evhttp_bind_socket_with_handle(myhttp, "127.0.0.1", 0);
	if (!sock)
		event_errx(1, "Couldn't open web port");

	port = regress_get_socket_port(evhttp_bound_socket_get_fd(sock));

	*pport = port;
	return (myhttp);
}