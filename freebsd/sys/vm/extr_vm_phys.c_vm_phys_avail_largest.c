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

/* Variables and functions */
 scalar_t__* phys_avail ; 
 scalar_t__ vm_phys_avail_size (int) ; 

int
vm_phys_avail_largest(void)
{
	vm_paddr_t sz, largesz;
	int largest;
	int i;

	largest = 0;
	largesz = 0;
	for (i = 0; phys_avail[i + 1]; i += 2) {
		sz = vm_phys_avail_size(i);
		if (sz > largesz) {
			largesz = sz;
			largest = i;
		}
	}

	return (largest);
}