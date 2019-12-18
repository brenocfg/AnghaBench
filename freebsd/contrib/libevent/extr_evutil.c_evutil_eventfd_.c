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
typedef  int evutil_socket_t ;

/* Variables and functions */
 int EVUTIL_EFD_CLOEXEC ; 
 int EVUTIL_EFD_NONBLOCK ; 
 int eventfd (unsigned int,int) ; 
 int /*<<< orphan*/  evutil_closesocket (int) ; 
 scalar_t__ evutil_fast_socket_closeonexec (int) ; 
 scalar_t__ evutil_fast_socket_nonblocking (int) ; 

evutil_socket_t
evutil_eventfd_(unsigned initval, int flags)
{
#if defined(EVENT__HAVE_EVENTFD) && defined(EVENT__HAVE_SYS_EVENTFD_H)
	int r;
#if defined(EFD_CLOEXEC) && defined(EFD_NONBLOCK)
	r = eventfd(initval, flags);
	if (r >= 0 || flags == 0)
		return r;
#endif
	r = eventfd(initval, 0);
	if (r < 0)
		return r;
	if (flags & EVUTIL_EFD_CLOEXEC) {
		if (evutil_fast_socket_closeonexec(r) < 0) {
			evutil_closesocket(r);
			return -1;
		}
	}
	if (flags & EVUTIL_EFD_NONBLOCK) {
		if (evutil_fast_socket_nonblocking(r) < 0) {
			evutil_closesocket(r);
			return -1;
		}
	}
	return r;
#else
	return -1;
#endif
}