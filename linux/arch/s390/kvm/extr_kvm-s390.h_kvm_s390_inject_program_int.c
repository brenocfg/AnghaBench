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
typedef  int /*<<< orphan*/  u16 ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  code; } ;
struct TYPE_4__ {TYPE_1__ pgm; } ;
struct kvm_s390_irq {TYPE_2__ u; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_S390_PROGRAM_INT ; 
 int kvm_s390_inject_vcpu (struct kvm_vcpu*,struct kvm_s390_irq*) ; 

__attribute__((used)) static inline int kvm_s390_inject_program_int(struct kvm_vcpu *vcpu, u16 code)
{
	struct kvm_s390_irq irq = {
		.type = KVM_S390_PROGRAM_INT,
		.u.pgm.code = code,
	};

	return kvm_s390_inject_vcpu(vcpu, &irq);
}