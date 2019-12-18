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
typedef  int u_int8_t ;
typedef  int u_int32_t ;
struct HBB_MessageUnit {int /*<<< orphan*/  drv2iop_doorbell; int /*<<< orphan*/  iop2drv_doorbell; } ;
struct AdapterControlBlock {scalar_t__ pmu; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCMSR_DRV2IOP_END_OF_INTERRUPT ; 
 int ARCMSR_IOP2DRV_MESSAGE_CMD_DONE ; 
 int /*<<< orphan*/  ARCMSR_MESSAGE_INT_CLEAR_PATTERN ; 
 int FALSE ; 
 int READ_CHIP_REG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int /*<<< orphan*/  UDELAY (int) ; 
 int /*<<< orphan*/  WRITE_CHIP_REG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int8_t arcmsr_hbb_wait_msgint_ready(struct AdapterControlBlock *acb)
{
	u_int32_t Index;
	u_int8_t Retries = 0x00;
	struct HBB_MessageUnit *phbbmu = (struct HBB_MessageUnit *)acb->pmu;

	do {
		for(Index=0; Index < 100; Index++) {
			if(READ_CHIP_REG32(0, phbbmu->iop2drv_doorbell) & ARCMSR_IOP2DRV_MESSAGE_CMD_DONE) {
				WRITE_CHIP_REG32(0, phbbmu->iop2drv_doorbell, ARCMSR_MESSAGE_INT_CLEAR_PATTERN);/*clear interrupt*/
				WRITE_CHIP_REG32(0, phbbmu->drv2iop_doorbell, ARCMSR_DRV2IOP_END_OF_INTERRUPT);
				return TRUE;
			}
			UDELAY(10000);
		}/*max 1 seconds*/
	}while(Retries++ < 20);/*max 20 sec*/
	return (FALSE);
}