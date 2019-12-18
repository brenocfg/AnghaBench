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
typedef  int /*<<< orphan*/ * vm_page_t ;
typedef  scalar_t__ vm_paddr_t ;
struct vm_phys_seg {scalar_t__ start; scalar_t__ end; int /*<<< orphan*/ * first_page; } ;

/* Variables and functions */
 size_t atop (scalar_t__) ; 
 int vm_phys_nsegs ; 
 struct vm_phys_seg* vm_phys_segs ; 

vm_page_t
vm_phys_paddr_to_vm_page(vm_paddr_t pa)
{
	struct vm_phys_seg *seg;
	int segind;

	for (segind = 0; segind < vm_phys_nsegs; segind++) {
		seg = &vm_phys_segs[segind];
		if (pa >= seg->start && pa < seg->end)
			return (&seg->first_page[atop(pa - seg->start)]);
	}
	return (NULL);
}