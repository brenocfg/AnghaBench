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
 int /*<<< orphan*/  evutil_closesocket (int) ; 

__attribute__((used)) static void
socketpair_close(evutil_socket_t fd[2])
{
	if (fd[0] != -1)
		evutil_closesocket(fd[0]);
	if (fd[1] != -1)
		evutil_closesocket(fd[1]);
}