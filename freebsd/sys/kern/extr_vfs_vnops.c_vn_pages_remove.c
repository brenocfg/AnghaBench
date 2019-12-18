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
typedef  int /*<<< orphan*/  vm_pindex_t ;
typedef  int /*<<< orphan*/ * vm_object_t ;
struct vnode {int /*<<< orphan*/ * v_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_OBJECT_WLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_object_page_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
vn_pages_remove(struct vnode *vp, vm_pindex_t start, vm_pindex_t end)
{
	vm_object_t object;

	if ((object = vp->v_object) == NULL)
		return;
	VM_OBJECT_WLOCK(object);
	vm_object_page_remove(object, start, end, 0);
	VM_OBJECT_WUNLOCK(object);
}