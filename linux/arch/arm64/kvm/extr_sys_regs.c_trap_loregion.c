#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct sys_reg_params {scalar_t__ is_write; } ;
struct sys_reg_desc {scalar_t__ Op2; scalar_t__ CRm; scalar_t__ CRn; scalar_t__ Op1; scalar_t__ Op0; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int ID_AA64MMFR1_LOR_SHIFT ; 
 int /*<<< orphan*/  SYS_ID_AA64MMFR1_EL1 ; 
 scalar_t__ SYS_LORID_EL1 ; 
 int /*<<< orphan*/  kvm_inject_undefined (struct kvm_vcpu*) ; 
 int read_sanitised_ftr_reg (int /*<<< orphan*/ ) ; 
 scalar_t__ sys_reg (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int trap_raz_wi (struct kvm_vcpu*,struct sys_reg_params*,struct sys_reg_desc const*) ; 
 int write_to_read_only (struct kvm_vcpu*,struct sys_reg_params*,struct sys_reg_desc const*) ; 

__attribute__((used)) static bool trap_loregion(struct kvm_vcpu *vcpu,
			  struct sys_reg_params *p,
			  const struct sys_reg_desc *r)
{
	u64 val = read_sanitised_ftr_reg(SYS_ID_AA64MMFR1_EL1);
	u32 sr = sys_reg((u32)r->Op0, (u32)r->Op1,
			 (u32)r->CRn, (u32)r->CRm, (u32)r->Op2);

	if (!(val & (0xfUL << ID_AA64MMFR1_LOR_SHIFT))) {
		kvm_inject_undefined(vcpu);
		return false;
	}

	if (p->is_write && sr == SYS_LORID_EL1)
		return write_to_read_only(vcpu, p, r);

	return trap_raz_wi(vcpu, p, r);
}