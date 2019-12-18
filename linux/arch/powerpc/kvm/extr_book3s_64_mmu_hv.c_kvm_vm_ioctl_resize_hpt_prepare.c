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
struct kvm_resize_hpt {unsigned long order; int error; int /*<<< orphan*/  work; struct kvm* kvm; } ;
struct kvm_ppc_resize_hpt {unsigned long flags; unsigned long shift; } ;
struct TYPE_2__ {int /*<<< orphan*/  mmu_setup_lock; struct kvm_resize_hpt* resize_hpt; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int EBUSY ; 
 long EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_is_radix (struct kvm*) ; 
 struct kvm_resize_hpt* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resize_hpt_prepare_work ; 
 int /*<<< orphan*/  resize_hpt_release (struct kvm*,struct kvm_resize_hpt*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

long kvm_vm_ioctl_resize_hpt_prepare(struct kvm *kvm,
				     struct kvm_ppc_resize_hpt *rhpt)
{
	unsigned long flags = rhpt->flags;
	unsigned long shift = rhpt->shift;
	struct kvm_resize_hpt *resize;
	int ret;

	if (flags != 0 || kvm_is_radix(kvm))
		return -EINVAL;

	if (shift && ((shift < 18) || (shift > 46)))
		return -EINVAL;

	mutex_lock(&kvm->arch.mmu_setup_lock);

	resize = kvm->arch.resize_hpt;

	if (resize) {
		if (resize->order == shift) {
			/* Suitable resize in progress? */
			ret = resize->error;
			if (ret == -EBUSY)
				ret = 100; /* estimated time in ms */
			else if (ret)
				resize_hpt_release(kvm, resize);

			goto out;
		}

		/* not suitable, cancel it */
		resize_hpt_release(kvm, resize);
	}

	ret = 0;
	if (!shift)
		goto out; /* nothing to do */

	/* start new resize */

	resize = kzalloc(sizeof(*resize), GFP_KERNEL);
	if (!resize) {
		ret = -ENOMEM;
		goto out;
	}

	resize->error = -EBUSY;
	resize->order = shift;
	resize->kvm = kvm;
	INIT_WORK(&resize->work, resize_hpt_prepare_work);
	kvm->arch.resize_hpt = resize;

	schedule_work(&resize->work);

	ret = 100; /* estimated time in ms */

out:
	mutex_unlock(&kvm->arch.mmu_setup_lock);
	return ret;
}