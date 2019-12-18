#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
struct TYPE_7__ {int kernbase; int pmapsize; int dmapbase; int dmapend; } ;
struct vmstate {TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  pde ;
typedef  int off_t ;
struct TYPE_8__ {int /*<<< orphan*/  program; int /*<<< orphan*/  pmfd; struct vmstate* vmst; } ;
typedef  TYPE_2__ kvm_t ;
typedef  int kvaddr_t ;
typedef  int amd64_pte_t ;
typedef  int amd64_physaddr_t ;
typedef  int amd64_pde_t ;

/* Variables and functions */
 int AMD64_NPTEPG ; 
 int AMD64_PAGE_MASK ; 
 int AMD64_PAGE_SHIFT ; 
 scalar_t__ AMD64_PAGE_SIZE ; 
 int AMD64_PDRMASK ; 
 int AMD64_PDRSHIFT ; 
 int AMD64_PG_FRAME ; 
 int AMD64_PG_PS ; 
 int AMD64_PG_PS_FRAME ; 
 int AMD64_PG_V ; 
 int _amd64_pde_get (TYPE_2__*,int) ; 
 int /*<<< orphan*/  _kvm_err (TYPE_2__*,int /*<<< orphan*/ ,char*,...) ; 
 int _kvm_pt_find (TYPE_2__*,int,scalar_t__) ; 
 int le64toh (int) ; 
 scalar_t__ pread (int /*<<< orphan*/ ,int**,scalar_t__,int) ; 

__attribute__((used)) static int
_amd64_minidump_vatop(kvm_t *kd, kvaddr_t va, off_t *pa)
{
	amd64_pte_t pt[AMD64_NPTEPG];
	struct vmstate *vm;
	amd64_physaddr_t offset;
	amd64_pde_t pde;
	amd64_pte_t pte;
	kvaddr_t pteindex;
	kvaddr_t pdeindex;
	amd64_physaddr_t a;
	off_t ofs;

	vm = kd->vmst;
	offset = va & AMD64_PAGE_MASK;

	if (va >= vm->hdr.kernbase) {
		pdeindex = (va - vm->hdr.kernbase) >> AMD64_PDRSHIFT;
		if (pdeindex >= vm->hdr.pmapsize / sizeof(pde))
			goto invalid;
		pde = _amd64_pde_get(kd, pdeindex);
		if ((pde & AMD64_PG_V) == 0) {
			_kvm_err(kd, kd->program,
			    "_amd64_minidump_vatop: pde not valid");
			goto invalid;
		}
		if ((pde & AMD64_PG_PS) == 0) {
			a = pde & AMD64_PG_FRAME;
			/* TODO: Just read the single PTE */
			ofs = _kvm_pt_find(kd, a, AMD64_PAGE_SIZE);
			if (ofs == -1) {
				_kvm_err(kd, kd->program,
				    "cannot find page table entry for %ju",
				    (uintmax_t)a);
				goto invalid;
			}
			if (pread(kd->pmfd, &pt, AMD64_PAGE_SIZE, ofs) !=
			    AMD64_PAGE_SIZE) {
				_kvm_err(kd, kd->program,
				    "cannot read page table entry for %ju",
				    (uintmax_t)a);
				goto invalid;
			}
			pteindex = (va >> AMD64_PAGE_SHIFT) &
			    (AMD64_NPTEPG - 1);
			pte = le64toh(pt[pteindex]);
			if ((pte & AMD64_PG_V) == 0) {
				_kvm_err(kd, kd->program,
				    "_amd64_minidump_vatop: pte not valid");
				goto invalid;
			}
			a = pte & AMD64_PG_FRAME;
		} else {
			a = pde & AMD64_PG_PS_FRAME;
			a += (va & AMD64_PDRMASK) ^ offset;
		}
		ofs = _kvm_pt_find(kd, a, AMD64_PAGE_SIZE);
		if (ofs == -1) {
			_kvm_err(kd, kd->program,
	    "_amd64_minidump_vatop: physical address 0x%jx not in minidump",
			    (uintmax_t)a);
			goto invalid;
		}
		*pa = ofs + offset;
		return (AMD64_PAGE_SIZE - offset);
	} else if (va >= vm->hdr.dmapbase && va < vm->hdr.dmapend) {
		a = (va - vm->hdr.dmapbase) & ~AMD64_PAGE_MASK;
		ofs = _kvm_pt_find(kd, a, AMD64_PAGE_SIZE);
		if (ofs == -1) {
			_kvm_err(kd, kd->program,
	    "_amd64_minidump_vatop: direct map address 0x%jx not in minidump",
			    (uintmax_t)va);
			goto invalid;
		}
		*pa = ofs + offset;
		return (AMD64_PAGE_SIZE - offset);
	} else {
		_kvm_err(kd, kd->program,
	    "_amd64_minidump_vatop: virtual address 0x%jx not minidumped",
		    (uintmax_t)va);
		goto invalid;
	}

invalid:
	_kvm_err(kd, 0, "invalid address (0x%jx)", (uintmax_t)va);
	return (0);
}