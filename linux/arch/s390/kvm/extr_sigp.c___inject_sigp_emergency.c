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
struct kvm_vcpu {int /*<<< orphan*/  vcpu_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  code; } ;
struct TYPE_4__ {TYPE_1__ emerg; } ;
struct kvm_s390_irq {TYPE_2__ u; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_S390_INT_EMERGENCY ; 
 int SIGP_CC_ORDER_CODE_ACCEPTED ; 
 int /*<<< orphan*/  VCPU_EVENT (struct kvm_vcpu*,int,char*,int /*<<< orphan*/ ) ; 
 int kvm_s390_inject_vcpu (struct kvm_vcpu*,struct kvm_s390_irq*) ; 

__attribute__((used)) static int __inject_sigp_emergency(struct kvm_vcpu *vcpu,
				    struct kvm_vcpu *dst_vcpu)
{
	struct kvm_s390_irq irq = {
		.type = KVM_S390_INT_EMERGENCY,
		.u.emerg.code = vcpu->vcpu_id,
	};
	int rc = 0;

	rc = kvm_s390_inject_vcpu(dst_vcpu, &irq);
	if (!rc)
		VCPU_EVENT(vcpu, 4, "sent sigp emerg to cpu %x",
			   dst_vcpu->vcpu_id);

	return rc ? rc : SIGP_CC_ORDER_CODE_ACCEPTED;
}