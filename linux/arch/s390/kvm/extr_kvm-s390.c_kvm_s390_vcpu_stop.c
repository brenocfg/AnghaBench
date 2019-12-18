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
struct kvm_vcpu {TYPE_2__* kvm; int /*<<< orphan*/  vcpu_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  start_stop_lock; } ;
struct TYPE_4__ {TYPE_1__ arch; struct kvm_vcpu** vcpus; int /*<<< orphan*/  online_vcpus; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUSTAT_STOPPED ; 
 int /*<<< orphan*/  __disable_ibs_on_vcpu (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  __enable_ibs_on_vcpu (struct kvm_vcpu*) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ is_vcpu_stopped (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_s390_clear_stop_irq (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_s390_set_cpuflags (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_kvm_s390_vcpu_start_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void kvm_s390_vcpu_stop(struct kvm_vcpu *vcpu)
{
	int i, online_vcpus, started_vcpus = 0;
	struct kvm_vcpu *started_vcpu = NULL;

	if (is_vcpu_stopped(vcpu))
		return;

	trace_kvm_s390_vcpu_start_stop(vcpu->vcpu_id, 0);
	/* Only one cpu at a time may enter/leave the STOPPED state. */
	spin_lock(&vcpu->kvm->arch.start_stop_lock);
	online_vcpus = atomic_read(&vcpu->kvm->online_vcpus);

	/* SIGP STOP and SIGP STOP AND STORE STATUS has been fully processed */
	kvm_s390_clear_stop_irq(vcpu);

	kvm_s390_set_cpuflags(vcpu, CPUSTAT_STOPPED);
	__disable_ibs_on_vcpu(vcpu);

	for (i = 0; i < online_vcpus; i++) {
		if (!is_vcpu_stopped(vcpu->kvm->vcpus[i])) {
			started_vcpus++;
			started_vcpu = vcpu->kvm->vcpus[i];
		}
	}

	if (started_vcpus == 1) {
		/*
		 * As we only have one VCPU left, we want to enable the
		 * IBS facility for that VCPU to speed it up.
		 */
		__enable_ibs_on_vcpu(started_vcpu);
	}

	spin_unlock(&vcpu->kvm->arch.start_stop_lock);
	return;
}