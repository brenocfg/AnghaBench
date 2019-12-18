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
struct sys_reg_desc {scalar_t__ Op2; scalar_t__ CRm; scalar_t__ CRn; scalar_t__ Op1; scalar_t__ Op0; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int ID_AA64ISAR1_APA_SHIFT ; 
 int ID_AA64ISAR1_API_SHIFT ; 
 int ID_AA64ISAR1_GPA_SHIFT ; 
 int ID_AA64ISAR1_GPI_SHIFT ; 
 int ID_AA64PFR0_SVE_SHIFT ; 
 scalar_t__ SYS_ID_AA64ISAR1_EL1 ; 
 scalar_t__ SYS_ID_AA64PFR0_EL1 ; 
 int read_sanitised_ftr_reg (scalar_t__) ; 
 scalar_t__ sys_reg (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vcpu_has_ptrauth (struct kvm_vcpu const*) ; 
 int /*<<< orphan*/  vcpu_has_sve (struct kvm_vcpu const*) ; 

__attribute__((used)) static u64 read_id_reg(const struct kvm_vcpu *vcpu,
		struct sys_reg_desc const *r, bool raz)
{
	u32 id = sys_reg((u32)r->Op0, (u32)r->Op1,
			 (u32)r->CRn, (u32)r->CRm, (u32)r->Op2);
	u64 val = raz ? 0 : read_sanitised_ftr_reg(id);

	if (id == SYS_ID_AA64PFR0_EL1 && !vcpu_has_sve(vcpu)) {
		val &= ~(0xfUL << ID_AA64PFR0_SVE_SHIFT);
	} else if (id == SYS_ID_AA64ISAR1_EL1 && !vcpu_has_ptrauth(vcpu)) {
		val &= ~((0xfUL << ID_AA64ISAR1_APA_SHIFT) |
			 (0xfUL << ID_AA64ISAR1_API_SHIFT) |
			 (0xfUL << ID_AA64ISAR1_GPA_SHIFT) |
			 (0xfUL << ID_AA64ISAR1_GPI_SHIFT));
	}

	return val;
}