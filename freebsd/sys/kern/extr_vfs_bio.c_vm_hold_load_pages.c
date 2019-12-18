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
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  scalar_t__ vm_offset_t ;
struct buf {int b_npages; int /*<<< orphan*/ * b_pages; scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_CHECK_MAPPED (struct buf*) ; 
 scalar_t__ PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 int VM_ALLOC_COUNT (scalar_t__) ; 
 int VM_ALLOC_NOOBJ ; 
 int VM_ALLOC_SYSTEM ; 
 int VM_ALLOC_WAITOK ; 
 int VM_ALLOC_WIRED ; 
 int /*<<< orphan*/  pmap_qenter (scalar_t__,int /*<<< orphan*/ *,int) ; 
 scalar_t__ round_page (scalar_t__) ; 
 scalar_t__ trunc_page (scalar_t__) ; 
 int /*<<< orphan*/  vm_page_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
vm_hold_load_pages(struct buf *bp, vm_offset_t from, vm_offset_t to)
{
	vm_offset_t pg;
	vm_page_t p;
	int index;

	BUF_CHECK_MAPPED(bp);

	to = round_page(to);
	from = round_page(from);
	index = (from - trunc_page((vm_offset_t)bp->b_data)) >> PAGE_SHIFT;

	for (pg = from; pg < to; pg += PAGE_SIZE, index++) {
		/*
		 * note: must allocate system pages since blocking here
		 * could interfere with paging I/O, no matter which
		 * process we are.
		 */
		p = vm_page_alloc(NULL, 0, VM_ALLOC_SYSTEM | VM_ALLOC_NOOBJ |
		    VM_ALLOC_WIRED | VM_ALLOC_COUNT((to - pg) >> PAGE_SHIFT) |
		    VM_ALLOC_WAITOK);
		pmap_qenter(pg, &p, 1);
		bp->b_pages[index] = p;
	}
	bp->b_npages = index;
}