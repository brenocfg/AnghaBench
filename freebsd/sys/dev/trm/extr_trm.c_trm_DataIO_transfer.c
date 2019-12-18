#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  scalar_t__ u_int16_t ;
struct TYPE_7__ {unsigned int SyncPeriod; } ;
struct TYPE_6__ {unsigned int SRBSGIndex; unsigned int SRBSGCount; unsigned int SRBTotalXferLength; unsigned int SRBSGPhyAddr; int /*<<< orphan*/  SRBState; int /*<<< orphan*/  SRBStatus; int /*<<< orphan*/  AdaptStatus; TYPE_1__* pSRBSGL; TYPE_3__* pSRBDCB; } ;
struct TYPE_5__ {unsigned int address; unsigned int length; } ;
typedef  TYPE_2__* PSRB ;
typedef  TYPE_3__* PDCB ;
typedef  int /*<<< orphan*/  PACB ;

/* Variables and functions */
 scalar_t__ DO_DATALATCH ; 
 int /*<<< orphan*/  H_OVER_UNDER_RUN ; 
 int /*<<< orphan*/  OVER_RUN ; 
 int /*<<< orphan*/  SCMD_DMA_IN ; 
 int /*<<< orphan*/  SCMD_DMA_OUT ; 
 int /*<<< orphan*/  SCMD_FIFO_IN ; 
 int /*<<< orphan*/  SCMD_FIFO_OUT ; 
 int /*<<< orphan*/  SRB_DATA_XFER ; 
 int /*<<< orphan*/  SRB_XFERPAD ; 
 int /*<<< orphan*/  TRMREG_DMA_COMMAND ; 
 int /*<<< orphan*/  TRMREG_DMA_XCNT ; 
 int /*<<< orphan*/  TRMREG_DMA_XHIGHADDR ; 
 int /*<<< orphan*/  TRMREG_DMA_XLOWADDR ; 
 int /*<<< orphan*/  TRMREG_SCSI_COMMAND ; 
 int /*<<< orphan*/  TRMREG_SCSI_CONTROL ; 
 int /*<<< orphan*/  TRMREG_SCSI_COUNTER ; 
 int /*<<< orphan*/  TRMREG_SCSI_FIFO ; 
 int /*<<< orphan*/  TRM_DPRINTF (char*,unsigned int) ; 
 int WIDE_SYNC ; 
 scalar_t__ XFERDATAOUT ; 
 int /*<<< orphan*/  trm_reg_read16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trm_reg_write16 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trm_reg_write32 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trm_reg_write8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
trm_DataIO_transfer(PACB pACB, PSRB pSRB, u_int16_t ioDir)
{
	u_int8_t	bval;
	PDCB		pDCB;

	pDCB = pSRB->pSRBDCB;
	if (pSRB->SRBSGIndex < pSRB->SRBSGCount) {
		if (pSRB->SRBTotalXferLength != 0) {
			/* 
			 * load what physical address of Scatter/Gather list 
			 table want to be transfer
			 */
			TRM_DPRINTF(" SG->address=%8x \n",pSRB->pSRBSGL->address);
			TRM_DPRINTF(" SG->length=%8x \n",pSRB->pSRBSGL->length);
			TRM_DPRINTF(" pDCB->SyncPeriod=%x \n",pDCB->SyncPeriod);
			TRM_DPRINTF(" pSRB->pSRBSGL=%8x \n",(unsigned int)pSRB->pSRBSGL);
			TRM_DPRINTF(" pSRB->SRBSGPhyAddr=%8x \n",pSRB->SRBSGPhyAddr);
			TRM_DPRINTF(" pSRB->SRBSGIndex=%d \n",pSRB->SRBSGIndex);
			TRM_DPRINTF(" pSRB->SRBSGCount=%d \n",pSRB->SRBSGCount);
			TRM_DPRINTF(" pSRB->SRBTotalXferLength=%d \n",pSRB->SRBTotalXferLength);

			pSRB->SRBState = SRB_DATA_XFER;
			trm_reg_write32(0, TRMREG_DMA_XHIGHADDR);
			trm_reg_write32(
			    (pSRB->SRBSGPhyAddr + 
			     ((u_long)pSRB->SRBSGIndex << 3)),
			    TRMREG_DMA_XLOWADDR);
			/*
			 * load how many bytes in the Scatter/Gather 
			 * list table 
			 */
			trm_reg_write32(
			    ((u_long)(pSRB->SRBSGCount - pSRB->SRBSGIndex) << 3),
			    TRMREG_DMA_XCNT);			
			/*
			 * load total transfer length (24bits) max value
			 * 16Mbyte 
			 */
			trm_reg_write32(pSRB->SRBTotalXferLength,
			    TRMREG_SCSI_COUNTER);
			/* Start DMA transfer */
			trm_reg_write16(ioDir, TRMREG_DMA_COMMAND);
			/* Start SCSI transfer */
			trm_reg_write16(DO_DATALATCH, TRMREG_SCSI_CONTROL);
			/* it's important for atn stop */
			/*
			 * SCSI cammand 
			 */
			bval = (ioDir == XFERDATAOUT) ?
			  SCMD_DMA_OUT : SCMD_DMA_IN;
			trm_reg_write8(bval, TRMREG_SCSI_COMMAND);
		} else {
		  /* xfer pad */
			if (pSRB->SRBSGCount) {
				pSRB->AdaptStatus = H_OVER_UNDER_RUN;
				pSRB->SRBStatus |= OVER_RUN;
			}
			if (pDCB->SyncPeriod & WIDE_SYNC)
				trm_reg_write32(2,TRMREG_SCSI_COUNTER);
			else
				trm_reg_write32(1,TRMREG_SCSI_COUNTER);
			if (ioDir == XFERDATAOUT)
				trm_reg_write16(0, TRMREG_SCSI_FIFO);
			else
				trm_reg_read16(TRMREG_SCSI_FIFO);
			pSRB->SRBState |= SRB_XFERPAD;
			trm_reg_write16(DO_DATALATCH, TRMREG_SCSI_CONTROL);
			/* it's important for atn stop */
			/*
			 * SCSI cammand 
			 */
			bval = (ioDir == XFERDATAOUT) ? 
			  SCMD_FIFO_OUT : SCMD_FIFO_IN;
			trm_reg_write8(bval, TRMREG_SCSI_COMMAND);
		}
	}
}