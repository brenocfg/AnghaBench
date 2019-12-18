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
 int /*<<< orphan*/  SIOCGIFNAME ; 
 int errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,char*) ; 

int os_get_ifname(int fd, char* namebuf)
{
	if (ioctl(fd, SIOCGIFNAME, namebuf) < 0)
		return -errno;

	return 0;
}