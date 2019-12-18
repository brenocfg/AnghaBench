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
struct kvm_enable_cap {int cap; int* args; scalar_t__ flags; } ;
struct TYPE_2__ {int disabled_quirks; int nr_reserved_ioapic_pins; int x2apic_format; int x2apic_broadcast_quirk_disabled; int mwait_in_guest; int hlt_in_guest; int pause_in_guest; int cstate_in_guest; int guest_can_read_msr_platform_info; int exception_payload_enabled; int /*<<< orphan*/  irqchip_mode; } ;
struct kvm {TYPE_1__ arch; int /*<<< orphan*/  lock; int /*<<< orphan*/  created_vcpus; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
#define  KVM_CAP_DISABLE_QUIRKS 133 
#define  KVM_CAP_EXCEPTION_PAYLOAD 132 
#define  KVM_CAP_MSR_PLATFORM_INFO 131 
#define  KVM_CAP_SPLIT_IRQCHIP 130 
#define  KVM_CAP_X2APIC_API 129 
#define  KVM_CAP_X86_DISABLE_EXITS 128 
 int /*<<< orphan*/  KVM_IRQCHIP_SPLIT ; 
 int KVM_X2APIC_API_DISABLE_BROADCAST_QUIRK ; 
 int KVM_X2APIC_API_USE_32BIT_IDS ; 
 int KVM_X2APIC_API_VALID_FLAGS ; 
 int KVM_X86_DISABLE_EXITS_CSTATE ; 
 int KVM_X86_DISABLE_EXITS_HLT ; 
 int KVM_X86_DISABLE_EXITS_MWAIT ; 
 int KVM_X86_DISABLE_EXITS_PAUSE ; 
 int KVM_X86_DISABLE_VALID_EXITS ; 
 int MAX_NR_RESERVED_IOAPIC_PINS ; 
 int /*<<< orphan*/  irqchip_in_kernel (struct kvm*) ; 
 int /*<<< orphan*/  kvm_can_mwait_in_guest () ; 
 int kvm_setup_empty_irq_routing (struct kvm*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_wmb () ; 

int kvm_vm_ioctl_enable_cap(struct kvm *kvm,
			    struct kvm_enable_cap *cap)
{
	int r;

	if (cap->flags)
		return -EINVAL;

	switch (cap->cap) {
	case KVM_CAP_DISABLE_QUIRKS:
		kvm->arch.disabled_quirks = cap->args[0];
		r = 0;
		break;
	case KVM_CAP_SPLIT_IRQCHIP: {
		mutex_lock(&kvm->lock);
		r = -EINVAL;
		if (cap->args[0] > MAX_NR_RESERVED_IOAPIC_PINS)
			goto split_irqchip_unlock;
		r = -EEXIST;
		if (irqchip_in_kernel(kvm))
			goto split_irqchip_unlock;
		if (kvm->created_vcpus)
			goto split_irqchip_unlock;
		r = kvm_setup_empty_irq_routing(kvm);
		if (r)
			goto split_irqchip_unlock;
		/* Pairs with irqchip_in_kernel. */
		smp_wmb();
		kvm->arch.irqchip_mode = KVM_IRQCHIP_SPLIT;
		kvm->arch.nr_reserved_ioapic_pins = cap->args[0];
		r = 0;
split_irqchip_unlock:
		mutex_unlock(&kvm->lock);
		break;
	}
	case KVM_CAP_X2APIC_API:
		r = -EINVAL;
		if (cap->args[0] & ~KVM_X2APIC_API_VALID_FLAGS)
			break;

		if (cap->args[0] & KVM_X2APIC_API_USE_32BIT_IDS)
			kvm->arch.x2apic_format = true;
		if (cap->args[0] & KVM_X2APIC_API_DISABLE_BROADCAST_QUIRK)
			kvm->arch.x2apic_broadcast_quirk_disabled = true;

		r = 0;
		break;
	case KVM_CAP_X86_DISABLE_EXITS:
		r = -EINVAL;
		if (cap->args[0] & ~KVM_X86_DISABLE_VALID_EXITS)
			break;

		if ((cap->args[0] & KVM_X86_DISABLE_EXITS_MWAIT) &&
			kvm_can_mwait_in_guest())
			kvm->arch.mwait_in_guest = true;
		if (cap->args[0] & KVM_X86_DISABLE_EXITS_HLT)
			kvm->arch.hlt_in_guest = true;
		if (cap->args[0] & KVM_X86_DISABLE_EXITS_PAUSE)
			kvm->arch.pause_in_guest = true;
		if (cap->args[0] & KVM_X86_DISABLE_EXITS_CSTATE)
			kvm->arch.cstate_in_guest = true;
		r = 0;
		break;
	case KVM_CAP_MSR_PLATFORM_INFO:
		kvm->arch.guest_can_read_msr_platform_info = cap->args[0];
		r = 0;
		break;
	case KVM_CAP_EXCEPTION_PAYLOAD:
		kvm->arch.exception_payload_enabled = cap->args[0];
		r = 0;
		break;
	default:
		r = -EINVAL;
		break;
	}
	return r;
}