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
struct TYPE_2__ {int /*<<< orphan*/  apic_vector; } ;
struct kvm_vcpu_hv_stimer {TYPE_1__ config; } ;
struct kvm_vcpu {int dummy; } ;
struct kvm_lapic_irq {int /*<<< orphan*/  vector; int /*<<< orphan*/  delivery_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_DM_FIXED ; 
 int /*<<< orphan*/  kvm_apic_set_irq (struct kvm_vcpu*,struct kvm_lapic_irq*,int /*<<< orphan*/ *) ; 
 scalar_t__ lapic_in_kernel (struct kvm_vcpu*) ; 
 struct kvm_vcpu* stimer_to_vcpu (struct kvm_vcpu_hv_stimer*) ; 

__attribute__((used)) static int stimer_notify_direct(struct kvm_vcpu_hv_stimer *stimer)
{
	struct kvm_vcpu *vcpu = stimer_to_vcpu(stimer);
	struct kvm_lapic_irq irq = {
		.delivery_mode = APIC_DM_FIXED,
		.vector = stimer->config.apic_vector
	};

	if (lapic_in_kernel(vcpu))
		return !kvm_apic_set_irq(vcpu, &irq, NULL);
	return 0;
}