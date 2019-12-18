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
struct msr_data {int dummy; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_4__ {TYPE_1__* pmu_ops; } ;
struct TYPE_3__ {int (* set_msr ) (struct kvm_vcpu*,struct msr_data*) ;} ;

/* Variables and functions */
 TYPE_2__* kvm_x86_ops ; 
 int stub1 (struct kvm_vcpu*,struct msr_data*) ; 

int kvm_pmu_set_msr(struct kvm_vcpu *vcpu, struct msr_data *msr_info)
{
	return kvm_x86_ops->pmu_ops->set_msr(vcpu, msr_info);
}