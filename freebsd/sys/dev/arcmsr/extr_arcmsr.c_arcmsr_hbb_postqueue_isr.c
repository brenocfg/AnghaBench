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
struct HBB_MessageUnit {int doneq_index; int* done_qbuffer; } ;
struct AdapterControlBlock {int /*<<< orphan*/  srb_dmamap; int /*<<< orphan*/  srb_dmat; scalar_t__ pmu; } ;

/* Variables and functions */
 int ARCMSR_MAX_HBB_POSTQUEUE ; 
 int ARCMSR_SRBREPLY_FLAG_ERROR_MODE0 ; 
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  arcmsr_drain_donequeue (struct AdapterControlBlock*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void arcmsr_hbb_postqueue_isr(struct AdapterControlBlock *acb)
{
	struct HBB_MessageUnit *phbbmu = (struct HBB_MessageUnit *)acb->pmu;
	u_int32_t flag_srb;
	int index;
	u_int16_t error;

	/*
	*****************************************************************************
	**               areca cdb command done
	*****************************************************************************
	*/
	bus_dmamap_sync(acb->srb_dmat, acb->srb_dmamap, 
		BUS_DMASYNC_POSTREAD|BUS_DMASYNC_POSTWRITE);
	index = phbbmu->doneq_index;
	while((flag_srb = phbbmu->done_qbuffer[index]) != 0) {
		phbbmu->done_qbuffer[index] = 0;
		index++;
		index %= ARCMSR_MAX_HBB_POSTQUEUE;     /*if last index number set it to 0 */
		phbbmu->doneq_index = index;
		/* check if command done with no error*/
	error = (flag_srb & ARCMSR_SRBREPLY_FLAG_ERROR_MODE0)?TRUE:FALSE;
		arcmsr_drain_donequeue(acb, flag_srb, error);
	}	/*drain reply FIFO*/
}