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
 int /*<<< orphan*/  MIPS_KSEG0_LARGEST_PHYS ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  vm_page_reclaim_contig (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pmap_grow_direct_page(int req)
{

#ifdef __mips_n64
	vm_wait(NULL);
#else
	if (!vm_page_reclaim_contig(req, 1, 0, MIPS_KSEG0_LARGEST_PHYS,
	    PAGE_SIZE, 0))
		vm_wait(NULL);
#endif
}