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
struct vmstate {scalar_t__ PTD; } ;
typedef  int /*<<< orphan*/  pte ;
typedef  int /*<<< orphan*/  pde ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_6__ {int /*<<< orphan*/  program; int /*<<< orphan*/  pmfd; struct vmstate* vmst; } ;
typedef  TYPE_1__ kvm_t ;
typedef  size_t kvaddr_t ;
typedef  int i386_pte_pae_t ;
typedef  int i386_physaddr_pae_t ;
typedef  int i386_pde_pae_t ;

/* Variables and functions */
 int I386_NBPDR_PAE ; 
 int I386_NPTEPG_PAE ; 
 size_t I386_PAGE_MASK ; 
 size_t I386_PAGE_PS_MASK_PAE ; 
 size_t I386_PAGE_SHIFT ; 
 int I386_PAGE_SIZE ; 
 size_t I386_PDRSHIFT_PAE ; 
 int I386_PG_FRAME_PAE ; 
 int I386_PG_PS ; 
 int I386_PG_PS_FRAME_PAE ; 
 int I386_PG_V ; 
 int /*<<< orphan*/  _kvm_err (TYPE_1__*,int /*<<< orphan*/ ,char*,...) ; 
 size_t _kvm_pa2off (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _kvm_syserr (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int le64toh (int) ; 
 int pread (int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
_i386_vatop_pae(kvm_t *kd, kvaddr_t va, off_t *pa)
{
	struct vmstate *vm;
	i386_physaddr_pae_t offset;
	i386_physaddr_pae_t pte_pa;
	i386_pde_pae_t pde;
	i386_pte_pae_t pte;
	kvaddr_t pdeindex;
	kvaddr_t pteindex;
	size_t s;
	i386_physaddr_pae_t a;
	off_t ofs;
	i386_pde_pae_t *PTD;

	vm = kd->vmst;
	PTD = (i386_pde_pae_t *)vm->PTD;
	offset = va & I386_PAGE_MASK;

	/*
	 * If we are initializing (kernel page table descriptor pointer
	 * not yet set) then return pa == va to avoid infinite recursion.
	 */
	if (PTD == NULL) {
		s = _kvm_pa2off(kd, va, pa);
		if (s == 0) {
			_kvm_err(kd, kd->program,
			    "_i386_vatop_pae: bootstrap data not in dump");
			goto invalid;
		} else
			return (I386_PAGE_SIZE - offset);
	}

	pdeindex = va >> I386_PDRSHIFT_PAE;
	pde = le64toh(PTD[pdeindex]);
	if ((pde & I386_PG_V) == 0) {
		_kvm_err(kd, kd->program, "_kvm_kvatop_pae: pde not valid");
		goto invalid;
	}

	if (pde & I386_PG_PS) {
		/*
		 * No second-level page table; ptd describes one 2MB
		 * page.  (We assume that the kernel wouldn't set
		 * PG_PS without enabling it cr0).
		 */
		offset = va & I386_PAGE_PS_MASK_PAE;
		a = (pde & I386_PG_PS_FRAME_PAE) + offset;
		s = _kvm_pa2off(kd, a, pa);
		if (s == 0) {
			_kvm_err(kd, kd->program,
			    "_i386_vatop: 2MB page address not in dump");
			goto invalid;
		}
		return (I386_NBPDR_PAE - offset);
	}

	pteindex = (va >> I386_PAGE_SHIFT) & (I386_NPTEPG_PAE - 1);
	pte_pa = (pde & I386_PG_FRAME_PAE) + (pteindex * sizeof(pde));

	s = _kvm_pa2off(kd, pte_pa, &ofs);
	if (s < sizeof(pte)) {
		_kvm_err(kd, kd->program, "_i386_vatop_pae: pdpe_pa not found");
		goto invalid;
	}

	/* XXX This has to be a physical address read, kvm_read is virtual */
	if (pread(kd->pmfd, &pte, sizeof(pte), ofs) != sizeof(pte)) {
		_kvm_syserr(kd, kd->program, "_i386_vatop_pae: read");
		goto invalid;
	}
	pte = le64toh(pte);
	if ((pte & I386_PG_V) == 0) {
		_kvm_err(kd, kd->program, "_i386_vatop_pae: pte not valid");
		goto invalid;
	}

	a = (pte & I386_PG_FRAME_PAE) + offset;
	s = _kvm_pa2off(kd, a, pa);
	if (s == 0) {
		_kvm_err(kd, kd->program,
		    "_i386_vatop_pae: address not in dump");
		goto invalid;
	} else
		return (I386_PAGE_SIZE - offset);

invalid:
	_kvm_err(kd, 0, "invalid address (0x%jx)", (uintmax_t)va);
	return (0);
}