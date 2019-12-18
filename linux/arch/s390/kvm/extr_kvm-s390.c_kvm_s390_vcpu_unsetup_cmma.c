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
struct TYPE_3__ {scalar_t__ cbrlo; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_page (scalar_t__) ; 

void kvm_s390_vcpu_unsetup_cmma(struct kvm_vcpu *vcpu)
{
	free_page(vcpu->arch.sie_block->cbrlo);
	vcpu->arch.sie_block->cbrlo = 0;
}