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
typedef  scalar_t__ u64 ;
struct TYPE_3__ {int /*<<< orphan*/  ia32_tsc_adjust_msr; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
typedef  scalar_t__ s64 ;
struct TYPE_4__ {scalar_t__ (* read_l1_tsc_offset ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 TYPE_2__* kvm_x86_ops ; 
 scalar_t__ stub1 (struct kvm_vcpu*) ; 

__attribute__((used)) static void update_ia32_tsc_adjust_msr(struct kvm_vcpu *vcpu, s64 offset)
{
	u64 curr_offset = kvm_x86_ops->read_l1_tsc_offset(vcpu);
	vcpu->arch.ia32_tsc_adjust_msr += offset - curr_offset;
}