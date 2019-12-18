#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* sie_block; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_3__ {int* gcr; } ;

/* Variables and functions */
 int MAX_ISC ; 
 unsigned long isc_to_irq_type (int) ; 
 int isc_to_isc_bits (int) ; 

__attribute__((used)) static unsigned long disable_iscs(struct kvm_vcpu *vcpu,
				   unsigned long active_mask)
{
	int i;

	for (i = 0; i <= MAX_ISC; i++)
		if (!(vcpu->arch.sie_block->gcr[6] & isc_to_isc_bits(i)))
			active_mask &= ~(1UL << (isc_to_irq_type(i)));

	return active_mask;
}