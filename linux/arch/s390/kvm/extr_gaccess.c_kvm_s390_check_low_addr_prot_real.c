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
union ctlreg0 {int /*<<< orphan*/  lap; int /*<<< orphan*/  val; } ;
struct TYPE_4__ {TYPE_1__* sie_block; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_3__ {int /*<<< orphan*/ * gcr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GACC_STORE ; 
 int /*<<< orphan*/  PGM_PROTECTION ; 
 int /*<<< orphan*/  PROT_TYPE_LA ; 
 int /*<<< orphan*/  is_low_address (unsigned long) ; 
 int trans_exc (struct kvm_vcpu*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int kvm_s390_check_low_addr_prot_real(struct kvm_vcpu *vcpu, unsigned long gra)
{
	union ctlreg0 ctlreg0 = {.val = vcpu->arch.sie_block->gcr[0]};

	if (!ctlreg0.lap || !is_low_address(gra))
		return 0;
	return trans_exc(vcpu, PGM_PROTECTION, gra, 0, GACC_STORE, PROT_TYPE_LA);
}