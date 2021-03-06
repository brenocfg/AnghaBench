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
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EVUTIL_SET_SOCKET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  WSAEWOULDBLOCK ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  event_sock_err (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sock_err_fn(void)
{
	evutil_socket_t fd = socket(AF_INET, SOCK_STREAM, 0);
#ifdef _WIN32
	EVUTIL_SET_SOCKET_ERROR(WSAEWOULDBLOCK);
#else
	errno = EAGAIN;
#endif
	event_sock_err(20, fd, "Unhappy socket");
}