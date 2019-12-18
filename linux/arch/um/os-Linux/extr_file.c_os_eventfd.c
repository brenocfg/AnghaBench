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
 int errno ; 
 int eventfd (unsigned int,int) ; 

int os_eventfd(unsigned int initval, int flags)
{
	int fd = eventfd(initval, flags);

	if (fd < 0)
		return -errno;
	return fd;
}