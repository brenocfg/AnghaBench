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
struct TYPE_3__ {int /*<<< orphan*/  ldt; int /*<<< orphan*/  gs; int /*<<< orphan*/  fs; int /*<<< orphan*/  gs_base; } ;
struct vcpu_svm {scalar_t__ vmcb; scalar_t__ tsc_aux; int /*<<< orphan*/ * host_user_msrs; TYPE_1__ host; scalar_t__ asid_generation; } ;
struct svm_cpu_data {scalar_t__ current_vmcb; } ;
struct TYPE_4__ {scalar_t__ tsc_scaling_ratio; } ;
struct kvm_vcpu {int cpu; TYPE_2__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_AMD64_TSC_RATIO ; 
 int /*<<< orphan*/  MSR_GS_BASE ; 
 int /*<<< orphan*/  MSR_TSC_AUX ; 
 int NR_HOST_SAVE_USER_MSRS ; 
 int /*<<< orphan*/  X86_FEATURE_RDTSCP ; 
 int /*<<< orphan*/  X86_FEATURE_TSCRATEMSR ; 
 scalar_t__ __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  avic_vcpu_load (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  current_tsc_ratio ; 
 int /*<<< orphan*/  fs ; 
 int /*<<< orphan*/  gs ; 
 int /*<<< orphan*/ * host_save_user_msrs ; 
 int /*<<< orphan*/  indirect_branch_prediction_barrier () ; 
 int /*<<< orphan*/  kvm_read_ldt () ; 
 int /*<<< orphan*/  mark_all_dirty (scalar_t__) ; 
 struct svm_cpu_data* per_cpu (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  savesegment (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ static_cpu_has (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svm_data ; 
 struct vcpu_svm* to_svm (struct kvm_vcpu*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void svm_vcpu_load(struct kvm_vcpu *vcpu, int cpu)
{
	struct vcpu_svm *svm = to_svm(vcpu);
	struct svm_cpu_data *sd = per_cpu(svm_data, cpu);
	int i;

	if (unlikely(cpu != vcpu->cpu)) {
		svm->asid_generation = 0;
		mark_all_dirty(svm->vmcb);
	}

#ifdef CONFIG_X86_64
	rdmsrl(MSR_GS_BASE, to_svm(vcpu)->host.gs_base);
#endif
	savesegment(fs, svm->host.fs);
	savesegment(gs, svm->host.gs);
	svm->host.ldt = kvm_read_ldt();

	for (i = 0; i < NR_HOST_SAVE_USER_MSRS; i++)
		rdmsrl(host_save_user_msrs[i], svm->host_user_msrs[i]);

	if (static_cpu_has(X86_FEATURE_TSCRATEMSR)) {
		u64 tsc_ratio = vcpu->arch.tsc_scaling_ratio;
		if (tsc_ratio != __this_cpu_read(current_tsc_ratio)) {
			__this_cpu_write(current_tsc_ratio, tsc_ratio);
			wrmsrl(MSR_AMD64_TSC_RATIO, tsc_ratio);
		}
	}
	/* This assumes that the kernel never uses MSR_TSC_AUX */
	if (static_cpu_has(X86_FEATURE_RDTSCP))
		wrmsrl(MSR_TSC_AUX, svm->tsc_aux);

	if (sd->current_vmcb != svm->vmcb) {
		sd->current_vmcb = svm->vmcb;
		indirect_branch_prediction_barrier();
	}
	avic_vcpu_load(vcpu, cpu);
}