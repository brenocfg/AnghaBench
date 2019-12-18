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
struct sys_reg_desc {int Op0; int Op1; int CRn; int CRm; int Op2; } ;

/* Variables and functions */
 int KVM_REG_ARM64 ; 
 int KVM_REG_ARM64_SYSREG ; 
 int KVM_REG_ARM64_SYSREG_CRM_SHIFT ; 
 int KVM_REG_ARM64_SYSREG_CRN_SHIFT ; 
 int KVM_REG_ARM64_SYSREG_OP0_SHIFT ; 
 int KVM_REG_ARM64_SYSREG_OP1_SHIFT ; 
 int KVM_REG_ARM64_SYSREG_OP2_SHIFT ; 
 int KVM_REG_SIZE_U64 ; 

__attribute__((used)) static u64 sys_reg_to_index(const struct sys_reg_desc *reg)
{
	return (KVM_REG_ARM64 | KVM_REG_SIZE_U64 |
		KVM_REG_ARM64_SYSREG |
		(reg->Op0 << KVM_REG_ARM64_SYSREG_OP0_SHIFT) |
		(reg->Op1 << KVM_REG_ARM64_SYSREG_OP1_SHIFT) |
		(reg->CRn << KVM_REG_ARM64_SYSREG_CRN_SHIFT) |
		(reg->CRm << KVM_REG_ARM64_SYSREG_CRM_SHIFT) |
		(reg->Op2 << KVM_REG_ARM64_SYSREG_OP2_SHIFT));
}