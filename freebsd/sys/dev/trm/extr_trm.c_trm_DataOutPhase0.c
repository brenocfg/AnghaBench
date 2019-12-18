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
typedef  scalar_t__ u_int8_t ;
typedef  int u_int16_t ;
struct TYPE_7__ {int SyncPeriod; } ;
struct TYPE_6__ {int length; int /*<<< orphan*/  address; } ;
struct TYPE_5__ {int SRBState; int SRBTotalXferLength; scalar_t__ SRBSGIndex; scalar_t__ SRBSGCount; TYPE_2__* pSRBSGL; int /*<<< orphan*/  SRBStatus; TYPE_3__* pSRBDCB; } ;
typedef  TYPE_1__* PSRB ;
typedef  TYPE_2__* PSEG ;
typedef  TYPE_3__* PDCB ;
typedef  int /*<<< orphan*/  PACB ;

/* Variables and functions */
 scalar_t__ DMAXFERCOMP ; 
 int /*<<< orphan*/  DO_CLRFIFO ; 
 int PARITYERROR ; 
 int /*<<< orphan*/  PARITY_ERROR ; 
 int SCSIXFERCNT_2_ZERO ; 
 int SCSIXFERDONE ; 
 int SRB_XFERPAD ; 
 int /*<<< orphan*/  STOPDMAXFER ; 
 int /*<<< orphan*/  TRMREG_DMA_CONTROL ; 
 int /*<<< orphan*/  TRMREG_DMA_STATUS ; 
 int /*<<< orphan*/  TRMREG_SCSI_CONTROL ; 
 int /*<<< orphan*/  TRMREG_SCSI_COUNTER ; 
 int /*<<< orphan*/  TRMREG_SCSI_FIFOCNT ; 
 int WIDE_SYNC ; 
 scalar_t__ trm_reg_read32 (int /*<<< orphan*/ ) ; 
 int trm_reg_read8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trm_reg_write16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trm_reg_write8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
trm_DataOutPhase0(PACB pACB, PSRB pSRB, u_int16_t *pscsi_status)
{
	PDCB		pDCB;
	u_int8_t	TempDMAstatus,SGIndexTemp;
	u_int16_t	scsi_status;
	PSEG		pseg;
	u_long		TempSRBXferredLength,dLeftCounter=0;

	pDCB = pSRB->pSRBDCB;
	scsi_status = *pscsi_status;

	if (!(pSRB->SRBState & SRB_XFERPAD)) {
		if (scsi_status & PARITYERROR)
			pSRB->SRBStatus |= PARITY_ERROR;
		if (!(scsi_status & SCSIXFERDONE)) {
      		  /*
		   * when data transfer from DMA FIFO to SCSI FIFO
		   * if there was some data left in SCSI FIFO
		   */
  			dLeftCounter = (u_long) 
			  (trm_reg_read8(TRMREG_SCSI_FIFOCNT) & 0x3F);
			if (pDCB->SyncPeriod & WIDE_SYNC) {
			  /*
		   	   * if WIDE scsi SCSI FIFOCNT unit is word
	   		   * so need to * 2
   			   */
				dLeftCounter <<= 1;
			}
		}
		/*
		 * caculate all the residue data that not yet tranfered
		 * SCSI transfer counter + left in SCSI FIFO data
		 *
		 * .....TRM_SCSI_COUNTER (24bits)
		 * The counter always decrement by one for every SCSI byte 
		 *transfer.
		 * .....TRM_SCSI_FIFOCNT (5bits)
		 * The counter is SCSI FIFO offset counter
		 */
		dLeftCounter += trm_reg_read32(TRMREG_SCSI_COUNTER);
		if (dLeftCounter == 1) {
			dLeftCounter = 0;
			trm_reg_write16(DO_CLRFIFO,TRMREG_SCSI_CONTROL);
		}
		if ((dLeftCounter == 0) || 
		    (scsi_status & SCSIXFERCNT_2_ZERO)) {   
			TempDMAstatus = trm_reg_read8(TRMREG_DMA_STATUS);
			while (!(TempDMAstatus & DMAXFERCOMP)) {
				TempDMAstatus = 
				  trm_reg_read8(TRMREG_DMA_STATUS);
			}
			pSRB->SRBTotalXferLength = 0;
		} else {
		  /* Update SG list		*/
		  /*
	   	   * if transfer not yet complete
   		   * there were some data residue in SCSI FIFO or
		   * SCSI transfer counter not empty
		   */
			if (pSRB->SRBTotalXferLength != dLeftCounter) {
			  /*
		  	   * data that had transferred length
	   		   */
				TempSRBXferredLength = 
				  pSRB->SRBTotalXferLength - dLeftCounter;
				/*
				 * next time to be transferred length
				 */
				pSRB->SRBTotalXferLength = dLeftCounter;
				/*
				 * parsing from last time disconnect SRBSGIndex
				 */
				pseg = 
				  pSRB->pSRBSGL + pSRB->SRBSGIndex;
				for (SGIndexTemp = pSRB->SRBSGIndex;
				    SGIndexTemp < pSRB->SRBSGCount; 
				    SGIndexTemp++) {
					/* 
					 * find last time which SG transfer be 
					 * disconnect 
					 */
					if (TempSRBXferredLength >= 
					    pseg->length) 
						TempSRBXferredLength -= 
						  pseg->length;
					else {
				  	  /*
			   		   * update last time disconnected SG 
					   * list
				   	   */
						pseg->length -= 
						  TempSRBXferredLength; 
						/* residue data length  */
						pseg->address += 
						  TempSRBXferredLength;
						/* residue data pointer */
						pSRB->SRBSGIndex = SGIndexTemp;
						break;
					}
					pseg++;
				}
			}
		}
	}
	trm_reg_write8(STOPDMAXFER ,TRMREG_DMA_CONTROL);
}