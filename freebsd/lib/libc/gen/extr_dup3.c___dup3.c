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
 int /*<<< orphan*/  EINVAL ; 
 int F_DUP2FD ; 
 int F_DUP2FD_CLOEXEC ; 
 int O_CLOEXEC ; 
 int _fcntl (int,int,int) ; 
 int /*<<< orphan*/  errno ; 

int
__dup3(int oldfd, int newfd, int flags)
{
	int how;

	if (oldfd == newfd) {
		errno = EINVAL;
		return (-1);
	}

	if (flags & ~O_CLOEXEC) {
		errno = EINVAL;
		return (-1);
	}

	how = (flags & O_CLOEXEC) ? F_DUP2FD_CLOEXEC : F_DUP2FD;

	return (_fcntl(oldfd, how, newfd));
}