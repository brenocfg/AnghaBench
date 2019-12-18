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
struct kvm_vcpu {int /*<<< orphan*/  guest_debug; TYPE_1__* run; } ;
struct TYPE_2__ {int /*<<< orphan*/  exit_reason; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_EXIT_DEBUG ; 
 int /*<<< orphan*/  KVM_GUESTDBG_EXIT_PENDING ; 

void kvm_s390_prepare_debug_exit(struct kvm_vcpu *vcpu)
{
	vcpu->run->exit_reason = KVM_EXIT_DEBUG;
	vcpu->guest_debug &= ~KVM_GUESTDBG_EXIT_PENDING;
}