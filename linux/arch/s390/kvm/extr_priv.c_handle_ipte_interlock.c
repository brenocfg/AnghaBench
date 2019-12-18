#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* sie_block; } ;
struct TYPE_7__ {int /*<<< orphan*/  instruction_ipte_interlock; } ;
struct kvm_vcpu {TYPE_5__* kvm; TYPE_3__ arch; TYPE_1__ stat; } ;
struct TYPE_12__ {scalar_t__ pstate; } ;
struct TYPE_10__ {int /*<<< orphan*/  ipte_wq; } ;
struct TYPE_11__ {TYPE_4__ arch; } ;
struct TYPE_8__ {int /*<<< orphan*/  gpsw; } ;

/* Variables and functions */
 int /*<<< orphan*/  PGM_PRIVILEGED_OP ; 
 int /*<<< orphan*/  VCPU_EVENT (struct kvm_vcpu*,int,char*,char*) ; 
 int /*<<< orphan*/  ipte_lock_held (struct kvm_vcpu*) ; 
 int kvm_s390_inject_program_int (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_s390_retry_instr (struct kvm_vcpu*) ; 
 TYPE_6__ psw_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int handle_ipte_interlock(struct kvm_vcpu *vcpu)
{
	vcpu->stat.instruction_ipte_interlock++;
	if (psw_bits(vcpu->arch.sie_block->gpsw).pstate)
		return kvm_s390_inject_program_int(vcpu, PGM_PRIVILEGED_OP);
	wait_event(vcpu->kvm->arch.ipte_wq, !ipte_lock_held(vcpu));
	kvm_s390_retry_instr(vcpu);
	VCPU_EVENT(vcpu, 4, "%s", "retrying ipte interlock operation");
	return 0;
}