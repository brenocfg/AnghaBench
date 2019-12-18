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
typedef  scalar_t__ u32 ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;
struct kvm_lapic {scalar_t__ base_address; } ;
struct kvm_io_device {int dummy; } ;
typedef  scalar_t__ gpa_t ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  KVM_X86_QUIRK_LAPIC_MMIO_HOLE ; 
 int /*<<< orphan*/  apic_mmio_in_range (struct kvm_lapic*,scalar_t__) ; 
 scalar_t__ apic_x2apic_mode (struct kvm_lapic*) ; 
 int /*<<< orphan*/  kvm_apic_hw_enabled (struct kvm_lapic*) ; 
 int /*<<< orphan*/  kvm_check_has_quirk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_lapic_reg_read (struct kvm_lapic*,scalar_t__,int,void*) ; 
 int /*<<< orphan*/  memset (void*,int,int) ; 
 struct kvm_lapic* to_lapic (struct kvm_io_device*) ; 

__attribute__((used)) static int apic_mmio_read(struct kvm_vcpu *vcpu, struct kvm_io_device *this,
			   gpa_t address, int len, void *data)
{
	struct kvm_lapic *apic = to_lapic(this);
	u32 offset = address - apic->base_address;

	if (!apic_mmio_in_range(apic, address))
		return -EOPNOTSUPP;

	if (!kvm_apic_hw_enabled(apic) || apic_x2apic_mode(apic)) {
		if (!kvm_check_has_quirk(vcpu->kvm,
					 KVM_X86_QUIRK_LAPIC_MMIO_HOLE))
			return -EOPNOTSUPP;

		memset(data, 0xff, len);
		return 0;
	}

	kvm_lapic_reg_read(apic, offset, len, data);

	return 0;
}