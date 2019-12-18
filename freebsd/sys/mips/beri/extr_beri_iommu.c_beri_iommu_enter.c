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
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
struct xdma_iommu {int /*<<< orphan*/  p; } ;
struct beri_iommu_softc {int dummy; } ;
typedef  int pt_entry_t ;
typedef  int /*<<< orphan*/ * pmap_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PTE_C (int /*<<< orphan*/ ) ; 
 int PTE_C_MASK ; 
 int /*<<< orphan*/  PTE_V ; 
 int /*<<< orphan*/  VM_MEMATTR_UNCACHEABLE ; 
 int /*<<< orphan*/  beri_iommu_invalidate (struct beri_iommu_softc*,int /*<<< orphan*/ ) ; 
 struct beri_iommu_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_dcache_wbinv_range (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int* pmap_pte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pte_test (int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
beri_iommu_enter(device_t dev, struct xdma_iommu *xio, vm_offset_t va,
    vm_paddr_t pa)
{
	struct beri_iommu_softc *sc;
	pt_entry_t opte, npte;
	pt_entry_t *pte;
	pmap_t p;

	sc = device_get_softc(dev);
	p = &xio->p;

	pte = pmap_pte(p, va);
	if (pte == NULL)
		panic("pte is NULL\n");

	/* Make pte uncacheable. */
	opte = *pte;
	npte = opte & ~PTE_C_MASK;
	npte |= PTE_C(VM_MEMATTR_UNCACHEABLE);
	*pte = npte;

	/* Write back, invalidate pte. */
	mips_dcache_wbinv_range((vm_offset_t)pte, sizeof(vm_offset_t));

	/* Invalidate the entry. */
	if (pte_test(&opte, PTE_V) && opte != npte)
		beri_iommu_invalidate(sc, va);

	return (0);
}