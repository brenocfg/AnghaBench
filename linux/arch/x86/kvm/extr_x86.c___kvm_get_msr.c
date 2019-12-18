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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct msr_data {int host_initiated; int /*<<< orphan*/  data; int /*<<< orphan*/  index; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {int (* get_msr ) (struct kvm_vcpu*,struct msr_data*) ;} ;

/* Variables and functions */
 TYPE_1__* kvm_x86_ops ; 
 int stub1 (struct kvm_vcpu*,struct msr_data*) ; 

__attribute__((used)) static int __kvm_get_msr(struct kvm_vcpu *vcpu, u32 index, u64 *data,
			 bool host_initiated)
{
	struct msr_data msr;
	int ret;

	msr.index = index;
	msr.host_initiated = host_initiated;

	ret = kvm_x86_ops->get_msr(vcpu, &msr);
	if (!ret)
		*data = msr.data;
	return ret;
}