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
struct HBB_MessageUnit {int /*<<< orphan*/  drv2iop_doorbell; } ;
struct AdapterControlBlock {int adapter_type; int /*<<< orphan*/  out_doorbell; scalar_t__ pmu; } ;

/* Variables and functions */
#define  ACB_ADAPTER_TYPE_A 132 
#define  ACB_ADAPTER_TYPE_B 131 
#define  ACB_ADAPTER_TYPE_C 130 
#define  ACB_ADAPTER_TYPE_D 129 
#define  ACB_ADAPTER_TYPE_E 128 
 int /*<<< orphan*/  ARCMSR_DRV2IOP_DATA_WRITE_OK ; 
 int /*<<< orphan*/  ARCMSR_HBCMU_DRV2IOP_DATA_WRITE_OK ; 
 int /*<<< orphan*/  ARCMSR_HBDMU_DRV2IOP_DATA_IN_READY ; 
 int /*<<< orphan*/  ARCMSR_HBEMU_DRV2IOP_DATA_WRITE_OK ; 
 int /*<<< orphan*/  ARCMSR_INBOUND_DRIVER_DATA_WRITE_OK ; 
 int /*<<< orphan*/  CHIP_REG_WRITE32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HBA_MessageUnit ; 
 int /*<<< orphan*/  HBC_MessageUnit ; 
 int /*<<< orphan*/  HBD_MessageUnit ; 
 int /*<<< orphan*/  HBE_MessageUnit ; 
 int /*<<< orphan*/  WRITE_CHIP_REG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inbound_doorbell ; 
 int /*<<< orphan*/  iobound_doorbell ; 

__attribute__((used)) static void arcmsr_iop_message_wrote(struct AdapterControlBlock *acb)
{
	switch (acb->adapter_type) {
	case ACB_ADAPTER_TYPE_A: {
			/*
			** push inbound doorbell tell iop, driver data write ok 
			** and wait reply on next hwinterrupt for next Qbuffer post
			*/
			CHIP_REG_WRITE32(HBA_MessageUnit, 0, inbound_doorbell, ARCMSR_INBOUND_DRIVER_DATA_WRITE_OK);
		}
		break;
	case ACB_ADAPTER_TYPE_B: {
			struct HBB_MessageUnit *phbbmu = (struct HBB_MessageUnit *)acb->pmu;
			/*
			** push inbound doorbell tell iop, driver data write ok 
			** and wait reply on next hwinterrupt for next Qbuffer post
			*/
			WRITE_CHIP_REG32(0, phbbmu->drv2iop_doorbell, ARCMSR_DRV2IOP_DATA_WRITE_OK);
		}
		break;
	case ACB_ADAPTER_TYPE_C: {
			/*
			** push inbound doorbell tell iop, driver data write ok 
			** and wait reply on next hwinterrupt for next Qbuffer post
			*/
			CHIP_REG_WRITE32(HBC_MessageUnit, 0, inbound_doorbell, ARCMSR_HBCMU_DRV2IOP_DATA_WRITE_OK);
		}
		break;
	case ACB_ADAPTER_TYPE_D: {
			/*
			** push inbound doorbell tell iop, driver data write ok 
			** and wait reply on next hwinterrupt for next Qbuffer post
			*/
			CHIP_REG_WRITE32(HBD_MessageUnit, 0, inbound_doorbell, ARCMSR_HBDMU_DRV2IOP_DATA_IN_READY);
		}
		break;
	case ACB_ADAPTER_TYPE_E: {
			/*
			** push inbound doorbell tell iop, driver data write ok 
			** and wait reply on next hwinterrupt for next Qbuffer post
			*/
			acb->out_doorbell ^= ARCMSR_HBEMU_DRV2IOP_DATA_WRITE_OK;
			CHIP_REG_WRITE32(HBE_MessageUnit, 0, iobound_doorbell, acb->out_doorbell);
		}
		break;
	}
}