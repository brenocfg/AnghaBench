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

/* Variables and functions */
 int /*<<< orphan*/  F_GETFL ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int fcntl (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
blocking_socket(int sock)
{
	int flags;

	flags = fcntl(sock, F_GETFL);
	PJDLOG_ASSERT(flags >= 0);
	return ((flags & O_NONBLOCK) == 0);
}