#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
struct TYPE_5__ {TYPE_3__* sie_block; } ;
struct TYPE_6__ {int /*<<< orphan*/  instruction_sck; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; TYPE_1__ arch; TYPE_2__ stat; } ;
struct kvm_s390_vm_tod_clock {int /*<<< orphan*/  tod; int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {int mask; } ;
struct TYPE_7__ {TYPE_4__ gpsw; } ;

/* Variables and functions */
 int /*<<< orphan*/  PGM_PRIVILEGED_OP ; 
 int /*<<< orphan*/  PGM_SPECIFICATION ; 
 int PSW_MASK_PSTATE ; 
 int /*<<< orphan*/  VCPU_EVENT (struct kvm_vcpu*,int,char*,int /*<<< orphan*/ ) ; 
 int kvm_s390_get_base_disp_s (struct kvm_vcpu*,int /*<<< orphan*/ *) ; 
 int kvm_s390_inject_prog_cond (struct kvm_vcpu*,int) ; 
 int kvm_s390_inject_program_int (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_s390_set_psw_cc (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_s390_set_tod_clock (int /*<<< orphan*/ ,struct kvm_s390_vm_tod_clock*) ; 
 int read_guest (struct kvm_vcpu*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int handle_set_clock(struct kvm_vcpu *vcpu)
{
	struct kvm_s390_vm_tod_clock gtod = { 0 };
	int rc;
	u8 ar;
	u64 op2;

	vcpu->stat.instruction_sck++;

	if (vcpu->arch.sie_block->gpsw.mask & PSW_MASK_PSTATE)
		return kvm_s390_inject_program_int(vcpu, PGM_PRIVILEGED_OP);

	op2 = kvm_s390_get_base_disp_s(vcpu, &ar);
	if (op2 & 7)	/* Operand must be on a doubleword boundary */
		return kvm_s390_inject_program_int(vcpu, PGM_SPECIFICATION);
	rc = read_guest(vcpu, op2, ar, &gtod.tod, sizeof(gtod.tod));
	if (rc)
		return kvm_s390_inject_prog_cond(vcpu, rc);

	VCPU_EVENT(vcpu, 3, "SCK: setting guest TOD to 0x%llx", gtod.tod);
	kvm_s390_set_tod_clock(vcpu->kvm, &gtod);

	kvm_s390_set_psw_cc(vcpu, 0);
	return 0;
}