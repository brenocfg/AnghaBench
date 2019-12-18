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
struct kvm_dirty_log {int dummy; } ;
struct kvm {int /*<<< orphan*/  slots_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* flush_log_dirty ) (struct kvm*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_flush_remote_tlbs (struct kvm*) ; 
 int kvm_get_dirty_log_protect (struct kvm*,struct kvm_dirty_log*,int*) ; 
 TYPE_1__* kvm_x86_ops ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct kvm*) ; 

int kvm_vm_ioctl_get_dirty_log(struct kvm *kvm, struct kvm_dirty_log *log)
{
	bool flush = false;
	int r;

	mutex_lock(&kvm->slots_lock);

	/*
	 * Flush potentially hardware-cached dirty pages to dirty_bitmap.
	 */
	if (kvm_x86_ops->flush_log_dirty)
		kvm_x86_ops->flush_log_dirty(kvm);

	r = kvm_get_dirty_log_protect(kvm, log, &flush);

	/*
	 * All the TLBs can be flushed out of mmu lock, see the comments in
	 * kvm_mmu_slot_remove_write_access().
	 */
	lockdep_assert_held(&kvm->slots_lock);
	if (flush)
		kvm_flush_remote_tlbs(kvm);

	mutex_unlock(&kvm->slots_lock);
	return r;
}