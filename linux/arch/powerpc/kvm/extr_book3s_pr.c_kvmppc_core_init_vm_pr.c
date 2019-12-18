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
struct TYPE_2__ {int /*<<< orphan*/  hpt_mutex; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_FEATURE_SET_MODE ; 
 scalar_t__ firmware_has_feature (int /*<<< orphan*/ ) ; 
 int kvm_global_user_count ; 
 int /*<<< orphan*/  kvm_global_user_count_lock ; 
 int /*<<< orphan*/  kvmppc_pr_init_default_hcalls (struct kvm*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pseries_disable_reloc_on_exc () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kvmppc_core_init_vm_pr(struct kvm *kvm)
{
	mutex_init(&kvm->arch.hpt_mutex);

#ifdef CONFIG_PPC_BOOK3S_64
	/* Start out with the default set of hcalls enabled */
	kvmppc_pr_init_default_hcalls(kvm);
#endif

	if (firmware_has_feature(FW_FEATURE_SET_MODE)) {
		spin_lock(&kvm_global_user_count_lock);
		if (++kvm_global_user_count == 1)
			pseries_disable_reloc_on_exc();
		spin_unlock(&kvm_global_user_count_lock);
	}
	return 0;
}