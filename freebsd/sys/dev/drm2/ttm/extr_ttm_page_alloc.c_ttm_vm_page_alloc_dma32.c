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
typedef  int /*<<< orphan*/  vm_memattr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/ * vm_page_alloc_contig (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_reclaim_contig (int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static vm_page_t
ttm_vm_page_alloc_dma32(int req, vm_memattr_t memattr)
{
	vm_page_t p;
	int tries;

	for (tries = 0; ; tries++) {
		p = vm_page_alloc_contig(NULL, 0, req, 1, 0, 0xffffffff,
		    PAGE_SIZE, 0, memattr);
		if (p != NULL || tries > 2)
			return (p);
		if (!vm_page_reclaim_contig(req, 1, 0, 0xffffffff,
		    PAGE_SIZE, 0))
			vm_wait(NULL);
	}
}