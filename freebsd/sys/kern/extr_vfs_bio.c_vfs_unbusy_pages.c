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
typedef  scalar_t__ vm_page_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  vm_object_t ;
struct buf {int b_flags; int b_npages; scalar_t__* b_pages; scalar_t__ b_data; int /*<<< orphan*/  b_offset; TYPE_1__* b_bufobj; } ;
struct TYPE_2__ {int /*<<< orphan*/  bo_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_CHECK_MAPPED (struct buf*) ; 
 int /*<<< orphan*/  BUF_CHECK_UNMAPPED (struct buf*) ; 
 int B_VMIO ; 
 scalar_t__ OFF_TO_IDX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_RLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_RUNLOCK (int /*<<< orphan*/ ) ; 
 scalar_t__ bogus_page ; 
 scalar_t__ buf_mapped (struct buf*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pmap_qenter (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  runningbufwakeup (struct buf*) ; 
 int /*<<< orphan*/  trunc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_pip_wakeupn (int /*<<< orphan*/ ,int) ; 
 scalar_t__ vm_page_lookup (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vm_page_sunbusy (scalar_t__) ; 

void
vfs_unbusy_pages(struct buf *bp)
{
	int i;
	vm_object_t obj;
	vm_page_t m;
	bool bogus;

	runningbufwakeup(bp);
	if (!(bp->b_flags & B_VMIO))
		return;

	obj = bp->b_bufobj->bo_object;
	bogus = false;
	for (i = 0; i < bp->b_npages; i++) {
		m = bp->b_pages[i];
		if (m == bogus_page) {
			if (bogus == false) {
				bogus = true;
				VM_OBJECT_RLOCK(obj);
			}
			m = vm_page_lookup(obj, OFF_TO_IDX(bp->b_offset) + i);
			if (!m)
				panic("vfs_unbusy_pages: page missing\n");
			bp->b_pages[i] = m;
			if (buf_mapped(bp)) {
				BUF_CHECK_MAPPED(bp);
				pmap_qenter(trunc_page((vm_offset_t)bp->b_data),
				    bp->b_pages, bp->b_npages);
			} else
				BUF_CHECK_UNMAPPED(bp);
		}
		vm_page_sunbusy(m);
	}
	if (bogus)
		VM_OBJECT_RUNLOCK(obj);
	vm_object_pip_wakeupn(obj, bp->b_npages);
}