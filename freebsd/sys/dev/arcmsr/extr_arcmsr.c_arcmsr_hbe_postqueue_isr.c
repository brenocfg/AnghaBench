#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct AdapterControlBlock {int doneq_index; int completionQ_entry; TYPE_1__* pCompletionQ; int /*<<< orphan*/  srb_dmamap; int /*<<< orphan*/  srb_dmat; } ;
struct TYPE_2__ {int cmdFlag; scalar_t__ cmdSMID; } ;

/* Variables and functions */
 int ARCMSR_SRBREPLY_FLAG_ERROR_MODE1 ; 
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int CHIP_REG_READ32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHIP_REG_WRITE32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HBE_MessageUnit ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  arcmsr_drain_donequeue (struct AdapterControlBlock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reply_post_consumer_index ; 
 int /*<<< orphan*/  reply_post_producer_index ; 

__attribute__((used)) static void arcmsr_hbe_postqueue_isr(struct AdapterControlBlock *acb)
{
	u_int16_t error;
	uint32_t doneq_index;
	uint16_t cmdSMID;
	
	/*
	*****************************************************************************
	**               areca cdb command done
	*****************************************************************************
	*/
	bus_dmamap_sync(acb->srb_dmat, acb->srb_dmamap, BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);
	doneq_index = acb->doneq_index;
	while ((CHIP_REG_READ32(HBE_MessageUnit, 0, reply_post_producer_index) & 0xFFFF) != doneq_index) {
		cmdSMID = acb->pCompletionQ[doneq_index].cmdSMID;
		error = (acb->pCompletionQ[doneq_index].cmdFlag & ARCMSR_SRBREPLY_FLAG_ERROR_MODE1) ? TRUE : FALSE;
		arcmsr_drain_donequeue(acb, (u_int32_t)cmdSMID, error);
		doneq_index++;
		if (doneq_index >= acb->completionQ_entry)
			doneq_index = 0;
	}
	acb->doneq_index = doneq_index;
	CHIP_REG_WRITE32(HBE_MessageUnit, 0, reply_post_consumer_index, doneq_index);
}