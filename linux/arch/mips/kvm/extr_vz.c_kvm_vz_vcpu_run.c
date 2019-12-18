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
struct TYPE_2__ {int (* vcpu_run ) (struct kvm_run*,struct kvm_vcpu*) ;} ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_run {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_mips_deliver_interrupts (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_vz_acquire_htimer (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_vz_check_requests (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvm_vz_vcpu_load_tlb (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvm_vz_vcpu_load_wired (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_vz_vcpu_save_wired (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  read_gc0_cause () ; 
 int smp_processor_id () ; 
 int stub1 (struct kvm_run*,struct kvm_vcpu*) ; 

__attribute__((used)) static int kvm_vz_vcpu_run(struct kvm_run *run, struct kvm_vcpu *vcpu)
{
	int cpu = smp_processor_id();
	int r;

	kvm_vz_acquire_htimer(vcpu);
	/* Check if we have any exceptions/interrupts pending */
	kvm_mips_deliver_interrupts(vcpu, read_gc0_cause());

	kvm_vz_check_requests(vcpu, cpu);
	kvm_vz_vcpu_load_tlb(vcpu, cpu);
	kvm_vz_vcpu_load_wired(vcpu);

	r = vcpu->arch.vcpu_run(run, vcpu);

	kvm_vz_vcpu_save_wired(vcpu);

	return r;
}