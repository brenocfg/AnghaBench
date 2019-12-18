#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_fault_t ;
struct vm_fault {struct page* page; TYPE_2__* vma; scalar_t__ address; } ;
struct page {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_9__ {scalar_t__ bus_base; } ;
struct TYPE_10__ {TYPE_1__* ops; TYPE_3__ aperture; } ;
typedef  TYPE_4__ alpha_agp_info ;
struct TYPE_11__ {TYPE_4__* dev_private_data; } ;
struct TYPE_8__ {scalar_t__ vm_start; } ;
struct TYPE_7__ {unsigned long (* translate ) (TYPE_4__*,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  VM_FAULT_SIGBUS ; 
 int /*<<< orphan*/  __va (unsigned long) ; 
 TYPE_6__* agp_bridge ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 unsigned long stub1 (TYPE_4__*,scalar_t__) ; 
 struct page* virt_to_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static vm_fault_t alpha_core_agp_vm_fault(struct vm_fault *vmf)
{
	alpha_agp_info *agp = agp_bridge->dev_private_data;
	dma_addr_t dma_addr;
	unsigned long pa;
	struct page *page;

	dma_addr = vmf->address - vmf->vma->vm_start + agp->aperture.bus_base;
	pa = agp->ops->translate(agp, dma_addr);

	if (pa == (unsigned long)-EINVAL)
		return VM_FAULT_SIGBUS;	/* no translation */

	/*
	 * Get the page, inc the use count, and return it
	 */
	page = virt_to_page(__va(pa));
	get_page(page);
	vmf->page = page;
	return 0;
}