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
typedef  int /*<<< orphan*/  u32 ;
struct x86_exception {int dummy; } ;
struct TYPE_4__ {TYPE_1__* mmu; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
typedef  int /*<<< orphan*/  gpa_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* gva_to_gpa ) (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct x86_exception*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  PFERR_USER_MASK ; 
 int /*<<< orphan*/  mmu_is_nested (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct x86_exception*) ; 

gpa_t translate_nested_gpa(struct kvm_vcpu *vcpu, gpa_t gpa, u32 access,
			   struct x86_exception *exception)
{
	gpa_t t_gpa;

	BUG_ON(!mmu_is_nested(vcpu));

	/* NPT walks are always user-walks */
	access |= PFERR_USER_MASK;
	t_gpa  = vcpu->arch.mmu->gva_to_gpa(vcpu, gpa, access, exception);

	return t_gpa;
}