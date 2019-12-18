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
typedef  int uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
typedef  int u_int ;
struct TYPE_3__ {int intr_status; } ;
struct TYPE_4__ {TYPE_1__ hlt; } ;
struct vm_exit {scalar_t__ exitcode; TYPE_2__ u; } ;
struct vlapic_vtx {int pending_prio; struct pir_desc* pir_desc; } ;
struct vlapic {int /*<<< orphan*/  vcpuid; int /*<<< orphan*/  vm; struct LAPIC* apic_page; } ;
struct pir_desc {scalar_t__* pir; int /*<<< orphan*/  pending; } ;
struct LAPIC {int ppr; } ;

/* Variables and functions */
 int APIC_TPR_INT ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  VCPU_CTR1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ VM_EXITCODE_HLT ; 
 int VPR_PRIO_BIT (int) ; 
 scalar_t__ atomic_load_acq_long (int /*<<< orphan*/ *) ; 
 int flsl (scalar_t__) ; 
 struct vm_exit* vm_exitinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vmx_pending_intr(struct vlapic *vlapic, int *vecptr)
{
	struct vlapic_vtx *vlapic_vtx;
	struct pir_desc *pir_desc;
	struct LAPIC *lapic;
	uint64_t pending, pirval;
	uint32_t ppr, vpr;
	int i;

	/*
	 * This function is only expected to be called from the 'HLT' exit
	 * handler which does not care about the vector that is pending.
	 */
	KASSERT(vecptr == NULL, ("vmx_pending_intr: vecptr must be NULL"));

	vlapic_vtx = (struct vlapic_vtx *)vlapic;
	pir_desc = vlapic_vtx->pir_desc;

	pending = atomic_load_acq_long(&pir_desc->pending);
	if (!pending) {
		/*
		 * While a virtual interrupt may have already been
		 * processed the actual delivery maybe pending the
		 * interruptibility of the guest.  Recognize a pending
		 * interrupt by reevaluating virtual interrupts
		 * following Section 29.2.1 in the Intel SDM Volume 3.
		 */
		struct vm_exit *vmexit;
		uint8_t rvi, ppr;

		vmexit = vm_exitinfo(vlapic->vm, vlapic->vcpuid);
		KASSERT(vmexit->exitcode == VM_EXITCODE_HLT,
		    ("vmx_pending_intr: exitcode not 'HLT'"));
		rvi = vmexit->u.hlt.intr_status & APIC_TPR_INT;
		lapic = vlapic->apic_page;
		ppr = lapic->ppr & APIC_TPR_INT;
		if (rvi > ppr) {
			return (1);
		}

		return (0);
	}

	/*
	 * If there is an interrupt pending then it will be recognized only
	 * if its priority is greater than the processor priority.
	 *
	 * Special case: if the processor priority is zero then any pending
	 * interrupt will be recognized.
	 */
	lapic = vlapic->apic_page;
	ppr = lapic->ppr & APIC_TPR_INT;
	if (ppr == 0)
		return (1);

	VCPU_CTR1(vlapic->vm, vlapic->vcpuid, "HLT with non-zero PPR %d",
	    lapic->ppr);

	vpr = 0;
	for (i = 3; i >= 0; i--) {
		pirval = pir_desc->pir[i];
		if (pirval != 0) {
			vpr = (i * 64 + flsl(pirval) - 1) & APIC_TPR_INT;
			break;
		}
	}

	/*
	 * If the highest-priority pending interrupt falls short of the
	 * processor priority of this vCPU, ensure that 'pending_prio' does not
	 * have any stale bits which would preclude a higher-priority interrupt
	 * from incurring a notification later.
	 */
	if (vpr <= ppr) {
		const u_int prio_bit = VPR_PRIO_BIT(vpr);
		const u_int old = vlapic_vtx->pending_prio;

		if (old > prio_bit && (old & prio_bit) == 0) {
			vlapic_vtx->pending_prio = prio_bit;
		}
		return (0);
	}
	return (1);
}