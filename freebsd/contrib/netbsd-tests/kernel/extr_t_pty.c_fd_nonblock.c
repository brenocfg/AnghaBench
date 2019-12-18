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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
fd_nonblock(int fd)
{
	int	opt;

	if ((opt = fcntl(fd, F_GETFL, NULL)) == -1)
		err(EXIT_FAILURE, "fcntl()");
	if (fcntl(fd, F_SETFL, opt | O_NONBLOCK) == -1)
		err(EXIT_FAILURE, "fcntl()");
}