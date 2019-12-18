#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int guest_can_read_msr_platform_info; int /*<<< orphan*/  kvmclock_sync_work; int /*<<< orphan*/  kvmclock_update_work; int /*<<< orphan*/  kvmclock_offset; int /*<<< orphan*/  pvclock_gtod_sync_lock; int /*<<< orphan*/  apic_map_lock; int /*<<< orphan*/  tsc_write_lock; int /*<<< orphan*/  irq_sources_bitmap; int /*<<< orphan*/  noncoherent_dma_count; int /*<<< orphan*/  assigned_dev_head; int /*<<< orphan*/  lpage_disallowed_mmu_pages; int /*<<< orphan*/  zapped_obsolete_pages; int /*<<< orphan*/  active_mmu_pages; int /*<<< orphan*/  mask_notifier_list; } ;
struct kvm {TYPE_1__ arch; } ;
struct TYPE_4__ {int (* vm_init ) (struct kvm*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KVM_IRQFD_RESAMPLE_IRQ_SOURCE_ID ; 
 int /*<<< orphan*/  KVM_USERSPACE_IRQ_SOURCE_ID ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_boottime_ns () ; 
 int /*<<< orphan*/  kvm_hv_init_vm (struct kvm*) ; 
 int /*<<< orphan*/  kvm_mmu_init_vm (struct kvm*) ; 
 int /*<<< orphan*/  kvm_page_track_init (struct kvm*) ; 
 TYPE_2__* kvm_x86_ops ; 
 int /*<<< orphan*/  kvmclock_sync_fn ; 
 int /*<<< orphan*/  kvmclock_update_fn ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pvclock_update_vm_gtod_copy (struct kvm*) ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int stub1 (struct kvm*) ; 

int kvm_arch_init_vm(struct kvm *kvm, unsigned long type)
{
	if (type)
		return -EINVAL;

	INIT_HLIST_HEAD(&kvm->arch.mask_notifier_list);
	INIT_LIST_HEAD(&kvm->arch.active_mmu_pages);
	INIT_LIST_HEAD(&kvm->arch.zapped_obsolete_pages);
	INIT_LIST_HEAD(&kvm->arch.lpage_disallowed_mmu_pages);
	INIT_LIST_HEAD(&kvm->arch.assigned_dev_head);
	atomic_set(&kvm->arch.noncoherent_dma_count, 0);

	/* Reserve bit 0 of irq_sources_bitmap for userspace irq source */
	set_bit(KVM_USERSPACE_IRQ_SOURCE_ID, &kvm->arch.irq_sources_bitmap);
	/* Reserve bit 1 of irq_sources_bitmap for irqfd-resampler */
	set_bit(KVM_IRQFD_RESAMPLE_IRQ_SOURCE_ID,
		&kvm->arch.irq_sources_bitmap);

	raw_spin_lock_init(&kvm->arch.tsc_write_lock);
	mutex_init(&kvm->arch.apic_map_lock);
	spin_lock_init(&kvm->arch.pvclock_gtod_sync_lock);

	kvm->arch.kvmclock_offset = -ktime_get_boottime_ns();
	pvclock_update_vm_gtod_copy(kvm);

	kvm->arch.guest_can_read_msr_platform_info = true;

	INIT_DELAYED_WORK(&kvm->arch.kvmclock_update_work, kvmclock_update_fn);
	INIT_DELAYED_WORK(&kvm->arch.kvmclock_sync_work, kvmclock_sync_fn);

	kvm_hv_init_vm(kvm);
	kvm_page_track_init(kvm);
	kvm_mmu_init_vm(kvm);

	return kvm_x86_ops->vm_init(kvm);
}