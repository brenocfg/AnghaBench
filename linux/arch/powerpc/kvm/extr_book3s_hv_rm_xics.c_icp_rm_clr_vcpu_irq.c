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
struct TYPE_2__ {int /*<<< orphan*/  pending_exceptions; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOOK3S_IRQPRIO_EXTERNAL ; 
 int LPCR_MER ; 
 int /*<<< orphan*/  SPRN_LPCR ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void icp_rm_clr_vcpu_irq(struct kvm_vcpu *vcpu)
{
	/* Note: Only called on self ! */
	clear_bit(BOOK3S_IRQPRIO_EXTERNAL, &vcpu->arch.pending_exceptions);
	mtspr(SPRN_LPCR, mfspr(SPRN_LPCR) & ~LPCR_MER);
}