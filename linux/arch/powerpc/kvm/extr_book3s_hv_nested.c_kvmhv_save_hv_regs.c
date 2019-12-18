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
struct kvmppc_vcore {int pcr; int /*<<< orphan*/  vtb; int /*<<< orphan*/  tb_offset; int /*<<< orphan*/  dpdes; } ;
struct TYPE_3__ {int /*<<< orphan*/  sprg3; int /*<<< orphan*/  sprg2; int /*<<< orphan*/  sprg1; int /*<<< orphan*/  sprg0; int /*<<< orphan*/  srr1; int /*<<< orphan*/  srr0; } ;
struct TYPE_4__ {int /*<<< orphan*/  ppr; int /*<<< orphan*/  cfar; int /*<<< orphan*/  pid; TYPE_1__ shregs; int /*<<< orphan*/  ic; int /*<<< orphan*/  spurr; int /*<<< orphan*/  purr; int /*<<< orphan*/  ciabr; int /*<<< orphan*/  dawrx; int /*<<< orphan*/  dawr; int /*<<< orphan*/  hfscr; struct kvmppc_vcore* vcore; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct hv_guest_state {int pcr; int /*<<< orphan*/  ppr; int /*<<< orphan*/  cfar; int /*<<< orphan*/  pidr; int /*<<< orphan*/ * sprg; int /*<<< orphan*/  srr1; int /*<<< orphan*/  srr0; int /*<<< orphan*/  vtb; int /*<<< orphan*/  ic; int /*<<< orphan*/  spurr; int /*<<< orphan*/  purr; int /*<<< orphan*/  ciabr; int /*<<< orphan*/  dawrx0; int /*<<< orphan*/  dawr0; int /*<<< orphan*/  tb_offset; int /*<<< orphan*/  hfscr; int /*<<< orphan*/  dpdes; } ;

/* Variables and functions */
 int PCR_MASK ; 

void kvmhv_save_hv_regs(struct kvm_vcpu *vcpu, struct hv_guest_state *hr)
{
	struct kvmppc_vcore *vc = vcpu->arch.vcore;

	hr->pcr = vc->pcr | PCR_MASK;
	hr->dpdes = vc->dpdes;
	hr->hfscr = vcpu->arch.hfscr;
	hr->tb_offset = vc->tb_offset;
	hr->dawr0 = vcpu->arch.dawr;
	hr->dawrx0 = vcpu->arch.dawrx;
	hr->ciabr = vcpu->arch.ciabr;
	hr->purr = vcpu->arch.purr;
	hr->spurr = vcpu->arch.spurr;
	hr->ic = vcpu->arch.ic;
	hr->vtb = vc->vtb;
	hr->srr0 = vcpu->arch.shregs.srr0;
	hr->srr1 = vcpu->arch.shregs.srr1;
	hr->sprg[0] = vcpu->arch.shregs.sprg0;
	hr->sprg[1] = vcpu->arch.shregs.sprg1;
	hr->sprg[2] = vcpu->arch.shregs.sprg2;
	hr->sprg[3] = vcpu->arch.shregs.sprg3;
	hr->pidr = vcpu->arch.pid;
	hr->cfar = vcpu->arch.cfar;
	hr->ppr = vcpu->arch.ppr;
}