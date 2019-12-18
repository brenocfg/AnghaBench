#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  TYPE_1__* vm_object_t ;
struct vnode {int dummy; } ;
struct TYPE_5__ {struct vnode* handle; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (TYPE_1__*) ; 
 int VM_PAGER_PUT_SYNC ; 
 int VOP_PUTPAGES (struct vnode*,int /*<<< orphan*/ *,int,int,int*) ; 
 scalar_t__ vm_page_count_min () ; 

__attribute__((used)) static void
vnode_pager_putpages(vm_object_t object, vm_page_t *m, int count,
    int flags, int *rtvals)
{
	int rtval;
	struct vnode *vp;
	int bytes = count * PAGE_SIZE;

	/*
	 * Force synchronous operation if we are extremely low on memory
	 * to prevent a low-memory deadlock.  VOP operations often need to
	 * allocate more memory to initiate the I/O ( i.e. do a BMAP
	 * operation ).  The swapper handles the case by limiting the amount
	 * of asynchronous I/O, but that sort of solution doesn't scale well
	 * for the vnode pager without a lot of work.
	 *
	 * Also, the backing vnode's iodone routine may not wake the pageout
	 * daemon up.  This should be probably be addressed XXX.
	 */

	if (vm_page_count_min())
		flags |= VM_PAGER_PUT_SYNC;

	/*
	 * Call device-specific putpages function
	 */
	vp = object->handle;
	VM_OBJECT_WUNLOCK(object);
	rtval = VOP_PUTPAGES(vp, m, bytes, flags, rtvals);
	KASSERT(rtval != EOPNOTSUPP, 
	    ("vnode_pager: stale FS putpages\n"));
	VM_OBJECT_WLOCK(object);
}