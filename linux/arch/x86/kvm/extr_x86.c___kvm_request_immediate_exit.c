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
struct kvm_vcpu {int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  smp_send_reschedule (int /*<<< orphan*/ ) ; 

void __kvm_request_immediate_exit(struct kvm_vcpu *vcpu)
{
	smp_send_reschedule(vcpu->cpu);
}