#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_5__ {int tsc_offset_adjustment; scalar_t__ last_host_tsc; int tsc_catchup; int /*<<< orphan*/  last_guest_tsc; int /*<<< orphan*/  wbinvd_dirty_mask; } ;
struct kvm_vcpu {int cpu; TYPE_3__* kvm; TYPE_1__ arch; } ;
typedef  scalar_t__ s64 ;
struct TYPE_8__ {int /*<<< orphan*/  (* vcpu_load ) (struct kvm_vcpu*,int) ;scalar_t__ (* has_wbinvd_exit ) () ;} ;
struct TYPE_6__ {int /*<<< orphan*/  use_master_clock; } ;
struct TYPE_7__ {TYPE_2__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_REQ_CLOCK_UPDATE ; 
 int /*<<< orphan*/  KVM_REQ_GLOBAL_CLOCK_UPDATE ; 
 int /*<<< orphan*/  KVM_REQ_MIGRATE_TIMER ; 
 int /*<<< orphan*/  KVM_REQ_STEAL_UPDATE ; 
 int /*<<< orphan*/  TIF_NEED_FPU_LOAD ; 
 int /*<<< orphan*/  adjust_tsc_offset_host (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpregs_assert_state_consistent () ; 
 scalar_t__ kvm_check_tsc_unstable () ; 
 int /*<<< orphan*/  kvm_compute_tsc_offset (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_lapic_hv_timer_in_use (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_lapic_restart_hv_timer (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_vcpu_write_tsc_offset (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 TYPE_4__* kvm_x86_ops ; 
 int /*<<< orphan*/  mark_tsc_unstable (char*) ; 
 scalar_t__ need_emulate_wbinvd (struct kvm_vcpu*) ; 
 scalar_t__ rdtsc () ; 
 int /*<<< orphan*/  smp_call_function_single (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ stub1 () ; 
 int /*<<< orphan*/  stub2 (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  switch_fpu_return () ; 
 scalar_t__ test_thread_flag (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wbinvd_ipi ; 

void kvm_arch_vcpu_load(struct kvm_vcpu *vcpu, int cpu)
{
	/* Address WBINVD may be executed by guest */
	if (need_emulate_wbinvd(vcpu)) {
		if (kvm_x86_ops->has_wbinvd_exit())
			cpumask_set_cpu(cpu, vcpu->arch.wbinvd_dirty_mask);
		else if (vcpu->cpu != -1 && vcpu->cpu != cpu)
			smp_call_function_single(vcpu->cpu,
					wbinvd_ipi, NULL, 1);
	}

	kvm_x86_ops->vcpu_load(vcpu, cpu);

	fpregs_assert_state_consistent();
	if (test_thread_flag(TIF_NEED_FPU_LOAD))
		switch_fpu_return();

	/* Apply any externally detected TSC adjustments (due to suspend) */
	if (unlikely(vcpu->arch.tsc_offset_adjustment)) {
		adjust_tsc_offset_host(vcpu, vcpu->arch.tsc_offset_adjustment);
		vcpu->arch.tsc_offset_adjustment = 0;
		kvm_make_request(KVM_REQ_CLOCK_UPDATE, vcpu);
	}

	if (unlikely(vcpu->cpu != cpu) || kvm_check_tsc_unstable()) {
		s64 tsc_delta = !vcpu->arch.last_host_tsc ? 0 :
				rdtsc() - vcpu->arch.last_host_tsc;
		if (tsc_delta < 0)
			mark_tsc_unstable("KVM discovered backwards TSC");

		if (kvm_check_tsc_unstable()) {
			u64 offset = kvm_compute_tsc_offset(vcpu,
						vcpu->arch.last_guest_tsc);
			kvm_vcpu_write_tsc_offset(vcpu, offset);
			vcpu->arch.tsc_catchup = 1;
		}

		if (kvm_lapic_hv_timer_in_use(vcpu))
			kvm_lapic_restart_hv_timer(vcpu);

		/*
		 * On a host with synchronized TSC, there is no need to update
		 * kvmclock on vcpu->cpu migration
		 */
		if (!vcpu->kvm->arch.use_master_clock || vcpu->cpu == -1)
			kvm_make_request(KVM_REQ_GLOBAL_CLOCK_UPDATE, vcpu);
		if (vcpu->cpu != cpu)
			kvm_make_request(KVM_REQ_MIGRATE_TIMER, vcpu);
		vcpu->cpu = cpu;
	}

	kvm_make_request(KVM_REQ_STEAL_UPDATE, vcpu);
}