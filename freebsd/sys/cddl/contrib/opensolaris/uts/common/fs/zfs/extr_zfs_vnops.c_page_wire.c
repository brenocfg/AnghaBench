#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  v_object; } ;
typedef  TYPE_1__ vnode_t ;
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int /*<<< orphan*/  vm_object_t ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  OFF_TO_IDX (int /*<<< orphan*/ ) ; 
 int VM_ALLOC_IGN_SBUSY ; 
 int VM_ALLOC_NOBUSY ; 
 int VM_ALLOC_NOCREAT ; 
 int VM_ALLOC_WIRED ; 
 int /*<<< orphan*/  vm_page_grab_valid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfs_vmobject_assert_wlocked (int /*<<< orphan*/ ) ; 

__attribute__((used)) static vm_page_t
page_wire(vnode_t *vp, int64_t start)
{
	vm_object_t obj;
	vm_page_t m;

	obj = vp->v_object;
	zfs_vmobject_assert_wlocked(obj);

	vm_page_grab_valid(&m, obj, OFF_TO_IDX(start), VM_ALLOC_NOCREAT |
	    VM_ALLOC_WIRED | VM_ALLOC_IGN_SBUSY | VM_ALLOC_NOBUSY);
	return (m);
}