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
struct kvmppc_vcore {int /*<<< orphan*/  vtb; int /*<<< orphan*/  dpdes; } ;
struct TYPE_3__ {int /*<<< orphan*/  sprg3; int /*<<< orphan*/  sprg2; int /*<<< orphan*/  sprg1; int /*<<< orphan*/  sprg0; int /*<<< orphan*/  srr1; int /*<<< orphan*/  srr0; } ;
struct TYPE_4__ {int /*<<< orphan*/  ppr; int /*<<< orphan*/  cfar; int /*<<< orphan*/  pid; TYPE_1__ shregs; int /*<<< orphan*/  emul_inst; int /*<<< orphan*/  fault_gpa; int /*<<< orphan*/  fault_dsisr; int /*<<< orphan*/  fault_dar; int /*<<< orphan*/  ic; int /*<<< orphan*/  spurr; int /*<<< orphan*/  purr; int /*<<< orphan*/  hfscr; struct kvmppc_vcore* vcore; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct hv_guest_state {int /*<<< orphan*/  ppr; int /*<<< orphan*/  cfar; int /*<<< orphan*/  pidr; int /*<<< orphan*/ * sprg; int /*<<< orphan*/  srr1; int /*<<< orphan*/  srr0; int /*<<< orphan*/  heir; int /*<<< orphan*/  asdr; int /*<<< orphan*/  hdsisr; int /*<<< orphan*/  hdar; int /*<<< orphan*/  vtb; int /*<<< orphan*/  ic; int /*<<< orphan*/  spurr; int /*<<< orphan*/  purr; int /*<<< orphan*/  hfscr; int /*<<< orphan*/  dpdes; } ;

/* Variables and functions */

void kvmhv_restore_hv_return_state(struct kvm_vcpu *vcpu,
				   struct hv_guest_state *hr)
{
	struct kvmppc_vcore *vc = vcpu->arch.vcore;

	vc->dpdes = hr->dpdes;
	vcpu->arch.hfscr = hr->hfscr;
	vcpu->arch.purr = hr->purr;
	vcpu->arch.spurr = hr->spurr;
	vcpu->arch.ic = hr->ic;
	vc->vtb = hr->vtb;
	vcpu->arch.fault_dar = hr->hdar;
	vcpu->arch.fault_dsisr = hr->hdsisr;
	vcpu->arch.fault_gpa = hr->asdr;
	vcpu->arch.emul_inst = hr->heir;
	vcpu->arch.shregs.srr0 = hr->srr0;
	vcpu->arch.shregs.srr1 = hr->srr1;
	vcpu->arch.shregs.sprg0 = hr->sprg[0];
	vcpu->arch.shregs.sprg1 = hr->sprg[1];
	vcpu->arch.shregs.sprg2 = hr->sprg[2];
	vcpu->arch.shregs.sprg3 = hr->sprg[3];
	vcpu->arch.pid = hr->pidr;
	vcpu->arch.cfar = hr->cfar;
	vcpu->arch.ppr = hr->ppr;
}