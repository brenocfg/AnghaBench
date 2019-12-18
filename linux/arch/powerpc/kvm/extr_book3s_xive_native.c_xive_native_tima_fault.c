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
typedef  int /*<<< orphan*/  vm_fault_t ;
struct vm_fault {int pgoff; int /*<<< orphan*/  address; struct vm_area_struct* vma; } ;
struct vm_area_struct {int vm_pgoff; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  VM_FAULT_NOPAGE ; 
 int /*<<< orphan*/  VM_FAULT_SIGBUS ; 
 int /*<<< orphan*/  vmf_insert_pfn (struct vm_area_struct*,int /*<<< orphan*/ ,int) ; 
 int xive_tima_os ; 

__attribute__((used)) static vm_fault_t xive_native_tima_fault(struct vm_fault *vmf)
{
	struct vm_area_struct *vma = vmf->vma;

	switch (vmf->pgoff - vma->vm_pgoff) {
	case 0: /* HW - forbid access */
	case 1: /* HV - forbid access */
		return VM_FAULT_SIGBUS;
	case 2: /* OS */
		vmf_insert_pfn(vma, vmf->address, xive_tima_os >> PAGE_SHIFT);
		return VM_FAULT_NOPAGE;
	case 3: /* USER - TODO */
	default:
		return VM_FAULT_SIGBUS;
	}
}