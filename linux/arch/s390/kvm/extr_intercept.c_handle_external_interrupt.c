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
typedef  int u16 ;
struct TYPE_11__ {TYPE_5__* sie_block; } ;
struct TYPE_8__ {int /*<<< orphan*/  exit_external_interrupt; } ;
struct kvm_vcpu {TYPE_4__ arch; TYPE_1__ stat; } ;
struct TYPE_9__ {int /*<<< orphan*/  code; } ;
struct TYPE_10__ {TYPE_2__ extcall; } ;
struct kvm_s390_irq {TYPE_3__ u; int /*<<< orphan*/  type; } ;
struct TYPE_13__ {int mask; } ;
typedef  TYPE_6__ psw_t ;
struct TYPE_12__ {int eic; int /*<<< orphan*/  extcpuaddr; } ;

/* Variables and functions */
 int EBUSY ; 
 int EOPNOTSUPP ; 
#define  EXT_IRQ_CLK_COMP 130 
#define  EXT_IRQ_CPU_TIMER 129 
#define  EXT_IRQ_EXTERNAL_CALL 128 
 int /*<<< orphan*/  KVM_S390_INT_CLOCK_COMP ; 
 int /*<<< orphan*/  KVM_S390_INT_CPU_TIMER ; 
 int /*<<< orphan*/  KVM_S390_INT_EXTERNAL_CALL ; 
 int PSW_MASK_EXT ; 
 int /*<<< orphan*/  __LC_EXT_NEW_PSW ; 
 int kvm_s390_inject_vcpu (struct kvm_vcpu*,struct kvm_s390_irq*) ; 
 int read_guest_lc (struct kvm_vcpu*,int /*<<< orphan*/ ,TYPE_6__*,int) ; 

__attribute__((used)) static int handle_external_interrupt(struct kvm_vcpu *vcpu)
{
	u16 eic = vcpu->arch.sie_block->eic;
	struct kvm_s390_irq irq;
	psw_t newpsw;
	int rc;

	vcpu->stat.exit_external_interrupt++;

	rc = read_guest_lc(vcpu, __LC_EXT_NEW_PSW, &newpsw, sizeof(psw_t));
	if (rc)
		return rc;
	/* We can not handle clock comparator or timer interrupt with bad PSW */
	if ((eic == EXT_IRQ_CLK_COMP || eic == EXT_IRQ_CPU_TIMER) &&
	    (newpsw.mask & PSW_MASK_EXT))
		return -EOPNOTSUPP;

	switch (eic) {
	case EXT_IRQ_CLK_COMP:
		irq.type = KVM_S390_INT_CLOCK_COMP;
		break;
	case EXT_IRQ_CPU_TIMER:
		irq.type = KVM_S390_INT_CPU_TIMER;
		break;
	case EXT_IRQ_EXTERNAL_CALL:
		irq.type = KVM_S390_INT_EXTERNAL_CALL;
		irq.u.extcall.code = vcpu->arch.sie_block->extcpuaddr;
		rc = kvm_s390_inject_vcpu(vcpu, &irq);
		/* ignore if another external call is already pending */
		if (rc == -EBUSY)
			return 0;
		return rc;
	default:
		return -EOPNOTSUPP;
	}

	return kvm_s390_inject_vcpu(vcpu, &irq);
}