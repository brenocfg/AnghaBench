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
typedef  int /*<<< orphan*/ * vm_object_t ;
struct ttm_buffer_object {int num_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_ALLOC_WAITFAIL ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cdev_pager_free_page (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cdev_pager_lookup (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  vm_object_deallocate (int /*<<< orphan*/ *) ; 
 scalar_t__ vm_page_busy_acquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vm_page_lookup (int /*<<< orphan*/ *,int) ; 

void
ttm_bo_release_mmap(struct ttm_buffer_object *bo)
{
	vm_object_t vm_obj;
	vm_page_t m;
	int i;

	vm_obj = cdev_pager_lookup(bo);
	if (vm_obj == NULL)
		return;

	VM_OBJECT_WLOCK(vm_obj);
retry:
	for (i = 0; i < bo->num_pages; i++) {
		m = vm_page_lookup(vm_obj, i);
		if (m == NULL)
			continue;
		if (vm_page_busy_acquire(m, VM_ALLOC_WAITFAIL) == 0)
			goto retry;
		cdev_pager_free_page(vm_obj, m);
	}
	VM_OBJECT_WUNLOCK(vm_obj);

	vm_object_deallocate(vm_obj);
}