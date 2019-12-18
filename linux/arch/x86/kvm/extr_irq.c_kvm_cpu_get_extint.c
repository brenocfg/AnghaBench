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
struct TYPE_2__ {int pending_external_vector; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; TYPE_1__ arch; } ;

/* Variables and functions */
 scalar_t__ irqchip_split (int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_cpu_has_extint (struct kvm_vcpu*) ; 
 int kvm_pic_read_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvm_cpu_get_extint(struct kvm_vcpu *v)
{
	if (kvm_cpu_has_extint(v)) {
		if (irqchip_split(v->kvm)) {
			int vector = v->arch.pending_external_vector;

			v->arch.pending_external_vector = -1;
			return vector;
		} else
			return kvm_pic_read_irq(v->kvm); /* PIC */
	} else
		return -1;
}