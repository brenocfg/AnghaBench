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
typedef  int /*<<< orphan*/ * vm_object_t ;
typedef  int u_int ;
struct vm_domain {int /*<<< orphan*/  vmd_domain; int /*<<< orphan*/  vmd_pageout_deficit; } ;

/* Variables and functions */
 int EAGAIN ; 
 int VM_ALLOC_COUNT_SHIFT ; 
 int VM_ALLOC_WAITFAIL ; 
 int VM_ALLOC_WAITOK ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max (int,int) ; 
 int /*<<< orphan*/  vm_domain_free_assert_unlocked (struct vm_domain*) ; 
 int /*<<< orphan*/  vm_wait_domain (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vm_domain_alloc_fail(struct vm_domain *vmd, vm_object_t object, int req)
{

	vm_domain_free_assert_unlocked(vmd);

	atomic_add_int(&vmd->vmd_pageout_deficit,
	    max((u_int)req >> VM_ALLOC_COUNT_SHIFT, 1));
	if (req & (VM_ALLOC_WAITOK | VM_ALLOC_WAITFAIL)) {
		if (object != NULL) 
			VM_OBJECT_WUNLOCK(object);
		vm_wait_domain(vmd->vmd_domain);
		if (object != NULL) 
			VM_OBJECT_WLOCK(object);
		if (req & VM_ALLOC_WAITOK)
			return (EAGAIN);
	}

	return (0);
}