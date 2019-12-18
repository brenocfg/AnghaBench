#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct kvm_memslots {int dummy; } ;
struct kvm_memory_slot {int /*<<< orphan*/  dirty_bitmap; } ;
struct kvm_dirty_log {int /*<<< orphan*/  slot; } ;
struct kvm {int /*<<< orphan*/  slots_lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  KVM_USER_MEM_SLOTS ; 
 struct kvm_memory_slot* id_to_memslot (struct kvm_memslots*,int /*<<< orphan*/ ) ; 
 unsigned long kvm_dirty_bitmap_bytes (struct kvm_memory_slot*) ; 
 int kvm_get_dirty_log (struct kvm*,struct kvm_dirty_log*,int*) ; 
 scalar_t__ kvm_is_ucontrol (struct kvm*) ; 
 struct kvm_memslots* kvm_memslots (struct kvm*) ; 
 int /*<<< orphan*/  kvm_s390_sync_dirty_log (struct kvm*,struct kvm_memory_slot*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int kvm_vm_ioctl_get_dirty_log(struct kvm *kvm,
			       struct kvm_dirty_log *log)
{
	int r;
	unsigned long n;
	struct kvm_memslots *slots;
	struct kvm_memory_slot *memslot;
	int is_dirty = 0;

	if (kvm_is_ucontrol(kvm))
		return -EINVAL;

	mutex_lock(&kvm->slots_lock);

	r = -EINVAL;
	if (log->slot >= KVM_USER_MEM_SLOTS)
		goto out;

	slots = kvm_memslots(kvm);
	memslot = id_to_memslot(slots, log->slot);
	r = -ENOENT;
	if (!memslot->dirty_bitmap)
		goto out;

	kvm_s390_sync_dirty_log(kvm, memslot);
	r = kvm_get_dirty_log(kvm, log, &is_dirty);
	if (r)
		goto out;

	/* Clear the dirty log */
	if (is_dirty) {
		n = kvm_dirty_bitmap_bytes(memslot);
		memset(memslot->dirty_bitmap, 0, n);
	}
	r = 0;
out:
	mutex_unlock(&kvm->slots_lock);
	return r;
}