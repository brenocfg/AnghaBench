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
union asce {int r; scalar_t__ val; } ;
typedef  int /*<<< orphan*/  u8 ;
struct psw_bits {int as; int /*<<< orphan*/  dat; } ;
struct TYPE_4__ {TYPE_1__* sie_block; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
typedef  enum gacc_mode { ____Placeholder_gacc_mode } gacc_mode ;
struct TYPE_3__ {scalar_t__* gcr; int /*<<< orphan*/  gpsw; } ;

/* Variables and functions */
 int GACC_IFETCH ; 
 int /*<<< orphan*/  PROT_TYPE_ALC ; 
#define  PSW_BITS_AS_ACCREG 131 
#define  PSW_BITS_AS_HOME 130 
#define  PSW_BITS_AS_PRIMARY 129 
#define  PSW_BITS_AS_SECONDARY 128 
 int ar_translation (struct kvm_vcpu*,union asce*,int /*<<< orphan*/ ,int) ; 
 struct psw_bits psw_bits (int /*<<< orphan*/ ) ; 
 int trans_exc (struct kvm_vcpu*,int,unsigned long,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_vcpu_asce(struct kvm_vcpu *vcpu, union asce *asce,
			 unsigned long ga, u8 ar, enum gacc_mode mode)
{
	int rc;
	struct psw_bits psw = psw_bits(vcpu->arch.sie_block->gpsw);

	if (!psw.dat) {
		asce->val = 0;
		asce->r = 1;
		return 0;
	}

	if ((mode == GACC_IFETCH) && (psw.as != PSW_BITS_AS_HOME))
		psw.as = PSW_BITS_AS_PRIMARY;

	switch (psw.as) {
	case PSW_BITS_AS_PRIMARY:
		asce->val = vcpu->arch.sie_block->gcr[1];
		return 0;
	case PSW_BITS_AS_SECONDARY:
		asce->val = vcpu->arch.sie_block->gcr[7];
		return 0;
	case PSW_BITS_AS_HOME:
		asce->val = vcpu->arch.sie_block->gcr[13];
		return 0;
	case PSW_BITS_AS_ACCREG:
		rc = ar_translation(vcpu, asce, ar, mode);
		if (rc > 0)
			return trans_exc(vcpu, rc, ga, ar, mode, PROT_TYPE_ALC);
		return rc;
	}
	return 0;
}