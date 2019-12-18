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
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  event_warn (char*,int /*<<< orphan*/ ) ; 
 int evutil_make_socket_nonblocking (int /*<<< orphan*/ ) ; 
 int fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
evutil_fast_socket_nonblocking(evutil_socket_t fd)
{
#ifdef _WIN32
	return evutil_make_socket_nonblocking(fd);
#else
	if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1) {
		event_warn("fcntl(%d, F_SETFL)", fd);
		return -1;
	}
	return 0;
#endif
}