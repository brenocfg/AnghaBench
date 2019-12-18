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
struct TYPE_2__ {scalar_t__ cputm_enabled; int /*<<< orphan*/  enabled_gmap; } ;
struct kvm_vcpu {int cpu; TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUSTAT_RUNNING ; 
 int /*<<< orphan*/  __start_cpu_timer_accounting (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  gmap_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_vcpu_idle (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_s390_set_cpuflags (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

void kvm_arch_vcpu_load(struct kvm_vcpu *vcpu, int cpu)
{

	gmap_enable(vcpu->arch.enabled_gmap);
	kvm_s390_set_cpuflags(vcpu, CPUSTAT_RUNNING);
	if (vcpu->arch.cputm_enabled && !is_vcpu_idle(vcpu))
		__start_cpu_timer_accounting(vcpu);
	vcpu->cpu = cpu;
}