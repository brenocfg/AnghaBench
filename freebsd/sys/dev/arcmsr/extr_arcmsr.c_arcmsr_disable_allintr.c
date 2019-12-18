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
typedef  int u_int32_t ;
struct HBB_MessageUnit {int /*<<< orphan*/  iop2drv_doorbell_mask; } ;
struct AdapterControlBlock {int adapter_type; scalar_t__ pmu; } ;

/* Variables and functions */
#define  ACB_ADAPTER_TYPE_A 132 
#define  ACB_ADAPTER_TYPE_B 131 
#define  ACB_ADAPTER_TYPE_C 130 
#define  ACB_ADAPTER_TYPE_D 129 
#define  ACB_ADAPTER_TYPE_E 128 
 int ARCMSR_HBCMU_ALL_INTMASKENABLE ; 
 int ARCMSR_HBDMU_ALL_INT_DISABLE ; 
 int ARCMSR_HBEMU_ALL_INTMASKENABLE ; 
 int ARCMSR_IOP2DRV_MESSAGE_CMD_DONE ; 
 int ARCMSR_MU_OUTBOUND_ALL_INTMASKENABLE ; 
 int CHIP_REG_READ32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHIP_REG_WRITE32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HBA_MessageUnit ; 
 int /*<<< orphan*/  HBC_MessageUnit ; 
 int /*<<< orphan*/  HBD_MessageUnit ; 
 int /*<<< orphan*/  HBE_MessageUnit ; 
 int READ_CHIP_REG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_CHIP_REG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host_int_mask ; 
 int /*<<< orphan*/  outbound_intmask ; 
 int /*<<< orphan*/  pcief0_int_enable ; 

__attribute__((used)) static u_int32_t arcmsr_disable_allintr( struct AdapterControlBlock *acb)
{
	u_int32_t intmask_org = 0;

	switch (acb->adapter_type) {
	case ACB_ADAPTER_TYPE_A: {
			/* disable all outbound interrupt */
			intmask_org = CHIP_REG_READ32(HBA_MessageUnit, 0, outbound_intmask); /* disable outbound message0 int */
			CHIP_REG_WRITE32(HBA_MessageUnit, 0, outbound_intmask, intmask_org|ARCMSR_MU_OUTBOUND_ALL_INTMASKENABLE);
		}
		break;
	case ACB_ADAPTER_TYPE_B: {
			struct HBB_MessageUnit *phbbmu = (struct HBB_MessageUnit *)acb->pmu;
			/* disable all outbound interrupt */
			intmask_org = READ_CHIP_REG32(0, phbbmu->iop2drv_doorbell_mask)
						& (~ARCMSR_IOP2DRV_MESSAGE_CMD_DONE); /* disable outbound message0 int */
			WRITE_CHIP_REG32(0, phbbmu->iop2drv_doorbell_mask, 0); /* disable all interrupt */
		}
		break;
	case ACB_ADAPTER_TYPE_C: {
			/* disable all outbound interrupt */
			intmask_org = CHIP_REG_READ32(HBC_MessageUnit, 0, host_int_mask)	; /* disable outbound message0 int */
			CHIP_REG_WRITE32(HBC_MessageUnit, 0, host_int_mask, intmask_org|ARCMSR_HBCMU_ALL_INTMASKENABLE);
		}
		break;
	case ACB_ADAPTER_TYPE_D: {
			/* disable all outbound interrupt */
			intmask_org = CHIP_REG_READ32(HBD_MessageUnit, 0, pcief0_int_enable)	; /* disable outbound message0 int */
			CHIP_REG_WRITE32(HBD_MessageUnit, 0, pcief0_int_enable, ARCMSR_HBDMU_ALL_INT_DISABLE);
		}
		break;
	case ACB_ADAPTER_TYPE_E: {
			/* disable all outbound interrupt */
			intmask_org = CHIP_REG_READ32(HBC_MessageUnit, 0, host_int_mask)	; /* disable outbound message0 int */
			CHIP_REG_WRITE32(HBE_MessageUnit, 0, host_int_mask, intmask_org | ARCMSR_HBEMU_ALL_INTMASKENABLE);
		}
		break;
	}
	return (intmask_org);
}