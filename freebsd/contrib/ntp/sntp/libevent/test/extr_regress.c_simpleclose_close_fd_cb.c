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
 int /*<<< orphan*/  TT_BLATHER (char*) ; 
 int /*<<< orphan*/  evutil_closesocket (int) ; 
 int have_closed ; 

__attribute__((used)) static void
simpleclose_close_fd_cb(evutil_socket_t s, short what, void *ptr)
{
	evutil_socket_t **fds = ptr;
	TT_BLATHER(("Closing"));
	evutil_closesocket(*fds[0]);
	evutil_closesocket(*fds[1]);
	*fds[0] = -1;
	*fds[1] = -1;
	have_closed = 1;
}