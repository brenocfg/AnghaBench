#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
struct vmstate {int* PML4; } ;
typedef  int /*<<< orphan*/  pte ;
typedef  int /*<<< orphan*/  pdpe ;
typedef  int /*<<< orphan*/  pde ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_6__ {int /*<<< orphan*/  program; int /*<<< orphan*/  pmfd; struct vmstate* vmst; } ;
typedef  TYPE_1__ kvm_t ;
typedef  int kvaddr_t ;
typedef  int amd64_pte_t ;
typedef  int amd64_pml4e_t ;
typedef  int amd64_physaddr_t ;
typedef  int amd64_pdpe_t ;
typedef  int amd64_pde_t ;

/* Variables and functions */
 int AMD64_NBPDP ; 
 int AMD64_NBPDR ; 
 int AMD64_NPDEPG ; 
 int AMD64_NPDPEPG ; 
 int AMD64_NPML4EPG ; 
 int AMD64_NPTEPG ; 
 int AMD64_PAGE_MASK ; 
 int AMD64_PAGE_SHIFT ; 
 int AMD64_PAGE_SIZE ; 
 int AMD64_PDPMASK ; 
 int AMD64_PDPSHIFT ; 
 int AMD64_PDRMASK ; 
 int AMD64_PDRSHIFT ; 
 int AMD64_PG_1GB_FRAME ; 
 int AMD64_PG_FRAME ; 
 int AMD64_PG_PS ; 
 int AMD64_PG_PS_FRAME ; 
 int AMD64_PG_V ; 
 int AMD64_PML4SHIFT ; 
 int /*<<< orphan*/  _kvm_err (TYPE_1__*,int /*<<< orphan*/ ,char*,...) ; 
 size_t _kvm_pa2off (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _kvm_syserr (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int le64toh (int) ; 
 int pread (int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
_amd64_vatop(kvm_t *kd, kvaddr_t va, off_t *pa)
{
	struct vmstate *vm;
	amd64_physaddr_t offset;
	amd64_physaddr_t pdpe_pa;
	amd64_physaddr_t pde_pa;
	amd64_physaddr_t pte_pa;
	amd64_pml4e_t pml4e;
	amd64_pdpe_t pdpe;
	amd64_pde_t pde;
	amd64_pte_t pte;
	kvaddr_t pml4eindex;
	kvaddr_t pdpeindex;
	kvaddr_t pdeindex;
	kvaddr_t pteindex;
	amd64_physaddr_t a;
	off_t ofs;
	size_t s;

	vm = kd->vmst;
	offset = va & AMD64_PAGE_MASK;

	/*
	 * If we are initializing (kernel page table descriptor pointer
	 * not yet set) then return pa == va to avoid infinite recursion.
	 */
	if (vm->PML4 == NULL) {
		s = _kvm_pa2off(kd, va, pa);
		if (s == 0) {
			_kvm_err(kd, kd->program,
			    "_amd64_vatop: bootstrap data not in dump");
			goto invalid;
		} else
			return (AMD64_PAGE_SIZE - offset);
	}

	pml4eindex = (va >> AMD64_PML4SHIFT) & (AMD64_NPML4EPG - 1);
	pml4e = le64toh(vm->PML4[pml4eindex]);
	if ((pml4e & AMD64_PG_V) == 0) {
		_kvm_err(kd, kd->program, "_amd64_vatop: pml4e not valid");
		goto invalid;
	}

	pdpeindex = (va >> AMD64_PDPSHIFT) & (AMD64_NPDPEPG - 1);
	pdpe_pa = (pml4e & AMD64_PG_FRAME) + (pdpeindex * sizeof(amd64_pdpe_t));

	s = _kvm_pa2off(kd, pdpe_pa, &ofs);
	if (s < sizeof(pdpe)) {
		_kvm_err(kd, kd->program, "_amd64_vatop: pdpe_pa not found");
		goto invalid;
	}
	if (pread(kd->pmfd, &pdpe, sizeof(pdpe), ofs) != sizeof(pdpe)) {
		_kvm_syserr(kd, kd->program, "_amd64_vatop: read pdpe");
		goto invalid;
	}
	pdpe = le64toh(pdpe);
	if ((pdpe & AMD64_PG_V) == 0) {
		_kvm_err(kd, kd->program, "_amd64_vatop: pdpe not valid");
		goto invalid;
	}

	if (pdpe & AMD64_PG_PS) {
		/*
		 * No next-level page table; pdpe describes one 1GB page.
		 */
		a = (pdpe & AMD64_PG_1GB_FRAME) + (va & AMD64_PDPMASK);
		s = _kvm_pa2off(kd, a, pa);
		if (s == 0) {
			_kvm_err(kd, kd->program,
			    "_amd64_vatop: 1GB page address not in dump");
			goto invalid;
		} else
			return (AMD64_NBPDP - (va & AMD64_PDPMASK));
	}

	pdeindex = (va >> AMD64_PDRSHIFT) & (AMD64_NPDEPG - 1);
	pde_pa = (pdpe & AMD64_PG_FRAME) + (pdeindex * sizeof(amd64_pde_t));

	s = _kvm_pa2off(kd, pde_pa, &ofs);
	if (s < sizeof(pde)) {
		_kvm_syserr(kd, kd->program, "_amd64_vatop: pde_pa not found");
		goto invalid;
	}
	if (pread(kd->pmfd, &pde, sizeof(pde), ofs) != sizeof(pde)) {
		_kvm_syserr(kd, kd->program, "_amd64_vatop: read pde");
		goto invalid;
	}
	pde = le64toh(pde);
	if ((pde & AMD64_PG_V) == 0) {
		_kvm_err(kd, kd->program, "_amd64_vatop: pde not valid");
		goto invalid;
	}

	if (pde & AMD64_PG_PS) {
		/*
		 * No final-level page table; pde describes one 2MB page.
		 */
		a = (pde & AMD64_PG_PS_FRAME) + (va & AMD64_PDRMASK);
		s = _kvm_pa2off(kd, a, pa);
		if (s == 0) {
			_kvm_err(kd, kd->program,
			    "_amd64_vatop: 2MB page address not in dump");
			goto invalid;
		} else
			return (AMD64_NBPDR - (va & AMD64_PDRMASK));
	}

	pteindex = (va >> AMD64_PAGE_SHIFT) & (AMD64_NPTEPG - 1);
	pte_pa = (pde & AMD64_PG_FRAME) + (pteindex * sizeof(amd64_pte_t));

	s = _kvm_pa2off(kd, pte_pa, &ofs);
	if (s < sizeof(pte)) {
		_kvm_err(kd, kd->program, "_amd64_vatop: pte_pa not found");
		goto invalid;
	}
	if (pread(kd->pmfd, &pte, sizeof(pte), ofs) != sizeof(pte)) {
		_kvm_syserr(kd, kd->program, "_amd64_vatop: read");
		goto invalid;
	}
	if ((pte & AMD64_PG_V) == 0) {
		_kvm_err(kd, kd->program, "_amd64_vatop: pte not valid");
		goto invalid;
	}

	a = (pte & AMD64_PG_FRAME) + offset;
	s = _kvm_pa2off(kd, a, pa);
	if (s == 0) {
		_kvm_err(kd, kd->program, "_amd64_vatop: address not in dump");
		goto invalid;
	} else
		return (AMD64_PAGE_SIZE - offset);

invalid:
	_kvm_err(kd, 0, "invalid address (0x%jx)", (uintmax_t)va);
	return (0);
}