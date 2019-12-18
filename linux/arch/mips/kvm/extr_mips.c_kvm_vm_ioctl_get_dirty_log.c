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
struct kvm_memslots {int dummy; } ;
struct kvm_memory_slot {int dummy; } ;
struct kvm_dirty_log {int /*<<< orphan*/  slot; } ;
struct kvm {int /*<<< orphan*/  slots_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* flush_shadow_memslot ) (struct kvm*,struct kvm_memory_slot*) ;} ;

/* Variables and functions */
 struct kvm_memory_slot* id_to_memslot (struct kvm_memslots*,int /*<<< orphan*/ ) ; 
 int kvm_get_dirty_log_protect (struct kvm*,struct kvm_dirty_log*,int*) ; 
 struct kvm_memslots* kvm_memslots (struct kvm*) ; 
 TYPE_1__* kvm_mips_callbacks ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct kvm*,struct kvm_memory_slot*) ; 

int kvm_vm_ioctl_get_dirty_log(struct kvm *kvm, struct kvm_dirty_log *log)
{
	struct kvm_memslots *slots;
	struct kvm_memory_slot *memslot;
	bool flush = false;
	int r;

	mutex_lock(&kvm->slots_lock);

	r = kvm_get_dirty_log_protect(kvm, log, &flush);

	if (flush) {
		slots = kvm_memslots(kvm);
		memslot = id_to_memslot(slots, log->slot);

		/* Let implementation handle TLB/GVA invalidation */
		kvm_mips_callbacks->flush_shadow_memslot(kvm, memslot);
	}

	mutex_unlock(&kvm->slots_lock);
	return r;
}