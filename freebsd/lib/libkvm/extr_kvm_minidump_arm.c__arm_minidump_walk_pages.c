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
typedef  int u_long ;
struct TYPE_7__ {int ptesize; int kernbase; scalar_t__ mmuformat; } ;
struct vmstate {TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  kvm_walk_pages_cb_t ;
struct TYPE_8__ {struct vmstate* vmst; } ;
typedef  TYPE_2__ kvm_t ;
typedef  int arm_pt_entry_t ;

/* Variables and functions */
 int ARM_L2_L_FRAME ; 
 int ARM_L2_L_OFFSET ; 
 int ARM_L2_S_FRAME ; 
 int ARM_L2_TYPE_INV ; 
 int ARM_L2_TYPE_L ; 
 int ARM_L2_TYPE_MASK ; 
 int ARM_L2_TYPE_T ; 
 int ARM_PAGE_SHIFT ; 
 int /*<<< orphan*/  ARM_PAGE_SIZE ; 
 scalar_t__ MINIDUMP_MMU_FORMAT_V4 ; 
 int /*<<< orphan*/  _arm_entry_to_prot (TYPE_2__*,int) ; 
 int _arm_pte_get (TYPE_2__*,int) ; 
 int /*<<< orphan*/  _kvm_visit_cb (TYPE_2__*,int /*<<< orphan*/ *,void*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
_arm_minidump_walk_pages(kvm_t *kd, kvm_walk_pages_cb_t *cb, void *arg)
{
	struct vmstate *vm = kd->vmst;
	u_long nptes = vm->hdr.ptesize / sizeof(arm_pt_entry_t);
	u_long dva, pa, pteindex, va;

	for (pteindex = 0; pteindex < nptes; pteindex++) {
		arm_pt_entry_t pte = _arm_pte_get(kd, pteindex);

		if ((pte & ARM_L2_TYPE_MASK) == ARM_L2_TYPE_INV)
			continue;

		va = vm->hdr.kernbase + (pteindex << ARM_PAGE_SHIFT);
		if ((pte & ARM_L2_TYPE_MASK) == ARM_L2_TYPE_L) {
			/* 64K page */
			pa = (pte & ARM_L2_L_FRAME) +
			    (va & ARM_L2_L_OFFSET & ARM_L2_S_FRAME);
		} else {
			if (vm->hdr.mmuformat == MINIDUMP_MMU_FORMAT_V4 &&
			    (pte & ARM_L2_TYPE_MASK) == ARM_L2_TYPE_T) {
				continue;
			}
			/* 4K page */
			pa = pte & ARM_L2_S_FRAME;
		}

		dva = 0; /* no direct map on this platform */
		if (!_kvm_visit_cb(kd, cb, arg, pa, va, dva,
		    _arm_entry_to_prot(kd, pte), ARM_PAGE_SIZE, 0))
			return (0);
	}
	return (1);
}