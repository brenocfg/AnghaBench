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
typedef  int /*<<< orphan*/  u64 ;
struct kvm_s390_sie_block {int icptcode; void* gcr; int fpf; int ihcpu; int /*<<< orphan*/  pp; int /*<<< orphan*/  gg15; int /*<<< orphan*/  gg14; int /*<<< orphan*/  gpsw; int /*<<< orphan*/  todpr; int /*<<< orphan*/  ckc; int /*<<< orphan*/  cputm; int /*<<< orphan*/  gbea; int /*<<< orphan*/  ipb; int /*<<< orphan*/  ipa; int /*<<< orphan*/  icptstatus; } ;
struct vsie_page {struct kvm_s390_sie_block* scb_o; struct kvm_s390_sie_block scb_s; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;

/* Variables and functions */
 int FPF_BPBC ; 
#define  ICPT_EXTINT 131 
#define  ICPT_INSTPROGI 130 
#define  ICPT_PARTEXEC 129 
#define  ICPT_PROGI 128 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 scalar_t__ test_kvm_facility (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void unshadow_scb(struct kvm_vcpu *vcpu, struct vsie_page *vsie_page)
{
	struct kvm_s390_sie_block *scb_s = &vsie_page->scb_s;
	struct kvm_s390_sie_block *scb_o = vsie_page->scb_o;

	/* interception */
	scb_o->icptcode = scb_s->icptcode;
	scb_o->icptstatus = scb_s->icptstatus;
	scb_o->ipa = scb_s->ipa;
	scb_o->ipb = scb_s->ipb;
	scb_o->gbea = scb_s->gbea;

	/* timer */
	scb_o->cputm = scb_s->cputm;
	scb_o->ckc = scb_s->ckc;
	scb_o->todpr = scb_s->todpr;

	/* guest state */
	scb_o->gpsw = scb_s->gpsw;
	scb_o->gg14 = scb_s->gg14;
	scb_o->gg15 = scb_s->gg15;
	memcpy(scb_o->gcr, scb_s->gcr, 128);
	scb_o->pp = scb_s->pp;

	/* branch prediction */
	if (test_kvm_facility(vcpu->kvm, 82)) {
		scb_o->fpf &= ~FPF_BPBC;
		scb_o->fpf |= scb_s->fpf & FPF_BPBC;
	}

	/* interrupt intercept */
	switch (scb_s->icptcode) {
	case ICPT_PROGI:
	case ICPT_INSTPROGI:
	case ICPT_EXTINT:
		memcpy((void *)((u64)scb_o + 0xc0),
		       (void *)((u64)scb_s + 0xc0), 0xf0 - 0xc0);
		break;
	case ICPT_PARTEXEC:
		/* MVPG only */
		memcpy((void *)((u64)scb_o + 0xc0),
		       (void *)((u64)scb_s + 0xc0), 0xd0 - 0xc0);
		break;
	}

	if (scb_s->ihcpu != 0xffffU)
		scb_o->ihcpu = scb_s->ihcpu;
}