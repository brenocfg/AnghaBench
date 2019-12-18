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
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 scalar_t__ emulate_invalid_guest_state ; 
 int /*<<< orphan*/  guest_state_valid (struct kvm_vcpu*) ; 

__attribute__((used)) static bool emulation_required(struct kvm_vcpu *vcpu)
{
	return emulate_invalid_guest_state && !guest_state_valid(vcpu);
}