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
 long EFAULT ; 
 unsigned long PAGE_SIZE ; 
 long __probe_kernel_read (void*,void const*,size_t) ; 

long probe_kernel_read(void *dst, const void *src, size_t size)
{
	unsigned long addr = (unsigned long)src;

	if (addr < PAGE_SIZE)
		return -EFAULT;

	/* check for I/O space F_EXTEND(0xfff00000) access as well? */

	return __probe_kernel_read(dst, src, size);
}