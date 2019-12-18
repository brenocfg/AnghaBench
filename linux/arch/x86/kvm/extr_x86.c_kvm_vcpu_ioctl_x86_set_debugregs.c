#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int dr6; int dr7; int /*<<< orphan*/  db; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_debugregs {int dr6; int dr7; int /*<<< orphan*/  db; scalar_t__ flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  kvm_update_dr0123 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_update_dr6 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_update_dr7 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int kvm_vcpu_ioctl_x86_set_debugregs(struct kvm_vcpu *vcpu,
					    struct kvm_debugregs *dbgregs)
{
	if (dbgregs->flags)
		return -EINVAL;

	if (dbgregs->dr6 & ~0xffffffffull)
		return -EINVAL;
	if (dbgregs->dr7 & ~0xffffffffull)
		return -EINVAL;

	memcpy(vcpu->arch.db, dbgregs->db, sizeof(vcpu->arch.db));
	kvm_update_dr0123(vcpu);
	vcpu->arch.dr6 = dbgregs->dr6;
	kvm_update_dr6(vcpu);
	vcpu->arch.dr7 = dbgregs->dr7;
	kvm_update_dr7(vcpu);

	return 0;
}