#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long dcache_base; unsigned long dcache_high; } ;

/* Variables and functions */
 unsigned long UNCACHED_SHADOW_MASK ; 
 TYPE_1__ cpuinfo ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

void *uncached_kernel_address(void *ptr)
{
	unsigned long addr = (unsigned long)ptr;

	addr |= UNCACHED_SHADOW_MASK;
	if (addr > cpuinfo.dcache_base && addr < cpuinfo.dcache_high)
		pr_warn("ERROR: Your cache coherent area is CACHED!!!\n");
	return (void *)addr;
}