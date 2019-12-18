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
struct AdapterControlBlock {int adapter_type; int outbound_int_enable; scalar_t__ pmu; } ;

/* Variables and functions */
#define  ACB_ADAPTER_TYPE_A 132 
#define  ACB_ADAPTER_TYPE_B 131 
#define  ACB_ADAPTER_TYPE_C 130 
#define  ACB_ADAPTER_TYPE_D 129 
#define  ACB_ADAPTER_TYPE_E 128 
 int ARCMSR_HBCMU_OUTBOUND_DOORBELL_ISR_MASK ; 
 int ARCMSR_HBCMU_OUTBOUND_POSTQUEUE_ISR_MASK ; 
 int ARCMSR_HBCMU_UTILITY_A_ISR_MASK ; 
 int ARCMSR_HBDMU_ALL_INT_ENABLE ; 
 int ARCMSR_HBEMU_OUTBOUND_DOORBELL_ISR ; 
 int ARCMSR_HBEMU_OUTBOUND_POSTQUEUE_ISR ; 
 int ARCMSR_IOP2DRV_CDB_DONE ; 
 int ARCMSR_IOP2DRV_DATA_READ_OK ; 
 int ARCMSR_IOP2DRV_DATA_WRITE_OK ; 
 int ARCMSR_IOP2DRV_MESSAGE_CMD_DONE ; 
 int ARCMSR_MU_OUTBOUND_DOORBELL_INTMASKENABLE ; 
 int ARCMSR_MU_OUTBOUND_MESSAGE0_INTMASKENABLE ; 
 int ARCMSR_MU_OUTBOUND_POSTQUEUE_INTMASKENABLE ; 
 int /*<<< orphan*/  CHIP_REG_READ32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHIP_REG_WRITE32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HBA_MessageUnit ; 
 int /*<<< orphan*/  HBC_MessageUnit ; 
 int /*<<< orphan*/  HBD_MessageUnit ; 
 int /*<<< orphan*/  HBE_MessageUnit ; 
 int /*<<< orphan*/  WRITE_CHIP_REG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  host_int_mask ; 
 int /*<<< orphan*/  outbound_intmask ; 
 int /*<<< orphan*/  pcief0_int_enable ; 

__attribute__((used)) static void arcmsr_enable_allintr( struct AdapterControlBlock *acb, u_int32_t intmask_org)
{
	u_int32_t mask;

	switch (acb->adapter_type) {
	case ACB_ADAPTER_TYPE_A: {
			/* enable outbound Post Queue, outbound doorbell Interrupt */
			mask = ~(ARCMSR_MU_OUTBOUND_POSTQUEUE_INTMASKENABLE|ARCMSR_MU_OUTBOUND_DOORBELL_INTMASKENABLE|ARCMSR_MU_OUTBOUND_MESSAGE0_INTMASKENABLE);
			CHIP_REG_WRITE32(HBA_MessageUnit, 0, outbound_intmask, intmask_org & mask);
			acb->outbound_int_enable = ~(intmask_org & mask) & 0x000000ff;
		}
		break;
	case ACB_ADAPTER_TYPE_B: {
			struct HBB_MessageUnit *phbbmu = (struct HBB_MessageUnit *)acb->pmu;
			/* enable ARCMSR_IOP2DRV_MESSAGE_CMD_DONE */
			mask = (ARCMSR_IOP2DRV_DATA_WRITE_OK|ARCMSR_IOP2DRV_DATA_READ_OK|ARCMSR_IOP2DRV_CDB_DONE|ARCMSR_IOP2DRV_MESSAGE_CMD_DONE);
			WRITE_CHIP_REG32(0, phbbmu->iop2drv_doorbell_mask, intmask_org | mask); /*1=interrupt enable, 0=interrupt disable*/
			acb->outbound_int_enable = (intmask_org | mask) & 0x0000000f;
		}
		break;
	case ACB_ADAPTER_TYPE_C: {
			/* enable outbound Post Queue, outbound doorbell Interrupt */
			mask = ~(ARCMSR_HBCMU_UTILITY_A_ISR_MASK | ARCMSR_HBCMU_OUTBOUND_DOORBELL_ISR_MASK | ARCMSR_HBCMU_OUTBOUND_POSTQUEUE_ISR_MASK);
			CHIP_REG_WRITE32(HBC_MessageUnit, 0, host_int_mask, intmask_org & mask);
			acb->outbound_int_enable = ~(intmask_org & mask) & 0x0000000f;
		}
		break;
	case ACB_ADAPTER_TYPE_D: {
			/* enable outbound Post Queue, outbound doorbell Interrupt */
			mask = ARCMSR_HBDMU_ALL_INT_ENABLE;
			CHIP_REG_WRITE32(HBD_MessageUnit, 0, pcief0_int_enable, intmask_org | mask);
			CHIP_REG_READ32(HBD_MessageUnit, 0, pcief0_int_enable);
			acb->outbound_int_enable = mask;
		}
		break;
	case ACB_ADAPTER_TYPE_E: {
			/* enable outbound Post Queue, outbound doorbell Interrupt */
			mask = ~(ARCMSR_HBEMU_OUTBOUND_DOORBELL_ISR | ARCMSR_HBEMU_OUTBOUND_POSTQUEUE_ISR);
			CHIP_REG_WRITE32(HBE_MessageUnit, 0, host_int_mask, intmask_org & mask);
			acb->outbound_int_enable = ~(intmask_org & mask) & 0x0000000f;
		}
		break;
	}
}