#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ulong ;
struct TYPE_5__ {int nip; } ;
struct TYPE_6__ {int epr_flags; int ivpr; int* ivor; scalar_t__ irq_type; int epcr; int pending_exceptions; int /*<<< orphan*/  queued_dear; int /*<<< orphan*/  queued_esr; TYPE_2__ regs; TYPE_1__* shared; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;
typedef  enum int_class { ____Placeholder_int_class } int_class ;
struct TYPE_4__ {int critical; int msr; } ;

/* Variables and functions */
 int BOOKE_IRQMASK_CE ; 
 int BOOKE_IRQMASK_EE ; 
#define  BOOKE_IRQPRIO_ALIGNMENT 154 
#define  BOOKE_IRQPRIO_ALTIVEC_ASSIST 153 
#define  BOOKE_IRQPRIO_ALTIVEC_UNAVAIL 152 
#define  BOOKE_IRQPRIO_AP_UNAVAIL 151 
#define  BOOKE_IRQPRIO_CRITICAL 150 
#define  BOOKE_IRQPRIO_DATA_STORAGE 149 
#define  BOOKE_IRQPRIO_DBELL 148 
#define  BOOKE_IRQPRIO_DBELL_CRIT 147 
#define  BOOKE_IRQPRIO_DEBUG 146 
#define  BOOKE_IRQPRIO_DECREMENTER 145 
#define  BOOKE_IRQPRIO_DTLB_MISS 144 
#define  BOOKE_IRQPRIO_EXTERNAL 143 
 unsigned int BOOKE_IRQPRIO_EXTERNAL_LEVEL ; 
#define  BOOKE_IRQPRIO_FIT 142 
#define  BOOKE_IRQPRIO_FP_UNAVAIL 141 
#define  BOOKE_IRQPRIO_INST_STORAGE 140 
#define  BOOKE_IRQPRIO_ITLB_MISS 139 
#define  BOOKE_IRQPRIO_MACHINE_CHECK 138 
#define  BOOKE_IRQPRIO_PROGRAM 137 
#define  BOOKE_IRQPRIO_SPE_FP_DATA 136 
#define  BOOKE_IRQPRIO_SPE_FP_ROUND 135 
#define  BOOKE_IRQPRIO_SPE_UNAVAIL 134 
#define  BOOKE_IRQPRIO_SYSCALL 133 
#define  BOOKE_IRQPRIO_WATCHDOG 132 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CPU_FTR_DEBUG_LVL_EXC ; 
#define  INT_CLASS_CRIT 131 
#define  INT_CLASS_DBG 130 
#define  INT_CLASS_MC 129 
#define  INT_CLASS_NONCRIT 128 
 int KVMPPC_EPR_KERNEL ; 
 int KVMPPC_EPR_USER ; 
 scalar_t__ KVMPPC_IRQ_MPIC ; 
 int /*<<< orphan*/  KVM_REQ_EPR_EXIT ; 
 int MSR_CE ; 
 int MSR_CM ; 
 int MSR_DE ; 
 int MSR_EE ; 
 int MSR_ME ; 
 int MSR_PR ; 
 int MSR_SF ; 
 int SPRN_EPCR_ICM ; 
 int /*<<< orphan*/  clear_bit (unsigned int,int*) ; 
 int /*<<< orphan*/  cpu_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int kvmppc_get_gpr (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvmppc_mpic_set_epr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_set_dar (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_set_esr (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_set_msr (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvmppc_set_pending_interrupt (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  set_guest_csrr (struct kvm_vcpu*,int,int) ; 
 int /*<<< orphan*/  set_guest_dsrr (struct kvm_vcpu*,int,int) ; 
 int /*<<< orphan*/  set_guest_mcsrr (struct kvm_vcpu*,int,int) ; 
 int /*<<< orphan*/  set_guest_srr (struct kvm_vcpu*,int,int) ; 

__attribute__((used)) static int kvmppc_booke_irqprio_deliver(struct kvm_vcpu *vcpu,
                                        unsigned int priority)
{
	int allowed = 0;
	ulong msr_mask = 0;
	bool update_esr = false, update_dear = false, update_epr = false;
	ulong crit_raw = vcpu->arch.shared->critical;
	ulong crit_r1 = kvmppc_get_gpr(vcpu, 1);
	bool crit;
	bool keep_irq = false;
	enum int_class int_class;
	ulong new_msr = vcpu->arch.shared->msr;

	/* Truncate crit indicators in 32 bit mode */
	if (!(vcpu->arch.shared->msr & MSR_SF)) {
		crit_raw &= 0xffffffff;
		crit_r1 &= 0xffffffff;
	}

	/* Critical section when crit == r1 */
	crit = (crit_raw == crit_r1);
	/* ... and we're in supervisor mode */
	crit = crit && !(vcpu->arch.shared->msr & MSR_PR);

	if (priority == BOOKE_IRQPRIO_EXTERNAL_LEVEL) {
		priority = BOOKE_IRQPRIO_EXTERNAL;
		keep_irq = true;
	}

	if ((priority == BOOKE_IRQPRIO_EXTERNAL) && vcpu->arch.epr_flags)
		update_epr = true;

	switch (priority) {
	case BOOKE_IRQPRIO_DTLB_MISS:
	case BOOKE_IRQPRIO_DATA_STORAGE:
	case BOOKE_IRQPRIO_ALIGNMENT:
		update_dear = true;
		/* fall through */
	case BOOKE_IRQPRIO_INST_STORAGE:
	case BOOKE_IRQPRIO_PROGRAM:
		update_esr = true;
		/* fall through */
	case BOOKE_IRQPRIO_ITLB_MISS:
	case BOOKE_IRQPRIO_SYSCALL:
	case BOOKE_IRQPRIO_FP_UNAVAIL:
#ifdef CONFIG_SPE_POSSIBLE
	case BOOKE_IRQPRIO_SPE_UNAVAIL:
	case BOOKE_IRQPRIO_SPE_FP_DATA:
	case BOOKE_IRQPRIO_SPE_FP_ROUND:
#endif
#ifdef CONFIG_ALTIVEC
	case BOOKE_IRQPRIO_ALTIVEC_UNAVAIL:
	case BOOKE_IRQPRIO_ALTIVEC_ASSIST:
#endif
	case BOOKE_IRQPRIO_AP_UNAVAIL:
		allowed = 1;
		msr_mask = MSR_CE | MSR_ME | MSR_DE;
		int_class = INT_CLASS_NONCRIT;
		break;
	case BOOKE_IRQPRIO_WATCHDOG:
	case BOOKE_IRQPRIO_CRITICAL:
	case BOOKE_IRQPRIO_DBELL_CRIT:
		allowed = vcpu->arch.shared->msr & MSR_CE;
		allowed = allowed && !crit;
		msr_mask = MSR_ME;
		int_class = INT_CLASS_CRIT;
		break;
	case BOOKE_IRQPRIO_MACHINE_CHECK:
		allowed = vcpu->arch.shared->msr & MSR_ME;
		allowed = allowed && !crit;
		int_class = INT_CLASS_MC;
		break;
	case BOOKE_IRQPRIO_DECREMENTER:
	case BOOKE_IRQPRIO_FIT:
		keep_irq = true;
		/* fall through */
	case BOOKE_IRQPRIO_EXTERNAL:
	case BOOKE_IRQPRIO_DBELL:
		allowed = vcpu->arch.shared->msr & MSR_EE;
		allowed = allowed && !crit;
		msr_mask = MSR_CE | MSR_ME | MSR_DE;
		int_class = INT_CLASS_NONCRIT;
		break;
	case BOOKE_IRQPRIO_DEBUG:
		allowed = vcpu->arch.shared->msr & MSR_DE;
		allowed = allowed && !crit;
		msr_mask = MSR_ME;
		if (cpu_has_feature(CPU_FTR_DEBUG_LVL_EXC))
			int_class = INT_CLASS_DBG;
		else
			int_class = INT_CLASS_CRIT;

		break;
	}

	if (allowed) {
		switch (int_class) {
		case INT_CLASS_NONCRIT:
			set_guest_srr(vcpu, vcpu->arch.regs.nip,
				      vcpu->arch.shared->msr);
			break;
		case INT_CLASS_CRIT:
			set_guest_csrr(vcpu, vcpu->arch.regs.nip,
				       vcpu->arch.shared->msr);
			break;
		case INT_CLASS_DBG:
			set_guest_dsrr(vcpu, vcpu->arch.regs.nip,
				       vcpu->arch.shared->msr);
			break;
		case INT_CLASS_MC:
			set_guest_mcsrr(vcpu, vcpu->arch.regs.nip,
					vcpu->arch.shared->msr);
			break;
		}

		vcpu->arch.regs.nip = vcpu->arch.ivpr |
					vcpu->arch.ivor[priority];
		if (update_esr == true)
			kvmppc_set_esr(vcpu, vcpu->arch.queued_esr);
		if (update_dear == true)
			kvmppc_set_dar(vcpu, vcpu->arch.queued_dear);
		if (update_epr == true) {
			if (vcpu->arch.epr_flags & KVMPPC_EPR_USER)
				kvm_make_request(KVM_REQ_EPR_EXIT, vcpu);
			else if (vcpu->arch.epr_flags & KVMPPC_EPR_KERNEL) {
				BUG_ON(vcpu->arch.irq_type != KVMPPC_IRQ_MPIC);
				kvmppc_mpic_set_epr(vcpu);
			}
		}

		new_msr &= msr_mask;
#if defined(CONFIG_64BIT)
		if (vcpu->arch.epcr & SPRN_EPCR_ICM)
			new_msr |= MSR_CM;
#endif
		kvmppc_set_msr(vcpu, new_msr);

		if (!keep_irq)
			clear_bit(priority, &vcpu->arch.pending_exceptions);
	}

#ifdef CONFIG_KVM_BOOKE_HV
	/*
	 * If an interrupt is pending but masked, raise a guest doorbell
	 * so that we are notified when the guest enables the relevant
	 * MSR bit.
	 */
	if (vcpu->arch.pending_exceptions & BOOKE_IRQMASK_EE)
		kvmppc_set_pending_interrupt(vcpu, INT_CLASS_NONCRIT);
	if (vcpu->arch.pending_exceptions & BOOKE_IRQMASK_CE)
		kvmppc_set_pending_interrupt(vcpu, INT_CLASS_CRIT);
	if (vcpu->arch.pending_exceptions & BOOKE_IRQPRIO_MACHINE_CHECK)
		kvmppc_set_pending_interrupt(vcpu, INT_CLASS_MC);
#endif

	return allowed;
}