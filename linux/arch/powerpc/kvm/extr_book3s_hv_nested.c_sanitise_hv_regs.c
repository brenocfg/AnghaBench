#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int hfscr; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct hv_guest_state {int hfscr; int ciabr; int /*<<< orphan*/  dawrx0; } ;

/* Variables and functions */
 int CIABR_PRIV ; 
 int CIABR_PRIV_HYPER ; 
 int /*<<< orphan*/  DAWRX_HYP ; 
 int HFSCR_INTR_CAUSE ; 

__attribute__((used)) static void sanitise_hv_regs(struct kvm_vcpu *vcpu, struct hv_guest_state *hr)
{
	/*
	 * Don't let L1 enable features for L2 which we've disabled for L1,
	 * but preserve the interrupt cause field.
	 */
	hr->hfscr &= (HFSCR_INTR_CAUSE | vcpu->arch.hfscr);

	/* Don't let data address watchpoint match in hypervisor state */
	hr->dawrx0 &= ~DAWRX_HYP;

	/* Don't let completed instruction address breakpt match in HV state */
	if ((hr->ciabr & CIABR_PRIV) == CIABR_PRIV_HYPER)
		hr->ciabr &= ~CIABR_PRIV;
}