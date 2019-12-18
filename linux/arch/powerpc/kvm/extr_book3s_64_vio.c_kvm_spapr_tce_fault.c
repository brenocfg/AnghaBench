#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_fault_t ;
struct vm_fault {scalar_t__ pgoff; struct page* page; TYPE_2__* vma; } ;
struct page {int dummy; } ;
struct kvmppc_spapr_tce_table {int /*<<< orphan*/  size; } ;
struct TYPE_4__ {TYPE_1__* vm_file; } ;
struct TYPE_3__ {struct kvmppc_spapr_tce_table* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_FAULT_OOM ; 
 int /*<<< orphan*/  VM_FAULT_SIGBUS ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 struct page* kvm_spapr_get_tce_page (struct kvmppc_spapr_tce_table*,scalar_t__) ; 
 scalar_t__ kvmppc_tce_pages (int /*<<< orphan*/ ) ; 

__attribute__((used)) static vm_fault_t kvm_spapr_tce_fault(struct vm_fault *vmf)
{
	struct kvmppc_spapr_tce_table *stt = vmf->vma->vm_file->private_data;
	struct page *page;

	if (vmf->pgoff >= kvmppc_tce_pages(stt->size))
		return VM_FAULT_SIGBUS;

	page = kvm_spapr_get_tce_page(stt, vmf->pgoff);
	if (!page)
		return VM_FAULT_OOM;

	get_page(page);
	vmf->page = page;
	return 0;
}