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
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  TIOCSCTTY ; 
 int _ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ getsid (int /*<<< orphan*/ ) ; 

int
tcsetsid(int fd, pid_t pid)
{

	if (pid != getsid(0)) {
		errno = EINVAL;
		return (-1);
	}

	return (_ioctl(fd, TIOCSCTTY, NULL));
}