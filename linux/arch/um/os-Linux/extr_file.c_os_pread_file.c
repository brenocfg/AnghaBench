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
 int pread (int,void*,int,unsigned long long) ; 

int os_pread_file(int fd, void *buf, int len, unsigned long long offset)
{
	int n = pread(fd, buf, len, offset);

	if (n < 0)
		return -errno;
	return n;
}