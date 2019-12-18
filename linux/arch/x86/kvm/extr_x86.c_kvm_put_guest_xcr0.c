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
struct TYPE_2__ {scalar_t__ xcr0; } ;
struct kvm_vcpu {scalar_t__ guest_xcr0_loaded; TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  XCR_XFEATURE_ENABLED_MASK ; 
 scalar_t__ host_xcr0 ; 
 int /*<<< orphan*/  xsetbv (int /*<<< orphan*/ ,scalar_t__) ; 

void kvm_put_guest_xcr0(struct kvm_vcpu *vcpu)
{
	if (vcpu->guest_xcr0_loaded) {
		if (vcpu->arch.xcr0 != host_xcr0)
			xsetbv(XCR_XFEATURE_ENABLED_MASK, host_xcr0);
		vcpu->guest_xcr0_loaded = 0;
	}
}