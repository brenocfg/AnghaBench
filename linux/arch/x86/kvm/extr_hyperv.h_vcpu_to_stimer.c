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
struct kvm_vcpu_hv_stimer {int dummy; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {struct kvm_vcpu_hv_stimer* stimer; } ;

/* Variables and functions */
 TYPE_1__* vcpu_to_hv_vcpu (struct kvm_vcpu*) ; 

__attribute__((used)) static inline struct kvm_vcpu_hv_stimer *vcpu_to_stimer(struct kvm_vcpu *vcpu,
							int timer_index)
{
	return &vcpu_to_hv_vcpu(vcpu)->stimer[timer_index];
}