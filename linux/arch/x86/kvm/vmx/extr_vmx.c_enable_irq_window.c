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
 int /*<<< orphan*/  CPU_BASED_VIRTUAL_INTR_PENDING ; 
 int /*<<< orphan*/  exec_controls_setbit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_vmx (struct kvm_vcpu*) ; 

__attribute__((used)) static void enable_irq_window(struct kvm_vcpu *vcpu)
{
	exec_controls_setbit(to_vmx(vcpu), CPU_BASED_VIRTUAL_INTR_PENDING);
}