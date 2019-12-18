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
typedef  scalar_t__ vm_paddr_t ;
struct TYPE_2__ {scalar_t__ end; scalar_t__ start; int domain; } ;

/* Variables and functions */
 TYPE_1__* mem_affinity ; 
 int vm_ndomains ; 

int
_vm_phys_domain(vm_paddr_t pa)
{
#ifdef NUMA
	int i;

	if (vm_ndomains == 1 || mem_affinity == NULL)
		return (0);

	/*
	 * Check for any memory that overlaps.
	 */
	for (i = 0; mem_affinity[i].end != 0; i++)
		if (mem_affinity[i].start <= pa &&
		    mem_affinity[i].end >= pa)
			return (mem_affinity[i].domain);
#endif
	return (0);
}