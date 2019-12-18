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
 int* mem_locality ; 
 int vm_ndomains ; 

int
vm_phys_mem_affinity(int f, int t)
{

#ifdef NUMA
	if (mem_locality == NULL)
		return (-1);
	if (f >= vm_ndomains || t >= vm_ndomains)
		return (-1);
	return (mem_locality[f * vm_ndomains + t]);
#else
	return (-1);
#endif
}