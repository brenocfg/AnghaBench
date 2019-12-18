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
typedef  scalar_t__ u_int ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCGSECTORSIZE ; 
 int g_ioctl_arg (int,int /*<<< orphan*/ ,scalar_t__*) ; 

ssize_t
g_sectorsize(int fd)
{
	u_int sectorsize;

	if (g_ioctl_arg(fd, DIOCGSECTORSIZE, &sectorsize) == -1)
		return (-1);
	return ((ssize_t)sectorsize);
}