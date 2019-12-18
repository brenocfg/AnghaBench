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
struct coproc_params {int is_64bit; int CRn; int CRm; int Op1; int Op2; } ;

/* Variables and functions */
 int KVM_REG_ARCH_MASK ; 
 int KVM_REG_ARM_32_CRN_MASK ; 
 int KVM_REG_ARM_32_CRN_SHIFT ; 
 int KVM_REG_ARM_32_OPC2_MASK ; 
 int KVM_REG_ARM_32_OPC2_SHIFT ; 
 int KVM_REG_ARM_COPROC_MASK ; 
 int KVM_REG_ARM_CRM_MASK ; 
 int KVM_REG_ARM_CRM_SHIFT ; 
 int KVM_REG_ARM_OPC1_MASK ; 
 int KVM_REG_ARM_OPC1_SHIFT ; 
 int KVM_REG_SIZE_MASK ; 
#define  KVM_REG_SIZE_U32 129 
#define  KVM_REG_SIZE_U64 128 

__attribute__((used)) static bool index_to_params(u64 id, struct coproc_params *params)
{
	switch (id & KVM_REG_SIZE_MASK) {
	case KVM_REG_SIZE_U32:
		/* Any unused index bits means it's not valid. */
		if (id & ~(KVM_REG_ARCH_MASK | KVM_REG_SIZE_MASK
			   | KVM_REG_ARM_COPROC_MASK
			   | KVM_REG_ARM_32_CRN_MASK
			   | KVM_REG_ARM_CRM_MASK
			   | KVM_REG_ARM_OPC1_MASK
			   | KVM_REG_ARM_32_OPC2_MASK))
			return false;

		params->is_64bit = false;
		params->CRn = ((id & KVM_REG_ARM_32_CRN_MASK)
			       >> KVM_REG_ARM_32_CRN_SHIFT);
		params->CRm = ((id & KVM_REG_ARM_CRM_MASK)
			       >> KVM_REG_ARM_CRM_SHIFT);
		params->Op1 = ((id & KVM_REG_ARM_OPC1_MASK)
			       >> KVM_REG_ARM_OPC1_SHIFT);
		params->Op2 = ((id & KVM_REG_ARM_32_OPC2_MASK)
			       >> KVM_REG_ARM_32_OPC2_SHIFT);
		return true;
	case KVM_REG_SIZE_U64:
		/* Any unused index bits means it's not valid. */
		if (id & ~(KVM_REG_ARCH_MASK | KVM_REG_SIZE_MASK
			      | KVM_REG_ARM_COPROC_MASK
			      | KVM_REG_ARM_CRM_MASK
			      | KVM_REG_ARM_OPC1_MASK))
			return false;
		params->is_64bit = true;
		/* CRm to CRn: see cp15_to_index for details */
		params->CRn = ((id & KVM_REG_ARM_CRM_MASK)
			       >> KVM_REG_ARM_CRM_SHIFT);
		params->Op1 = ((id & KVM_REG_ARM_OPC1_MASK)
			       >> KVM_REG_ARM_OPC1_SHIFT);
		params->Op2 = 0;
		params->CRm = 0;
		return true;
	default:
		return false;
	}
}