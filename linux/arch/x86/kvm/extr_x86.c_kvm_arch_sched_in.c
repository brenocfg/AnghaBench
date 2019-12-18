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
struct TYPE_3__ {int l1tf_flush_l1d; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* sched_in ) (struct kvm_vcpu*,int) ;} ;

/* Variables and functions */
 TYPE_2__* kvm_x86_ops ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,int) ; 

void kvm_arch_sched_in(struct kvm_vcpu *vcpu, int cpu)
{
	vcpu->arch.l1tf_flush_l1d = true;
	kvm_x86_ops->sched_in(vcpu, cpu);
}