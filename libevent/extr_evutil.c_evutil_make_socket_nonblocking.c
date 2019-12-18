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
typedef  scalar_t__ evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  FIONBIO ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 scalar_t__ SOCKET_ERROR ; 
 int /*<<< orphan*/  event_sock_warn (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  event_warn (char*,scalar_t__) ; 
 int fcntl (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ioctlsocket (scalar_t__,int /*<<< orphan*/ ,unsigned long*) ; 

int
evutil_make_socket_nonblocking(evutil_socket_t fd)
{
#ifdef _WIN32
	{
		unsigned long nonblocking = 1;
		if (ioctlsocket(fd, FIONBIO, &nonblocking) == SOCKET_ERROR) {
			event_sock_warn(fd, "fcntl(%d, F_GETFL)", (int)fd);
			return -1;
		}
	}
#else
	{
		int flags;
		if ((flags = fcntl(fd, F_GETFL, NULL)) < 0) {
			event_warn("fcntl(%d, F_GETFL)", fd);
			return -1;
		}
		if (!(flags & O_NONBLOCK)) {
			if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) {
				event_warn("fcntl(%d, F_SETFL)", fd);
				return -1;
			}
		}
	}
#endif
	return 0;
}