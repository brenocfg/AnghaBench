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
struct kvm_memslots {int used_slots; struct kvm_memory_slot* memslots; } ;
struct kvm_memory_slot {scalar_t__ npages; int /*<<< orphan*/  dirty_bitmap; } ;
struct TYPE_2__ {int migration_mode; int /*<<< orphan*/  cmma_dirty_pages; int /*<<< orphan*/  use_cmma; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KVM_REQ_START_MIGRATION ; 
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  kvm_dirty_bitmap_bytes (struct kvm_memory_slot*) ; 
 struct kvm_memslots* kvm_memslots (struct kvm*) ; 
 int /*<<< orphan*/  kvm_s390_sync_request_broadcast (struct kvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_second_dirty_bitmap (struct kvm_memory_slot*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvm_s390_vm_start_migration(struct kvm *kvm)
{
	struct kvm_memory_slot *ms;
	struct kvm_memslots *slots;
	unsigned long ram_pages = 0;
	int slotnr;

	/* migration mode already enabled */
	if (kvm->arch.migration_mode)
		return 0;
	slots = kvm_memslots(kvm);
	if (!slots || !slots->used_slots)
		return -EINVAL;

	if (!kvm->arch.use_cmma) {
		kvm->arch.migration_mode = 1;
		return 0;
	}
	/* mark all the pages in active slots as dirty */
	for (slotnr = 0; slotnr < slots->used_slots; slotnr++) {
		ms = slots->memslots + slotnr;
		if (!ms->dirty_bitmap)
			return -EINVAL;
		/*
		 * The second half of the bitmap is only used on x86,
		 * and would be wasted otherwise, so we put it to good
		 * use here to keep track of the state of the storage
		 * attributes.
		 */
		memset(kvm_second_dirty_bitmap(ms), 0xff, kvm_dirty_bitmap_bytes(ms));
		ram_pages += ms->npages;
	}
	atomic64_set(&kvm->arch.cmma_dirty_pages, ram_pages);
	kvm->arch.migration_mode = 1;
	kvm_s390_sync_request_broadcast(kvm, KVM_REQ_START_MIGRATION);
	return 0;
}