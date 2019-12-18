#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dec; int /*<<< orphan*/  vrsave; int /*<<< orphan*/  mcsr; int /*<<< orphan*/  csrr1; int /*<<< orphan*/  csrr0; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct TYPE_5__ {int features; int update_special; int /*<<< orphan*/  tsr; int /*<<< orphan*/  dec; int /*<<< orphan*/  tcr; int /*<<< orphan*/  vrsave; int /*<<< orphan*/  dear; int /*<<< orphan*/  esr; int /*<<< orphan*/  mcsr; int /*<<< orphan*/  csrr1; int /*<<< orphan*/  csrr0; } ;
struct TYPE_6__ {TYPE_2__ e; } ;
struct kvm_sregs {TYPE_3__ u; } ;

/* Variables and functions */
 int KVM_SREGS_E_BASE ; 
 int KVM_SREGS_E_UPDATE_DEC ; 
 int KVM_SREGS_E_UPDATE_TSR ; 
 int /*<<< orphan*/  kvmppc_emulate_dec (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_set_dar (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_set_esr (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_set_tcr (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_set_tsr (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_sregs_base(struct kvm_vcpu *vcpu,
                          struct kvm_sregs *sregs)
{
	if (!(sregs->u.e.features & KVM_SREGS_E_BASE))
		return 0;

	vcpu->arch.csrr0 = sregs->u.e.csrr0;
	vcpu->arch.csrr1 = sregs->u.e.csrr1;
	vcpu->arch.mcsr = sregs->u.e.mcsr;
	kvmppc_set_esr(vcpu, sregs->u.e.esr);
	kvmppc_set_dar(vcpu, sregs->u.e.dear);
	vcpu->arch.vrsave = sregs->u.e.vrsave;
	kvmppc_set_tcr(vcpu, sregs->u.e.tcr);

	if (sregs->u.e.update_special & KVM_SREGS_E_UPDATE_DEC) {
		vcpu->arch.dec = sregs->u.e.dec;
		kvmppc_emulate_dec(vcpu);
	}

	if (sregs->u.e.update_special & KVM_SREGS_E_UPDATE_TSR)
		kvmppc_set_tsr(vcpu, sregs->u.e.tsr);

	return 0;
}