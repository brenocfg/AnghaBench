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
typedef  int /*<<< orphan*/  vm_fault_t ;
struct vma_data {unsigned long* maddr; int /*<<< orphan*/  lock; int /*<<< orphan*/  count; } ;
struct vm_fault {size_t pgoff; int /*<<< orphan*/  address; TYPE_1__* vma; } ;
typedef  size_t pgoff_t ;
struct TYPE_2__ {struct vma_data* vm_private_data; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  VM_FAULT_OOM ; 
 unsigned long __IA64_UNCACHED_OFFSET ; 
 int /*<<< orphan*/  numa_node_id () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 unsigned long uncached_alloc_page (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uncached_free_page (unsigned long,int) ; 
 int /*<<< orphan*/  vmf_insert_pfn (TYPE_1__*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static vm_fault_t
mspec_fault(struct vm_fault *vmf)
{
	unsigned long paddr, maddr;
	unsigned long pfn;
	pgoff_t index = vmf->pgoff;
	struct vma_data *vdata = vmf->vma->vm_private_data;

	maddr = (volatile unsigned long) vdata->maddr[index];
	if (maddr == 0) {
		maddr = uncached_alloc_page(numa_node_id(), 1);
		if (maddr == 0)
			return VM_FAULT_OOM;

		spin_lock(&vdata->lock);
		if (vdata->maddr[index] == 0) {
			vdata->count++;
			vdata->maddr[index] = maddr;
		} else {
			uncached_free_page(maddr, 1);
			maddr = vdata->maddr[index];
		}
		spin_unlock(&vdata->lock);
	}

	paddr = maddr & ~__IA64_UNCACHED_OFFSET;
	pfn = paddr >> PAGE_SHIFT;

	return vmf_insert_pfn(vmf->vma, vmf->address, pfn);
}