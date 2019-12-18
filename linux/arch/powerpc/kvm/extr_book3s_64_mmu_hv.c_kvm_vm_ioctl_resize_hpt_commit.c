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
struct kvm_resize_hpt {unsigned long order; long error; } ;
struct kvm_ppc_resize_hpt {unsigned long flags; unsigned long shift; } ;
struct TYPE_2__ {int mmu_ready; int /*<<< orphan*/  mmu_setup_lock; struct kvm_resize_hpt* resize_hpt; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 long EINVAL ; 
 long EIO ; 
 long ENXIO ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ kvm_is_radix (struct kvm*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  resize_hpt_boot_vcpu ; 
 int /*<<< orphan*/  resize_hpt_pivot (struct kvm_resize_hpt*) ; 
 long resize_hpt_rehash (struct kvm_resize_hpt*) ; 
 int /*<<< orphan*/  resize_hpt_release (struct kvm*,struct kvm_resize_hpt*) ; 
 int /*<<< orphan*/  smp_mb () ; 

long kvm_vm_ioctl_resize_hpt_commit(struct kvm *kvm,
				    struct kvm_ppc_resize_hpt *rhpt)
{
	unsigned long flags = rhpt->flags;
	unsigned long shift = rhpt->shift;
	struct kvm_resize_hpt *resize;
	long ret;

	if (flags != 0 || kvm_is_radix(kvm))
		return -EINVAL;

	if (shift && ((shift < 18) || (shift > 46)))
		return -EINVAL;

	mutex_lock(&kvm->arch.mmu_setup_lock);

	resize = kvm->arch.resize_hpt;

	/* This shouldn't be possible */
	ret = -EIO;
	if (WARN_ON(!kvm->arch.mmu_ready))
		goto out_no_hpt;

	/* Stop VCPUs from running while we mess with the HPT */
	kvm->arch.mmu_ready = 0;
	smp_mb();

	/* Boot all CPUs out of the guest so they re-read
	 * mmu_ready */
	on_each_cpu(resize_hpt_boot_vcpu, NULL, 1);

	ret = -ENXIO;
	if (!resize || (resize->order != shift))
		goto out;

	ret = resize->error;
	if (ret)
		goto out;

	ret = resize_hpt_rehash(resize);
	if (ret)
		goto out;

	resize_hpt_pivot(resize);

out:
	/* Let VCPUs run again */
	kvm->arch.mmu_ready = 1;
	smp_mb();
out_no_hpt:
	resize_hpt_release(kvm, resize);
	mutex_unlock(&kvm->arch.mmu_setup_lock);
	return ret;
}