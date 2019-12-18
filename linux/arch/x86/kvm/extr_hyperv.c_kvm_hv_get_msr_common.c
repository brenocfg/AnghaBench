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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct kvm_vcpu {TYPE_3__* kvm; } ;
struct TYPE_4__ {int /*<<< orphan*/  hv_lock; } ;
struct TYPE_5__ {TYPE_1__ hyperv; } ;
struct TYPE_6__ {TYPE_2__ arch; } ;

/* Variables and functions */
 int kvm_hv_get_msr (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int kvm_hv_get_msr_pw (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ kvm_hv_msr_partition_wide (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int kvm_hv_get_msr_common(struct kvm_vcpu *vcpu, u32 msr, u64 *pdata, bool host)
{
	if (kvm_hv_msr_partition_wide(msr)) {
		int r;

		mutex_lock(&vcpu->kvm->arch.hyperv.hv_lock);
		r = kvm_hv_get_msr_pw(vcpu, msr, pdata);
		mutex_unlock(&vcpu->kvm->arch.hyperv.hv_lock);
		return r;
	} else
		return kvm_hv_get_msr(vcpu, msr, pdata, host);
}