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
typedef  int /*<<< orphan*/  one ;
typedef  int /*<<< orphan*/  evutil_socket_t ;
typedef  int /*<<< orphan*/  ev_socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEPORT ; 
 int setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

int
evutil_make_listen_socket_reuseable_port(evutil_socket_t sock)
{
#if defined __linux__ && defined(SO_REUSEPORT)
	int one = 1;
	/* REUSEPORT on Linux 3.9+ means, "Multiple servers (processes or
	 * threads) can bind to the same port if they each set the option. */
	return setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, (void*) &one,
	    (ev_socklen_t)sizeof(one));
#else
	return 0;
#endif
}