#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_4__* sie_block; } ;
struct TYPE_8__ {int /*<<< orphan*/  exit_operation_exception; } ;
struct kvm_vcpu {TYPE_5__ arch; TYPE_3__* kvm; TYPE_1__ stat; } ;
struct TYPE_13__ {int addr; int mask; } ;
typedef  TYPE_6__ psw_t ;
struct TYPE_11__ {int ipa; TYPE_6__ gpsw; int /*<<< orphan*/  ipb; } ;
struct TYPE_9__ {scalar_t__ user_instr0; } ;
struct TYPE_10__ {TYPE_2__ arch; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  PGM_OPERATION ; 
 int PSW_MASK_ASC ; 
 int PSW_MASK_DAT ; 
 int PSW_MASK_PSTATE ; 
 int PSW_MASK_WAIT ; 
 int /*<<< orphan*/  __LC_PGM_NEW_PSW ; 
 int handle_sthyi (struct kvm_vcpu*) ; 
 int kvm_s390_inject_program_int (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int read_guest_lc (struct kvm_vcpu*,int /*<<< orphan*/ ,TYPE_6__*,int) ; 
 int /*<<< orphan*/  trace_kvm_s390_handle_operexc (struct kvm_vcpu*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_operexc(struct kvm_vcpu *vcpu)
{
	psw_t oldpsw, newpsw;
	int rc;

	vcpu->stat.exit_operation_exception++;
	trace_kvm_s390_handle_operexc(vcpu, vcpu->arch.sie_block->ipa,
				      vcpu->arch.sie_block->ipb);

	if (vcpu->arch.sie_block->ipa == 0xb256)
		return handle_sthyi(vcpu);

	if (vcpu->arch.sie_block->ipa == 0 && vcpu->kvm->arch.user_instr0)
		return -EOPNOTSUPP;
	rc = read_guest_lc(vcpu, __LC_PGM_NEW_PSW, &newpsw, sizeof(psw_t));
	if (rc)
		return rc;
	/*
	 * Avoid endless loops of operation exceptions, if the pgm new
	 * PSW will cause a new operation exception.
	 * The heuristic checks if the pgm new psw is within 6 bytes before
	 * the faulting psw address (with same DAT, AS settings) and the
	 * new psw is not a wait psw and the fault was not triggered by
	 * problem state.
	 */
	oldpsw = vcpu->arch.sie_block->gpsw;
	if (oldpsw.addr - newpsw.addr <= 6 &&
	    !(newpsw.mask & PSW_MASK_WAIT) &&
	    !(oldpsw.mask & PSW_MASK_PSTATE) &&
	    (newpsw.mask & PSW_MASK_ASC) == (oldpsw.mask & PSW_MASK_ASC) &&
	    (newpsw.mask & PSW_MASK_DAT) == (oldpsw.mask & PSW_MASK_DAT))
		return -EOPNOTSUPP;

	return kvm_s390_inject_program_int(vcpu, PGM_OPERATION);
}