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
struct kvm_pic_state {int dummy; } ;
struct kvm_pic {int /*<<< orphan*/  lock; int /*<<< orphan*/ * pics; } ;
struct TYPE_4__ {int /*<<< orphan*/  ioapic; int /*<<< orphan*/  pic; } ;
struct kvm_irqchip {int chip_id; TYPE_2__ chip; } ;
struct TYPE_3__ {struct kvm_pic* vpic; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int EINVAL ; 
#define  KVM_IRQCHIP_IOAPIC 130 
#define  KVM_IRQCHIP_PIC_MASTER 129 
#define  KVM_IRQCHIP_PIC_SLAVE 128 
 int /*<<< orphan*/  kvm_pic_update_irq (struct kvm_pic*) ; 
 int /*<<< orphan*/  kvm_set_ioapic (struct kvm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kvm_vm_ioctl_set_irqchip(struct kvm *kvm, struct kvm_irqchip *chip)
{
	struct kvm_pic *pic = kvm->arch.vpic;
	int r;

	r = 0;
	switch (chip->chip_id) {
	case KVM_IRQCHIP_PIC_MASTER:
		spin_lock(&pic->lock);
		memcpy(&pic->pics[0], &chip->chip.pic,
			sizeof(struct kvm_pic_state));
		spin_unlock(&pic->lock);
		break;
	case KVM_IRQCHIP_PIC_SLAVE:
		spin_lock(&pic->lock);
		memcpy(&pic->pics[1], &chip->chip.pic,
			sizeof(struct kvm_pic_state));
		spin_unlock(&pic->lock);
		break;
	case KVM_IRQCHIP_IOAPIC:
		kvm_set_ioapic(kvm, &chip->chip.ioapic);
		break;
	default:
		r = -EINVAL;
		break;
	}
	kvm_pic_update_irq(pic);
	return r;
}