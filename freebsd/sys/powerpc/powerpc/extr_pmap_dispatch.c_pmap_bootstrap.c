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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  MMU_BOOTSTRAP (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobj_class_compile_static (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobj_init_static (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmu_def_impl ; 
 int /*<<< orphan*/  mmu_kernel_kops ; 
 int /*<<< orphan*/  mmu_kernel_obj ; 
 int /*<<< orphan*/ * mmu_obj ; 

void
pmap_bootstrap(vm_offset_t start, vm_offset_t end)
{
	mmu_obj = &mmu_kernel_obj;

	/*
	 * Take care of compiling the selected class, and
	 * then statically initialise the MMU object
	 */
	kobj_class_compile_static(mmu_def_impl, &mmu_kernel_kops);
	kobj_init_static((kobj_t)mmu_obj, mmu_def_impl);

	MMU_BOOTSTRAP(mmu_obj, start, end);
}