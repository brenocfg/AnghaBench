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
struct xdma_iommu {int /*<<< orphan*/  vmem; } ;
struct TYPE_3__ {struct xdma_iommu xio; } ;
typedef  TYPE_1__ xdma_channel_t ;
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  int vm_paddr_t ;
typedef  int vm_offset_t ;

/* Variables and functions */
 int M_FIRSTFIT ; 
 int M_NOWAIT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  roundup2 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ vmem_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  xdma_iommu_enter (struct xdma_iommu*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
xdma_iommu_add_entry(xdma_channel_t *xchan, vm_offset_t *va,
    vm_paddr_t pa, vm_size_t size, vm_prot_t prot)
{
	struct xdma_iommu *xio;
	vm_offset_t addr;

	size = roundup2(size, PAGE_SIZE);
	xio = &xchan->xio;

	if (vmem_alloc(xio->vmem, size,
	    M_FIRSTFIT | M_NOWAIT, &addr)) {
		panic("Could not allocate virtual address.\n");
	}

	addr |= pa & (PAGE_SIZE - 1);

	if (va)
		*va = addr;

	xdma_iommu_enter(xio, addr, pa, size, prot);
}