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
struct TYPE_2__ {scalar_t__ tsc_scaling_ratio; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  adjust_tsc_offset_guest (struct kvm_vcpu*,scalar_t__) ; 
 scalar_t__ kvm_default_tsc_scaling_ratio ; 
 scalar_t__ kvm_scale_tsc (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void adjust_tsc_offset_host(struct kvm_vcpu *vcpu, s64 adjustment)
{
	if (vcpu->arch.tsc_scaling_ratio != kvm_default_tsc_scaling_ratio)
		WARN_ON(adjustment < 0);
	adjustment = kvm_scale_tsc(vcpu, (u64) adjustment);
	adjust_tsc_offset_guest(vcpu, adjustment);
}