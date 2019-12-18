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
typedef  size_t u32 ;
struct kvm_vcpu_hv_synic {int /*<<< orphan*/ * sint_to_gsi; } ;
struct TYPE_2__ {size_t sintx; int /*<<< orphan*/  direct_mode; scalar_t__ enable; } ;
struct kvm_vcpu_hv_stimer {TYPE_1__ config; scalar_t__ msg_pending; } ;
struct kvm_vcpu_hv {struct kvm_vcpu_hv_stimer* stimer; } ;
struct kvm_vcpu {int /*<<< orphan*/  vcpu_id; struct kvm* kvm; } ;
struct kvm {int /*<<< orphan*/  irq_srcu; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct kvm_vcpu_hv_stimer*) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_notify_acked_gsi (struct kvm*,int) ; 
 int srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stimer_mark_pending (struct kvm_vcpu_hv_stimer*,int) ; 
 int /*<<< orphan*/  trace_kvm_hv_notify_acked_sint (int /*<<< orphan*/ ,size_t) ; 
 struct kvm_vcpu_hv* vcpu_to_hv_vcpu (struct kvm_vcpu*) ; 
 struct kvm_vcpu_hv_synic* vcpu_to_synic (struct kvm_vcpu*) ; 

__attribute__((used)) static void kvm_hv_notify_acked_sint(struct kvm_vcpu *vcpu, u32 sint)
{
	struct kvm *kvm = vcpu->kvm;
	struct kvm_vcpu_hv_synic *synic = vcpu_to_synic(vcpu);
	struct kvm_vcpu_hv *hv_vcpu = vcpu_to_hv_vcpu(vcpu);
	struct kvm_vcpu_hv_stimer *stimer;
	int gsi, idx;

	trace_kvm_hv_notify_acked_sint(vcpu->vcpu_id, sint);

	/* Try to deliver pending Hyper-V SynIC timers messages */
	for (idx = 0; idx < ARRAY_SIZE(hv_vcpu->stimer); idx++) {
		stimer = &hv_vcpu->stimer[idx];
		if (stimer->msg_pending && stimer->config.enable &&
		    !stimer->config.direct_mode &&
		    stimer->config.sintx == sint)
			stimer_mark_pending(stimer, false);
	}

	idx = srcu_read_lock(&kvm->irq_srcu);
	gsi = atomic_read(&synic->sint_to_gsi[sint]);
	if (gsi != -1)
		kvm_notify_acked_gsi(kvm, gsi);
	srcu_read_unlock(&kvm->irq_srcu, idx);
}