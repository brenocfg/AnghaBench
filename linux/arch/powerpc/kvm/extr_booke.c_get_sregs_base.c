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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_6__ {int /*<<< orphan*/  vrsave; int /*<<< orphan*/  tcr; int /*<<< orphan*/  tsr; int /*<<< orphan*/  mcsr; int /*<<< orphan*/  csrr1; int /*<<< orphan*/  csrr0; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;
struct TYPE_4__ {int /*<<< orphan*/  vrsave; int /*<<< orphan*/  tb; int /*<<< orphan*/  dec; int /*<<< orphan*/  tcr; int /*<<< orphan*/  tsr; int /*<<< orphan*/  dear; int /*<<< orphan*/  esr; int /*<<< orphan*/  mcsr; int /*<<< orphan*/  csrr1; int /*<<< orphan*/  csrr0; int /*<<< orphan*/  features; } ;
struct TYPE_5__ {TYPE_1__ e; } ;
struct kvm_sregs {TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_SREGS_E_BASE ; 
 int /*<<< orphan*/  get_tb () ; 
 int /*<<< orphan*/  kvmppc_get_dar (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_get_dec (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_get_esr (struct kvm_vcpu*) ; 

__attribute__((used)) static void get_sregs_base(struct kvm_vcpu *vcpu,
                           struct kvm_sregs *sregs)
{
	u64 tb = get_tb();

	sregs->u.e.features |= KVM_SREGS_E_BASE;

	sregs->u.e.csrr0 = vcpu->arch.csrr0;
	sregs->u.e.csrr1 = vcpu->arch.csrr1;
	sregs->u.e.mcsr = vcpu->arch.mcsr;
	sregs->u.e.esr = kvmppc_get_esr(vcpu);
	sregs->u.e.dear = kvmppc_get_dar(vcpu);
	sregs->u.e.tsr = vcpu->arch.tsr;
	sregs->u.e.tcr = vcpu->arch.tcr;
	sregs->u.e.dec = kvmppc_get_dec(vcpu, tb);
	sregs->u.e.tb = tb;
	sregs->u.e.vrsave = vcpu->arch.vrsave;
}