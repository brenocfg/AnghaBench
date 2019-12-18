#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  tsc_seq ;
struct pvclock_vcpu_time_info {int dummy; } ;
struct TYPE_5__ {int tsc_sequence; } ;
struct kvm_hv {int hv_tsc_page; int /*<<< orphan*/  hv_lock; TYPE_2__ tsc_ref; } ;
struct TYPE_4__ {struct kvm_hv hyperv; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  HV_REFERENCE_TSC_PAGE ; 
 int HV_X64_MSR_TSC_REFERENCE_ADDRESS_SHIFT ; 
 int HV_X64_MSR_TSC_REFERENCE_ENABLE ; 
 int /*<<< orphan*/  compute_tsc_page_parameters (struct pvclock_vcpu_time_info*,TYPE_2__*) ; 
 int /*<<< orphan*/  gfn_to_gpa (int) ; 
 int /*<<< orphan*/  kvm_read_guest (struct kvm*,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ kvm_write_guest (struct kvm*,int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  tsc_sequence ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void kvm_hv_setup_tsc_page(struct kvm *kvm,
			   struct pvclock_vcpu_time_info *hv_clock)
{
	struct kvm_hv *hv = &kvm->arch.hyperv;
	u32 tsc_seq;
	u64 gfn;

	BUILD_BUG_ON(sizeof(tsc_seq) != sizeof(hv->tsc_ref.tsc_sequence));
	BUILD_BUG_ON(offsetof(HV_REFERENCE_TSC_PAGE, tsc_sequence) != 0);

	if (!(hv->hv_tsc_page & HV_X64_MSR_TSC_REFERENCE_ENABLE))
		return;

	mutex_lock(&kvm->arch.hyperv.hv_lock);
	if (!(hv->hv_tsc_page & HV_X64_MSR_TSC_REFERENCE_ENABLE))
		goto out_unlock;

	gfn = hv->hv_tsc_page >> HV_X64_MSR_TSC_REFERENCE_ADDRESS_SHIFT;
	/*
	 * Because the TSC parameters only vary when there is a
	 * change in the master clock, do not bother with caching.
	 */
	if (unlikely(kvm_read_guest(kvm, gfn_to_gpa(gfn),
				    &tsc_seq, sizeof(tsc_seq))))
		goto out_unlock;

	/*
	 * While we're computing and writing the parameters, force the
	 * guest to use the time reference count MSR.
	 */
	hv->tsc_ref.tsc_sequence = 0;
	if (kvm_write_guest(kvm, gfn_to_gpa(gfn),
			    &hv->tsc_ref, sizeof(hv->tsc_ref.tsc_sequence)))
		goto out_unlock;

	if (!compute_tsc_page_parameters(hv_clock, &hv->tsc_ref))
		goto out_unlock;

	/* Ensure sequence is zero before writing the rest of the struct.  */
	smp_wmb();
	if (kvm_write_guest(kvm, gfn_to_gpa(gfn), &hv->tsc_ref, sizeof(hv->tsc_ref)))
		goto out_unlock;

	/*
	 * Now switch to the TSC page mechanism by writing the sequence.
	 */
	tsc_seq++;
	if (tsc_seq == 0xFFFFFFFF || tsc_seq == 0)
		tsc_seq = 1;

	/* Write the struct entirely before the non-zero sequence.  */
	smp_wmb();

	hv->tsc_ref.tsc_sequence = tsc_seq;
	kvm_write_guest(kvm, gfn_to_gpa(gfn),
			&hv->tsc_ref, sizeof(hv->tsc_ref.tsc_sequence));
out_unlock:
	mutex_unlock(&kvm->arch.hyperv.hv_lock);
}