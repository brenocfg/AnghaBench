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
struct TYPE_3__ {int last_sched_cpu; } ;
struct kvm_vcpu {int cpu; TYPE_1__ arch; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* vcpu_put ) (struct kvm_vcpu*,int) ;} ;

/* Variables and functions */
 TYPE_2__* kvm_mips_callbacks ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,int) ; 

void kvm_arch_vcpu_put(struct kvm_vcpu *vcpu)
{
	unsigned long flags;
	int cpu;

	local_irq_save(flags);

	cpu = smp_processor_id();
	vcpu->arch.last_sched_cpu = cpu;
	vcpu->cpu = -1;

	/* save guest state in registers */
	kvm_mips_callbacks->vcpu_put(vcpu, cpu);

	local_irq_restore(flags);
}