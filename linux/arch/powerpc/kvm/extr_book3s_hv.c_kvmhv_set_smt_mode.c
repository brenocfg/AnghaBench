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
struct TYPE_2__ {unsigned long smt_mode; int emul_smt_mode; int /*<<< orphan*/  online_vcores; } ;
struct kvm {int /*<<< orphan*/  lock; TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_ARCH_300 ; 
 int EBUSY ; 
 int EINVAL ; 
 unsigned long MAX_SMT_THREADS ; 
 int /*<<< orphan*/  cpu_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_power_of_2 (unsigned long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned long threads_per_subcore ; 

__attribute__((used)) static int kvmhv_set_smt_mode(struct kvm *kvm, unsigned long smt_mode,
			      unsigned long flags)
{
	int err;
	int esmt = 0;

	if (flags)
		return -EINVAL;
	if (smt_mode > MAX_SMT_THREADS || !is_power_of_2(smt_mode))
		return -EINVAL;
	if (!cpu_has_feature(CPU_FTR_ARCH_300)) {
		/*
		 * On POWER8 (or POWER7), the threading mode is "strict",
		 * so we pack smt_mode vcpus per vcore.
		 */
		if (smt_mode > threads_per_subcore)
			return -EINVAL;
	} else {
		/*
		 * On POWER9, the threading mode is "loose",
		 * so each vcpu gets its own vcore.
		 */
		esmt = smt_mode;
		smt_mode = 1;
	}
	mutex_lock(&kvm->lock);
	err = -EBUSY;
	if (!kvm->arch.online_vcores) {
		kvm->arch.smt_mode = smt_mode;
		kvm->arch.emul_smt_mode = esmt;
		err = 0;
	}
	mutex_unlock(&kvm->lock);

	return err;
}