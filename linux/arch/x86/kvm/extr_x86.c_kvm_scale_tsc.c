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
typedef  scalar_t__ u64 ;
struct TYPE_2__ {scalar_t__ tsc_scaling_ratio; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 scalar_t__ __scale_tsc (scalar_t__,scalar_t__) ; 
 scalar_t__ kvm_default_tsc_scaling_ratio ; 

u64 kvm_scale_tsc(struct kvm_vcpu *vcpu, u64 tsc)
{
	u64 _tsc = tsc;
	u64 ratio = vcpu->arch.tsc_scaling_ratio;

	if (ratio != kvm_default_tsc_scaling_ratio)
		_tsc = __scale_tsc(ratio, tsc);

	return _tsc;
}