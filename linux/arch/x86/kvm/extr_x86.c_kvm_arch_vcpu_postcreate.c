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
struct msr_data {int data; int host_initiated; int /*<<< orphan*/  index; } ;
struct TYPE_3__ {int msr_kvm_poll_control; } ;
struct kvm_vcpu {int /*<<< orphan*/  mutex; TYPE_1__ arch; struct kvm* kvm; } ;
struct TYPE_4__ {int /*<<< orphan*/  kvmclock_sync_work; } ;
struct kvm {TYPE_2__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVMCLOCK_SYNC_PERIOD ; 
 int /*<<< orphan*/  MSR_IA32_TSC ; 
 int /*<<< orphan*/  kvm_hv_vcpu_postcreate (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_write_tsc (struct kvm_vcpu*,struct msr_data*) ; 
 int /*<<< orphan*/  kvmclock_periodic_sync ; 
 scalar_t__ mutex_lock_killable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcpu_load (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_put (struct kvm_vcpu*) ; 

void kvm_arch_vcpu_postcreate(struct kvm_vcpu *vcpu)
{
	struct msr_data msr;
	struct kvm *kvm = vcpu->kvm;

	kvm_hv_vcpu_postcreate(vcpu);

	if (mutex_lock_killable(&vcpu->mutex))
		return;
	vcpu_load(vcpu);
	msr.data = 0x0;
	msr.index = MSR_IA32_TSC;
	msr.host_initiated = true;
	kvm_write_tsc(vcpu, &msr);
	vcpu_put(vcpu);

	/* poll control enabled by default */
	vcpu->arch.msr_kvm_poll_control = 1;

	mutex_unlock(&vcpu->mutex);

	if (!kvmclock_periodic_sync)
		return;

	schedule_delayed_work(&kvm->arch.kvmclock_sync_work,
					KVMCLOCK_SYNC_PERIOD);
}