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
struct kvm_mips_interrupt {scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPS_EXC_INT_IO ; 
 int /*<<< orphan*/  MIPS_EXC_INT_IPI_1 ; 
 int /*<<< orphan*/  MIPS_EXC_INT_IPI_2 ; 
 int /*<<< orphan*/  kvm_vz_queue_irq (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvm_vz_queue_io_int_cb(struct kvm_vcpu *vcpu,
				   struct kvm_mips_interrupt *irq)
{
	int intr = (int)irq->irq;

	/*
	 * interrupts are asynchronous to vcpu execution therefore defer guest
	 * cp0 accesses
	 */
	switch (intr) {
	case 2:
		kvm_vz_queue_irq(vcpu, MIPS_EXC_INT_IO);
		break;

	case 3:
		kvm_vz_queue_irq(vcpu, MIPS_EXC_INT_IPI_1);
		break;

	case 4:
		kvm_vz_queue_irq(vcpu, MIPS_EXC_INT_IPI_2);
		break;

	default:
		break;
	}

}