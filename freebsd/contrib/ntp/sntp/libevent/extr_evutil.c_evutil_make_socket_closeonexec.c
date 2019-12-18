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
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int FD_CLOEXEC ; 
 int /*<<< orphan*/  F_GETFD ; 
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  event_warn (char*,int /*<<< orphan*/ ) ; 
 int fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
evutil_make_socket_closeonexec(evutil_socket_t fd)
{
#if !defined(_WIN32) && defined(EVENT__HAVE_SETFD)
	int flags;
	if ((flags = fcntl(fd, F_GETFD, NULL)) < 0) {
		event_warn("fcntl(%d, F_GETFD)", fd);
		return -1;
	}
	if (!(flags & FD_CLOEXEC)) {
		if (fcntl(fd, F_SETFD, flags | FD_CLOEXEC) == -1) {
			event_warn("fcntl(%d, F_SETFD)", fd);
			return -1;
		}
	}
#endif
	return 0;
}