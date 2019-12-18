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
 int evutil_win_socketpair (int,int,int,int /*<<< orphan*/ *) ; 
 int socketpair (int,int,int,int /*<<< orphan*/ *) ; 

int
evutil_socketpair(int family, int type, int protocol, evutil_socket_t fd[2])
{
#ifndef _WIN32
	return socketpair(family, type, protocol, fd);
#else
	return evutil_win_socketpair(family, type, protocol, fd);
#endif
}