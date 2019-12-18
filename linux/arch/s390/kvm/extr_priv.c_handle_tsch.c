#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_16__ {TYPE_7__* sie_block; } ;
struct TYPE_9__ {int /*<<< orphan*/  instruction_tsch; } ;
struct kvm_vcpu {TYPE_8__ arch; TYPE_6__* run; int /*<<< orphan*/  kvm; TYPE_1__ stat; } ;
struct TYPE_12__ {int /*<<< orphan*/  io_int_word; int /*<<< orphan*/  io_int_parm; int /*<<< orphan*/  subchannel_nr; int /*<<< orphan*/  subchannel_id; } ;
struct kvm_s390_interrupt_info {TYPE_4__ io; } ;
struct TYPE_15__ {int /*<<< orphan*/  ipb; } ;
struct TYPE_13__ {int dequeued; int /*<<< orphan*/  ipb; int /*<<< orphan*/  io_int_word; int /*<<< orphan*/  io_int_parm; int /*<<< orphan*/  subchannel_nr; int /*<<< orphan*/  subchannel_id; } ;
struct TYPE_10__ {int /*<<< orphan*/ * gprs; } ;
struct TYPE_11__ {TYPE_2__ regs; } ;
struct TYPE_14__ {TYPE_5__ s390_tsch; int /*<<< orphan*/  exit_reason; TYPE_3__ s; } ;

/* Variables and functions */
 int EREMOTE ; 
 int /*<<< orphan*/  KVM_EXIT_S390_TSCH ; 
 int /*<<< orphan*/  kfree (struct kvm_s390_interrupt_info*) ; 
 struct kvm_s390_interrupt_info* kvm_s390_get_io_int (int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_tsch(struct kvm_vcpu *vcpu)
{
	struct kvm_s390_interrupt_info *inti = NULL;
	const u64 isc_mask = 0xffUL << 24; /* all iscs set */

	vcpu->stat.instruction_tsch++;

	/* a valid schid has at least one bit set */
	if (vcpu->run->s.regs.gprs[1])
		inti = kvm_s390_get_io_int(vcpu->kvm, isc_mask,
					   vcpu->run->s.regs.gprs[1]);

	/*
	 * Prepare exit to userspace.
	 * We indicate whether we dequeued a pending I/O interrupt
	 * so that userspace can re-inject it if the instruction gets
	 * a program check. While this may re-order the pending I/O
	 * interrupts, this is no problem since the priority is kept
	 * intact.
	 */
	vcpu->run->exit_reason = KVM_EXIT_S390_TSCH;
	vcpu->run->s390_tsch.dequeued = !!inti;
	if (inti) {
		vcpu->run->s390_tsch.subchannel_id = inti->io.subchannel_id;
		vcpu->run->s390_tsch.subchannel_nr = inti->io.subchannel_nr;
		vcpu->run->s390_tsch.io_int_parm = inti->io.io_int_parm;
		vcpu->run->s390_tsch.io_int_word = inti->io.io_int_word;
	}
	vcpu->run->s390_tsch.ipb = vcpu->arch.sie_block->ipb;
	kfree(inti);
	return -EREMOTE;
}