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
struct vm_area_struct {int /*<<< orphan*/  vm_mm; } ;
struct binder_alloc {struct vm_area_struct* vma; int /*<<< orphan*/  vma_vm_mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static inline void binder_alloc_set_vma(struct binder_alloc *alloc,
		struct vm_area_struct *vma)
{
	if (vma)
		alloc->vma_vm_mm = vma->vm_mm;
	/*
	 * If we see alloc->vma is not NULL, buffer data structures set up
	 * completely. Look at smp_rmb side binder_alloc_get_vma.
	 * We also want to guarantee new alloc->vma_vm_mm is always visible
	 * if alloc->vma is set.
	 */
	smp_wmb();
	alloc->vma = vma;
}