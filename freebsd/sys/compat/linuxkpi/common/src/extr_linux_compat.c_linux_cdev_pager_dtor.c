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
struct vm_operations_struct {int /*<<< orphan*/  (* close ) (struct vm_area_struct*) ;} ;
struct vm_area_struct {TYPE_1__* vm_mm; struct vm_operations_struct* vm_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 struct vm_area_struct* linux_cdev_handle_find (void*) ; 
 int /*<<< orphan*/  linux_cdev_handle_free (struct vm_area_struct*) ; 
 int /*<<< orphan*/  linux_cdev_handle_remove (struct vm_area_struct*) ; 
 int /*<<< orphan*/  stub1 (struct vm_area_struct*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
linux_cdev_pager_dtor(void *handle)
{
	const struct vm_operations_struct *vm_ops;
	struct vm_area_struct *vmap;

	vmap = linux_cdev_handle_find(handle);
	MPASS(vmap != NULL);

	/*
	 * Remove handle before calling close operation to prevent
	 * other threads from reusing the handle pointer.
	 */
	linux_cdev_handle_remove(vmap);

	down_write(&vmap->vm_mm->mmap_sem);
	vm_ops = vmap->vm_ops;
	if (likely(vm_ops != NULL))
		vm_ops->close(vmap);
	up_write(&vmap->vm_mm->mmap_sem);

	linux_cdev_handle_free(vmap);
}