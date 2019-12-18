#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
struct TYPE_8__ {scalar_t__ kernbase; int ptesize; scalar_t__ mmuformat; } ;
struct vmstate {TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  pte ;
typedef  int off_t ;
struct TYPE_9__ {int /*<<< orphan*/  program; struct vmstate* vmst; } ;
typedef  TYPE_2__ kvm_t ;
typedef  scalar_t__ kvaddr_t ;
typedef  scalar_t__ arm_pt_entry_t ;
typedef  int arm_physaddr_t ;

/* Variables and functions */
 scalar_t__ ARM_L2_L_FRAME ; 
 scalar_t__ ARM_L2_L_OFFSET ; 
 scalar_t__ ARM_L2_S_FRAME ; 
 scalar_t__ ARM_L2_S_OFFSET ; 
 scalar_t__ ARM_L2_TYPE_INV ; 
 scalar_t__ ARM_L2_TYPE_L ; 
 scalar_t__ ARM_L2_TYPE_MASK ; 
 scalar_t__ ARM_L2_TYPE_T ; 
 scalar_t__ ARM_PAGE_SHIFT ; 
 int ARM_PAGE_SIZE ; 
 scalar_t__ ISALIVE (TYPE_2__*) ; 
 scalar_t__ MINIDUMP_MMU_FORMAT_V4 ; 
 scalar_t__ _arm_pte_get (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  _kvm_err (TYPE_2__*,int /*<<< orphan*/ ,char*,...) ; 
 int _kvm_pt_find (TYPE_2__*,int,int) ; 

__attribute__((used)) static int
_arm_minidump_kvatop(kvm_t *kd, kvaddr_t va, off_t *pa)
{
	struct vmstate *vm;
	arm_pt_entry_t pte;
	arm_physaddr_t offset, a;
	kvaddr_t pteindex;
	off_t ofs;

	if (ISALIVE(kd)) {
		_kvm_err(kd, 0, "_arm_minidump_kvatop called in live kernel!");
		return (0);
	}

	vm = kd->vmst;

	if (va >= vm->hdr.kernbase) {
		pteindex = (va - vm->hdr.kernbase) >> ARM_PAGE_SHIFT;
		if (pteindex >= vm->hdr.ptesize / sizeof(pte))
			goto invalid;
		pte = _arm_pte_get(kd, pteindex);
		if ((pte & ARM_L2_TYPE_MASK) == ARM_L2_TYPE_INV) {
			_kvm_err(kd, kd->program,
			    "_arm_minidump_kvatop: pte not valid");
			goto invalid;
		}
		if ((pte & ARM_L2_TYPE_MASK) == ARM_L2_TYPE_L) {
			/* 64K page -> convert to be like 4K page */
			offset = va & ARM_L2_S_OFFSET;
			a = (pte & ARM_L2_L_FRAME) +
			    (va & ARM_L2_L_OFFSET & ARM_L2_S_FRAME);
		} else {
			if (kd->vmst->hdr.mmuformat == MINIDUMP_MMU_FORMAT_V4 &&
			    (pte & ARM_L2_TYPE_MASK) == ARM_L2_TYPE_T) {
				_kvm_err(kd, kd->program,
				    "_arm_minidump_kvatop: pte not supported");
				goto invalid;
			}
			/* 4K page */
			offset = va & ARM_L2_S_OFFSET;
			a = pte & ARM_L2_S_FRAME;
		}

		ofs = _kvm_pt_find(kd, a, ARM_PAGE_SIZE);
		if (ofs == -1) {
			_kvm_err(kd, kd->program, "_arm_minidump_kvatop: "
			    "physical address 0x%jx not in minidump",
			    (uintmax_t)a);
			goto invalid;
		}

		*pa = ofs + offset;
		return (ARM_PAGE_SIZE - offset);
	} else
		_kvm_err(kd, kd->program, "_arm_minidump_kvatop: virtual "
		    "address 0x%jx not minidumped", (uintmax_t)va);

invalid:
	_kvm_err(kd, 0, "invalid address (0x%jx)", (uintmax_t)va);
	return (0);
}