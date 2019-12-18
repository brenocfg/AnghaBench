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
typedef  int uint16_t ;
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct HBD_MessageUnit0 {int doneq_index; TYPE_1__* done_qbuffer; } ;
struct AdapterControlBlock {int /*<<< orphan*/  srb_dmamap; int /*<<< orphan*/  srb_dmat; scalar_t__ pmu; } ;
struct TYPE_2__ {int addressLow; } ;

/* Variables and functions */
 int ARCMSR_HBDMU_OUTBOUND_LIST_INTERRUPT ; 
 int ARCMSR_HBDMU_OUTBOUND_LIST_INTERRUPT_CLEAR ; 
 int ARCMSR_SRBREPLY_FLAG_ERROR_MODE1 ; 
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int CHIP_REG_READ32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHIP_REG_WRITE32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HBD_MessageUnit ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  arcmsr_drain_donequeue (struct AdapterControlBlock*,int,int /*<<< orphan*/ ) ; 
 int arcmsr_get_doneq_index (struct HBD_MessageUnit0*) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  outboundlist_interrupt_cause ; 
 int /*<<< orphan*/  outboundlist_read_pointer ; 

__attribute__((used)) static void arcmsr_hbd_postqueue_isr(struct AdapterControlBlock *acb)
{
	struct HBD_MessageUnit0 *phbdmu = (struct HBD_MessageUnit0 *)acb->pmu;
	u_int32_t outbound_write_pointer;
	u_int32_t addressLow;
	uint16_t doneq_index;
	u_int16_t error;
	/*
	*****************************************************************************
	**               areca cdb command done
	*****************************************************************************
	*/
	if((CHIP_REG_READ32(HBD_MessageUnit, 0, outboundlist_interrupt_cause) &
		ARCMSR_HBDMU_OUTBOUND_LIST_INTERRUPT) == 0)
		return;
	bus_dmamap_sync(acb->srb_dmat, acb->srb_dmamap, 
		BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);
	outbound_write_pointer = phbdmu->done_qbuffer[0].addressLow;
	doneq_index = phbdmu->doneq_index;
	while ((doneq_index & 0xFF) != (outbound_write_pointer & 0xFF)) {
		doneq_index = arcmsr_get_doneq_index(phbdmu);
		addressLow = phbdmu->done_qbuffer[(doneq_index & 0xFF)+1].addressLow;
		error = (addressLow & ARCMSR_SRBREPLY_FLAG_ERROR_MODE1) ? TRUE : FALSE;
		arcmsr_drain_donequeue(acb, addressLow, error); /*Check if command done with no error */
		CHIP_REG_WRITE32(HBD_MessageUnit, 0, outboundlist_read_pointer, doneq_index);
		outbound_write_pointer = phbdmu->done_qbuffer[0].addressLow;
	}
	CHIP_REG_WRITE32(HBD_MessageUnit, 0, outboundlist_interrupt_cause, ARCMSR_HBDMU_OUTBOUND_LIST_INTERRUPT_CLEAR);
	CHIP_REG_READ32(HBD_MessageUnit, 0, outboundlist_interrupt_cause); /*Dummy ioread32 to force pci flush */
}