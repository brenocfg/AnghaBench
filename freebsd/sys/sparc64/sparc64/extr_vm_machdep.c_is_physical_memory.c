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
typedef  scalar_t__ vm_paddr_t ;
struct ofw_mem_region {scalar_t__ mr_start; scalar_t__ mr_size; } ;

/* Variables and functions */
 struct ofw_mem_region* sparc64_memreg ; 
 int sparc64_nmemreg ; 

int
is_physical_memory(vm_paddr_t addr)
{
	struct ofw_mem_region *mr;

	for (mr = sparc64_memreg; mr < sparc64_memreg + sparc64_nmemreg; mr++)
		if (addr >= mr->mr_start && addr < mr->mr_start + mr->mr_size)
			return (1);
	return (0);
}