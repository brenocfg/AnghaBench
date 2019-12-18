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
struct evutil_addrinfo {int dummy; } ;
typedef  int evutil_socket_t ;
typedef  scalar_t__ ev_uint16_t ;

/* Variables and functions */
 int bind_socket_ai (struct evutil_addrinfo*,int) ; 
 int /*<<< orphan*/  evutil_freeaddrinfo (struct evutil_addrinfo*) ; 
 struct evutil_addrinfo* make_addrinfo (char const*,scalar_t__) ; 

__attribute__((used)) static evutil_socket_t
bind_socket(const char *address, ev_uint16_t port, int reuse)
{
	evutil_socket_t fd;
	struct evutil_addrinfo *aitop = NULL;

	/* just create an unbound socket */
	if (address == NULL && port == 0)
		return bind_socket_ai(NULL, 0);

	aitop = make_addrinfo(address, port);

	if (aitop == NULL)
		return (-1);

	fd = bind_socket_ai(aitop, reuse);

	evutil_freeaddrinfo(aitop);

	return (fd);
}