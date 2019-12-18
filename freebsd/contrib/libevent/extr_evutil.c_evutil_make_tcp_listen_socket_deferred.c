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
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  TCP_DEFER_ACCEPT ; 
 int setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

int
evutil_make_tcp_listen_socket_deferred(evutil_socket_t sock)
{
#if defined(EVENT__HAVE_NETINET_TCP_H) && defined(TCP_DEFER_ACCEPT)
	int one = 1;

	/* TCP_DEFER_ACCEPT tells the kernel to call defer accept() only after data
	 * has arrived and ready to read */ 
	return setsockopt(sock, IPPROTO_TCP, TCP_DEFER_ACCEPT, &one,
		(ev_socklen_t)sizeof(one)); 
#endif
	return 0;
}