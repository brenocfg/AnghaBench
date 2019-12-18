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
struct TYPE_2__ {int /*<<< orphan*/  spapr_tce_tables; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  FW_FEATURE_SET_MODE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ firmware_has_feature (int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_global_user_count ; 
 int /*<<< orphan*/  kvm_global_user_count_lock ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pseries_enable_reloc_on_exc () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kvmppc_core_destroy_vm_pr(struct kvm *kvm)
{
#ifdef CONFIG_PPC64
	WARN_ON(!list_empty(&kvm->arch.spapr_tce_tables));
#endif

	if (firmware_has_feature(FW_FEATURE_SET_MODE)) {
		spin_lock(&kvm_global_user_count_lock);
		BUG_ON(kvm_global_user_count == 0);
		if (--kvm_global_user_count == 0)
			pseries_enable_reloc_on_exc();
		spin_unlock(&kvm_global_user_count_lock);
	}
}