#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  function; } ;
struct TYPE_15__ {TYPE_5__* sie_block; TYPE_9__ ckc_timer; } ;
struct kvm_vcpu {TYPE_6__ arch; TYPE_7__* kvm; TYPE_3__* run; int /*<<< orphan*/  vcpu_id; } ;
struct TYPE_17__ {scalar_t__ has_kss; scalar_t__ has_sigpif; scalar_t__ has_siif; scalar_t__ has_ib; scalar_t__ has_cei; } ;
struct TYPE_13__ {scalar_t__ use_cmma; scalar_t__ use_pfmfi; } ;
struct TYPE_16__ {TYPE_4__ arch; } ;
struct TYPE_14__ {int eca; int gd; unsigned long sdnxo; unsigned long riccbd; int ictl; int /*<<< orphan*/  hpid; int /*<<< orphan*/  ecd; int /*<<< orphan*/  ecb2; int /*<<< orphan*/  ecb; int /*<<< orphan*/  cpuflags; } ;
struct TYPE_10__ {int /*<<< orphan*/  riccb; int /*<<< orphan*/  sdnx; } ;
struct TYPE_11__ {TYPE_1__ regs; } ;
struct TYPE_12__ {TYPE_2__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  CPUSTAT_GED ; 
 int /*<<< orphan*/  CPUSTAT_GED2 ; 
 int /*<<< orphan*/  CPUSTAT_KSS ; 
 int CPUSTAT_SM ; 
 int CPUSTAT_STOPPED ; 
 int CPUSTAT_ZARCH ; 
 int ECA_AIV ; 
 int ECA_CEI ; 
 int ECA_IB ; 
 int ECA_MVPGI ; 
 int ECA_PROTEXCI ; 
 int ECA_SIGPI ; 
 int ECA_SII ; 
 int ECA_VX ; 
 int /*<<< orphan*/  ECB2_IEP ; 
 int /*<<< orphan*/  ECB2_PFMFI ; 
 int /*<<< orphan*/  ECB_HOSTPROTINT ; 
 int /*<<< orphan*/  ECB_SRSI ; 
 int /*<<< orphan*/  ECB_TE ; 
 int /*<<< orphan*/  ECD_ETOKENF ; 
 int /*<<< orphan*/  ECD_HOSTREGMGMT ; 
 int /*<<< orphan*/  ECD_MEF ; 
 int /*<<< orphan*/  HPID_KVM ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int ICTL_ISKE ; 
 int ICTL_RRBE ; 
 int ICTL_SSKE ; 
 scalar_t__ MACHINE_HAS_ESOP ; 
 unsigned long SDNXC ; 
 int /*<<< orphan*/  VCPU_EVENT (struct kvm_vcpu*,int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_s390_idle_wakeup ; 
 int /*<<< orphan*/  kvm_s390_set_cpuflags (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_s390_vcpu_crypto_setup (struct kvm_vcpu*) ; 
 int kvm_s390_vcpu_setup_cmma (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_s390_vcpu_setup_model (struct kvm_vcpu*) ; 
 TYPE_8__ sclp ; 
 scalar_t__ test_kvm_facility (TYPE_7__*,int) ; 

int kvm_arch_vcpu_setup(struct kvm_vcpu *vcpu)
{
	int rc = 0;

	atomic_set(&vcpu->arch.sie_block->cpuflags, CPUSTAT_ZARCH |
						    CPUSTAT_SM |
						    CPUSTAT_STOPPED);

	if (test_kvm_facility(vcpu->kvm, 78))
		kvm_s390_set_cpuflags(vcpu, CPUSTAT_GED2);
	else if (test_kvm_facility(vcpu->kvm, 8))
		kvm_s390_set_cpuflags(vcpu, CPUSTAT_GED);

	kvm_s390_vcpu_setup_model(vcpu);

	/* pgste_set_pte has special handling for !MACHINE_HAS_ESOP */
	if (MACHINE_HAS_ESOP)
		vcpu->arch.sie_block->ecb |= ECB_HOSTPROTINT;
	if (test_kvm_facility(vcpu->kvm, 9))
		vcpu->arch.sie_block->ecb |= ECB_SRSI;
	if (test_kvm_facility(vcpu->kvm, 73))
		vcpu->arch.sie_block->ecb |= ECB_TE;

	if (test_kvm_facility(vcpu->kvm, 8) && vcpu->kvm->arch.use_pfmfi)
		vcpu->arch.sie_block->ecb2 |= ECB2_PFMFI;
	if (test_kvm_facility(vcpu->kvm, 130))
		vcpu->arch.sie_block->ecb2 |= ECB2_IEP;
	vcpu->arch.sie_block->eca = ECA_MVPGI | ECA_PROTEXCI;
	if (sclp.has_cei)
		vcpu->arch.sie_block->eca |= ECA_CEI;
	if (sclp.has_ib)
		vcpu->arch.sie_block->eca |= ECA_IB;
	if (sclp.has_siif)
		vcpu->arch.sie_block->eca |= ECA_SII;
	if (sclp.has_sigpif)
		vcpu->arch.sie_block->eca |= ECA_SIGPI;
	if (test_kvm_facility(vcpu->kvm, 129)) {
		vcpu->arch.sie_block->eca |= ECA_VX;
		vcpu->arch.sie_block->ecd |= ECD_HOSTREGMGMT;
	}
	if (test_kvm_facility(vcpu->kvm, 139))
		vcpu->arch.sie_block->ecd |= ECD_MEF;
	if (test_kvm_facility(vcpu->kvm, 156))
		vcpu->arch.sie_block->ecd |= ECD_ETOKENF;
	if (vcpu->arch.sie_block->gd) {
		vcpu->arch.sie_block->eca |= ECA_AIV;
		VCPU_EVENT(vcpu, 3, "AIV gisa format-%u enabled for cpu %03u",
			   vcpu->arch.sie_block->gd & 0x3, vcpu->vcpu_id);
	}
	vcpu->arch.sie_block->sdnxo = ((unsigned long) &vcpu->run->s.regs.sdnx)
					| SDNXC;
	vcpu->arch.sie_block->riccbd = (unsigned long) &vcpu->run->s.regs.riccb;

	if (sclp.has_kss)
		kvm_s390_set_cpuflags(vcpu, CPUSTAT_KSS);
	else
		vcpu->arch.sie_block->ictl |= ICTL_ISKE | ICTL_SSKE | ICTL_RRBE;

	if (vcpu->kvm->arch.use_cmma) {
		rc = kvm_s390_vcpu_setup_cmma(vcpu);
		if (rc)
			return rc;
	}
	hrtimer_init(&vcpu->arch.ckc_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	vcpu->arch.ckc_timer.function = kvm_s390_idle_wakeup;

	vcpu->arch.sie_block->hpid = HPID_KVM;

	kvm_s390_vcpu_crypto_setup(vcpu);

	return rc;
}