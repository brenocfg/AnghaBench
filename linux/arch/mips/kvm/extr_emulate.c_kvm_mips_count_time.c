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
struct TYPE_2__ {int count_ctl; int /*<<< orphan*/  count_resume; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int KVM_REG_MIPS_COUNT_CTL_DC ; 
 int /*<<< orphan*/  ktime_get () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline ktime_t kvm_mips_count_time(struct kvm_vcpu *vcpu)
{
	if (unlikely(vcpu->arch.count_ctl & KVM_REG_MIPS_COUNT_CTL_DC))
		return vcpu->arch.count_resume;

	return ktime_get();
}