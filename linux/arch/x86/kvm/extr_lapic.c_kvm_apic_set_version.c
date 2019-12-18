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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {struct kvm_lapic* apic; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; TYPE_1__ arch; } ;
struct kvm_lapic {int /*<<< orphan*/  vcpu; } ;
struct kvm_cpuid_entry2 {int ecx; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_LVR ; 
 int /*<<< orphan*/  APIC_LVR_DIRECTED_EOI ; 
 int /*<<< orphan*/  APIC_VERSION ; 
 int X86_FEATURE_X2APIC ; 
 int /*<<< orphan*/  ioapic_in_kernel (int /*<<< orphan*/ ) ; 
 struct kvm_cpuid_entry2* kvm_find_cpuid_entry (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_lapic_set_reg (struct kvm_lapic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lapic_in_kernel (struct kvm_vcpu*) ; 

void kvm_apic_set_version(struct kvm_vcpu *vcpu)
{
	struct kvm_lapic *apic = vcpu->arch.apic;
	struct kvm_cpuid_entry2 *feat;
	u32 v = APIC_VERSION;

	if (!lapic_in_kernel(vcpu))
		return;

	/*
	 * KVM emulates 82093AA datasheet (with in-kernel IOAPIC implementation)
	 * which doesn't have EOI register; Some buggy OSes (e.g. Windows with
	 * Hyper-V role) disable EOI broadcast in lapic not checking for IOAPIC
	 * version first and level-triggered interrupts never get EOIed in
	 * IOAPIC.
	 */
	feat = kvm_find_cpuid_entry(apic->vcpu, 0x1, 0);
	if (feat && (feat->ecx & (1 << (X86_FEATURE_X2APIC & 31))) &&
	    !ioapic_in_kernel(vcpu->kvm))
		v |= APIC_LVR_DIRECTED_EOI;
	kvm_lapic_set_reg(apic, APIC_LVR, v);
}