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
struct kvmppc_icp {struct kvm_vcpu* rm_kick_target; int /*<<< orphan*/  rm_action; } ;
struct TYPE_4__ {int thread_cpu; int /*<<< orphan*/  pending_exceptions; struct kvmppc_icp* icp; } ;
struct TYPE_3__ {int /*<<< orphan*/  queue_intr; } ;
struct kvm_vcpu {TYPE_2__ arch; TYPE_1__ stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOOK3S_IRQPRIO_EXTERNAL ; 
 int LPCR_MER ; 
 int /*<<< orphan*/  SPRN_LPCR ; 
 int /*<<< orphan*/  XICS_RM_KICK_VCPU ; 
 int find_available_hostcore (int /*<<< orphan*/ ) ; 
 scalar_t__ h_ipi_redirect ; 
 int /*<<< orphan*/  icp_send_hcore_msg (int,struct kvm_vcpu*) ; 
 scalar_t__ kvmhv_on_pseries () ; 
 int /*<<< orphan*/  kvmhv_rm_send_ipi (int) ; 
 scalar_t__ kvmppc_host_rm_ops_hv ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 
 int nr_cpu_ids ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb () ; 
 scalar_t__ xive_enabled () ; 

__attribute__((used)) static void icp_rm_set_vcpu_irq(struct kvm_vcpu *vcpu,
				struct kvm_vcpu *this_vcpu)
{
	struct kvmppc_icp *this_icp = this_vcpu->arch.icp;
	int cpu;
	int hcore;

	/* Mark the target VCPU as having an interrupt pending */
	vcpu->stat.queue_intr++;
	set_bit(BOOK3S_IRQPRIO_EXTERNAL, &vcpu->arch.pending_exceptions);

	/* Kick self ? Just set MER and return */
	if (vcpu == this_vcpu) {
		mtspr(SPRN_LPCR, mfspr(SPRN_LPCR) | LPCR_MER);
		return;
	}

	if (xive_enabled() && kvmhv_on_pseries()) {
		/* No XICS access or hypercalls available, too hard */
		this_icp->rm_action |= XICS_RM_KICK_VCPU;
		this_icp->rm_kick_target = vcpu;
		return;
	}

	/*
	 * Check if the core is loaded,
	 * if not, find an available host core to post to wake the VCPU,
	 * if we can't find one, set up state to eventually return too hard.
	 */
	cpu = vcpu->arch.thread_cpu;
	if (cpu < 0 || cpu >= nr_cpu_ids) {
		hcore = -1;
		if (kvmppc_host_rm_ops_hv && h_ipi_redirect)
			hcore = find_available_hostcore(XICS_RM_KICK_VCPU);
		if (hcore != -1) {
			icp_send_hcore_msg(hcore, vcpu);
		} else {
			this_icp->rm_action |= XICS_RM_KICK_VCPU;
			this_icp->rm_kick_target = vcpu;
		}
		return;
	}

	smp_mb();
	kvmhv_rm_send_ipi(cpu);
}