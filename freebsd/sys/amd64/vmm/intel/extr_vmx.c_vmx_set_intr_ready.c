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
typedef  unsigned long uint64_t ;
typedef  int u_int ;
struct vlapic_vtx {int pending_prio; struct pir_desc* pir_desc; } ;
struct vlapic {int /*<<< orphan*/  vcpuid; int /*<<< orphan*/  vm; } ;
struct pir_desc {int /*<<< orphan*/  pending; int /*<<< orphan*/ * pir; } ;

/* Variables and functions */
 int APIC_TPR_INT ; 
 int /*<<< orphan*/  VMX_CTR_PIR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pir_desc*,int,int,int,char*) ; 
 int VPR_PRIO_BIT (int) ; 
 scalar_t__ atomic_cmpset_long (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atomic_set_int (int*,int const) ; 
 int /*<<< orphan*/  atomic_set_long (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
vmx_set_intr_ready(struct vlapic *vlapic, int vector, bool level)
{
	struct vlapic_vtx *vlapic_vtx;
	struct pir_desc *pir_desc;
	uint64_t mask;
	int idx, notify = 0;

	vlapic_vtx = (struct vlapic_vtx *)vlapic;
	pir_desc = vlapic_vtx->pir_desc;

	/*
	 * Keep track of interrupt requests in the PIR descriptor. This is
	 * because the virtual APIC page pointed to by the VMCS cannot be
	 * modified if the vcpu is running.
	 */
	idx = vector / 64;
	mask = 1UL << (vector % 64);
	atomic_set_long(&pir_desc->pir[idx], mask);

	/*
	 * A notification is required whenever the 'pending' bit makes a
	 * transition from 0->1.
	 *
	 * Even if the 'pending' bit is already asserted, notification about
	 * the incoming interrupt may still be necessary.  For example, if a
	 * vCPU is HLTed with a high PPR, a low priority interrupt would cause
	 * the 0->1 'pending' transition with a notification, but the vCPU
	 * would ignore the interrupt for the time being.  The same vCPU would
	 * need to then be notified if a high-priority interrupt arrived which
	 * satisfied the PPR.
	 *
	 * The priorities of interrupts injected while 'pending' is asserted
	 * are tracked in a custom bitfield 'pending_prio'.  Should the
	 * to-be-injected interrupt exceed the priorities already present, the
	 * notification is sent.  The priorities recorded in 'pending_prio' are
	 * cleared whenever the 'pending' bit makes another 0->1 transition.
	 */
	if (atomic_cmpset_long(&pir_desc->pending, 0, 1) != 0) {
		notify = 1;
		vlapic_vtx->pending_prio = 0;
	} else {
		const u_int old_prio = vlapic_vtx->pending_prio;
		const u_int prio_bit = VPR_PRIO_BIT(vector & APIC_TPR_INT);

		if ((old_prio & prio_bit) == 0 && prio_bit > old_prio) {
			atomic_set_int(&vlapic_vtx->pending_prio, prio_bit);
			notify = 1;
		}
	}

	VMX_CTR_PIR(vlapic->vm, vlapic->vcpuid, pir_desc, notify, vector,
	    level, "vmx_set_intr_ready");
	return (notify);
}