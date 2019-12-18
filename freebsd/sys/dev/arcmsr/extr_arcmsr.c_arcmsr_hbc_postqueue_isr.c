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
typedef  int /*<<< orphan*/  u_int16_t ;
struct AdapterControlBlock {int /*<<< orphan*/  srb_dmamap; int /*<<< orphan*/  srb_dmat; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCMSR_HBCMU_DRV2IOP_POSTQUEUE_THROTTLING ; 
 int ARCMSR_HBCMU_OUTBOUND_POSTQUEUE_ISR ; 
 int ARCMSR_HBC_ISR_THROTTLING_LEVEL ; 
 int ARCMSR_SRBREPLY_FLAG_ERROR_MODE1 ; 
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int CHIP_REG_READ32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHIP_REG_WRITE32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HBC_MessageUnit ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  arcmsr_drain_donequeue (struct AdapterControlBlock*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  host_int_status ; 
 int /*<<< orphan*/  inbound_doorbell ; 
 int /*<<< orphan*/  outbound_queueport_low ; 

__attribute__((used)) static void arcmsr_hbc_postqueue_isr(struct AdapterControlBlock *acb)
{
	u_int32_t flag_srb,throttling = 0;
	u_int16_t error;

	/*
	*****************************************************************************
	**               areca cdb command done
	*****************************************************************************
	*/
	bus_dmamap_sync(acb->srb_dmat, acb->srb_dmamap, BUS_DMASYNC_POSTREAD|BUS_DMASYNC_POSTWRITE);
	do {
		flag_srb = CHIP_REG_READ32(HBC_MessageUnit, 0, outbound_queueport_low);
		if (flag_srb == 0xFFFFFFFF)
			break;
		/* check if command done with no error*/
		error = (flag_srb & ARCMSR_SRBREPLY_FLAG_ERROR_MODE1)?TRUE:FALSE;
		arcmsr_drain_donequeue(acb, flag_srb, error);
		throttling++;
		if(throttling == ARCMSR_HBC_ISR_THROTTLING_LEVEL) {
			CHIP_REG_WRITE32(HBC_MessageUnit, 0, inbound_doorbell,ARCMSR_HBCMU_DRV2IOP_POSTQUEUE_THROTTLING);
			throttling = 0;
		}
	} while(CHIP_REG_READ32(HBC_MessageUnit, 0, host_int_status) & ARCMSR_HBCMU_OUTBOUND_POSTQUEUE_ISR);
}