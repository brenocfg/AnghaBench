#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int u_long ;
struct TYPE_11__ {int kernbase; int ptesize; } ;
struct vmstate {int pte_size; TYPE_2__ hdr; } ;
typedef  int /*<<< orphan*/  pte64 ;
typedef  int /*<<< orphan*/  pte32 ;
typedef  int off_t ;
typedef  int mips_physaddr_t ;
typedef  int mips64_pte_t ;
typedef  int mips32_pte_t ;
struct TYPE_10__ {scalar_t__* e_ident; } ;
struct TYPE_12__ {int /*<<< orphan*/  program; TYPE_1__ nlehdr; struct vmstate* vmst; } ;
typedef  TYPE_3__ kvm_t ;
typedef  int kvaddr_t ;

/* Variables and functions */
 size_t EI_CLASS ; 
 scalar_t__ ELFCLASS64 ; 
 scalar_t__ ISALIVE (TYPE_3__*) ; 
 int MIPS32_KSEG0_END ; 
 int MIPS32_KSEG0_START ; 
 int MIPS32_KSEG1_END ; 
 int MIPS32_KSEG1_START ; 
 int MIPS32_PTE_TO_PA (int) ; 
 int MIPS64_KSEG0_END ; 
 int MIPS64_KSEG0_START ; 
 int MIPS64_KSEG1_END ; 
 int MIPS64_KSEG1_START ; 
 int MIPS64_PTE_TO_PA (int) ; 
 int MIPS_KSEG0_PHYS_MASK ; 
 int MIPS_PAGE_MASK ; 
 int MIPS_PAGE_SHIFT ; 
 int MIPS_PAGE_SIZE ; 
 int MIPS_PTE_V ; 
 int MIPS_XKPHYS_END ; 
 int MIPS_XKPHYS_PHYS_MASK ; 
 int MIPS_XKPHYS_START ; 
 int /*<<< orphan*/  _kvm_err (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 int _kvm_pt_find (TYPE_3__*,int,int) ; 
 int _mips32_pte_get (TYPE_3__*,int) ; 
 int _mips64_pte_get (TYPE_3__*,int) ; 

__attribute__((used)) static int
_mips_minidump_kvatop(kvm_t *kd, kvaddr_t va, off_t *pa)
{
	struct vmstate *vm;
	mips_physaddr_t offset, a;
	kvaddr_t pteindex;
	u_long valid;
	off_t ofs;
	mips32_pte_t pte32;
	mips64_pte_t pte64;

	if (ISALIVE(kd)) {
		_kvm_err(kd, 0, "_mips_minidump_kvatop called in live kernel!");
		return (0);
	}

	offset = va & MIPS_PAGE_MASK;
	/* Operate with page-aligned address */
	va &= ~MIPS_PAGE_MASK;

	vm = kd->vmst;
	if (kd->nlehdr.e_ident[EI_CLASS] == ELFCLASS64) {
		if (va >= MIPS_XKPHYS_START && va < MIPS_XKPHYS_END) {
			a = va & MIPS_XKPHYS_PHYS_MASK;
			goto found;
		}
		if (va >= MIPS64_KSEG0_START && va < MIPS64_KSEG0_END) {
			a = va & MIPS_KSEG0_PHYS_MASK;
			goto found;
		}
		if (va >= MIPS64_KSEG1_START && va < MIPS64_KSEG1_END) {
			a = va & MIPS_KSEG0_PHYS_MASK;
			goto found;
		}
	} else {
		if (va >= MIPS32_KSEG0_START && va < MIPS32_KSEG0_END) {
			a = va & MIPS_KSEG0_PHYS_MASK;
			goto found;
		}
		if (va >= MIPS32_KSEG1_START && va < MIPS32_KSEG1_END) {
			a = va & MIPS_KSEG0_PHYS_MASK;
			goto found;
		}
	}
	if (va >= vm->hdr.kernbase) {
		pteindex = (va - vm->hdr.kernbase) >> MIPS_PAGE_SHIFT;
		if (vm->pte_size == 64) {
			valid = pteindex < vm->hdr.ptesize / sizeof(pte64);
			if (pteindex >= vm->hdr.ptesize / sizeof(pte64))
				goto invalid;
			pte64 = _mips64_pte_get(kd, pteindex);
			valid = pte64 & MIPS_PTE_V;
			if (valid)
				a = MIPS64_PTE_TO_PA(pte64);
		} else {
			if (pteindex >= vm->hdr.ptesize / sizeof(pte32))
				goto invalid;
			pte32 = _mips32_pte_get(kd, pteindex);
			valid = pte32 & MIPS_PTE_V;
			if (valid)
				a = MIPS32_PTE_TO_PA(pte32);
		}
		if (!valid) {
			_kvm_err(kd, kd->program, "_mips_minidump_kvatop: pte "
			    "not valid");
			goto invalid;
		}
	} else {
		_kvm_err(kd, kd->program, "_mips_minidump_kvatop: virtual "
		    "address 0x%jx not minidumped", (uintmax_t)va);
		return (0);
	}

found:
	ofs = _kvm_pt_find(kd, a, MIPS_PAGE_SIZE);
	if (ofs == -1) {
		_kvm_err(kd, kd->program, "_mips_minidump_kvatop: physical "
		    "address 0x%jx not in minidump", (uintmax_t)a);
		goto invalid;
	}

	*pa = ofs + offset;
	return (MIPS_PAGE_SIZE - offset);


invalid:
	_kvm_err(kd, 0, "invalid address (0x%jx)", (uintmax_t)va);
	return (0);
}