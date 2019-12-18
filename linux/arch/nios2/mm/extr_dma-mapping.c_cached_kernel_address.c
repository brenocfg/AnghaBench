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
 unsigned long CONFIG_NIOS2_IO_REGION_BASE ; 
 unsigned long CONFIG_NIOS2_KERNEL_REGION_BASE ; 

void *cached_kernel_address(void *ptr)
{
	unsigned long addr = (unsigned long)ptr;

	addr &= ~CONFIG_NIOS2_IO_REGION_BASE;
	addr |= CONFIG_NIOS2_KERNEL_REGION_BASE;

	return (void *)ptr;
}