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
struct TYPE_2__ {int /*<<< orphan*/  nx_lpage_recovery_thread; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  kthread_unpark (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_nx_lpage_recovery_worker ; 
 int kvm_vm_create_worker_thread (struct kvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

int kvm_mmu_post_init_vm(struct kvm *kvm)
{
	int err;

	err = kvm_vm_create_worker_thread(kvm, kvm_nx_lpage_recovery_worker, 0,
					  "kvm-nx-lpage-recovery",
					  &kvm->arch.nx_lpage_recovery_thread);
	if (!err)
		kthread_unpark(kvm->arch.nx_lpage_recovery_thread);

	return err;
}