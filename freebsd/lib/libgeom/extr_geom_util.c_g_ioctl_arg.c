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
 int ioctl (int,unsigned long,...) ; 

__attribute__((used)) static int
g_ioctl_arg(int fd, unsigned long cmd, void *arg)
{
	int ret;

	if (arg != NULL)
		ret = ioctl(fd, cmd, arg);
	else
		ret = ioctl(fd, cmd);
	return (ret >= 0 ? 0 : -1);
}