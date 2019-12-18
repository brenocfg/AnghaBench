#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_long ;
typedef  scalar_t__ u_int8_t ;
typedef  int u_int16_t ;
struct TYPE_5__ {scalar_t__ length; int /*<<< orphan*/  address; } ;
struct TYPE_4__ {int SRBState; scalar_t__ SRBTotalXferLength; scalar_t__ SRBSGIndex; scalar_t__ SRBSGCount; TYPE_2__* pSRBSGL; int /*<<< orphan*/  SRBStatus; } ;
typedef  TYPE_1__* PSRB ;
typedef  TYPE_2__* PSEG ;
typedef  int /*<<< orphan*/  PACB ;

/* Variables and functions */
 scalar_t__ DMAXFERCOMP ; 
 int PARITYERROR ; 
 int /*<<< orphan*/  PARITY_ERROR ; 
 int SCSIXFERCNT_2_ZERO ; 
 int SRB_XFERPAD ; 
 int /*<<< orphan*/  TRMREG_DMA_STATUS ; 
 int /*<<< orphan*/  TRMREG_SCSI_COUNTER ; 
 scalar_t__ trm_reg_read32 (int /*<<< orphan*/ ) ; 
 scalar_t__ trm_reg_read8 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void 
trm_DataInPhase0(PACB pACB, PSRB pSRB, u_int16_t *pscsi_status)
{
	u_int8_t	TempDMAstatus, SGIndexTemp;
	u_int16_t	scsi_status;
	PSEG		pseg;
	u_long		TempSRBXferredLength,dLeftCounter = 0;

    	scsi_status = *pscsi_status;
	if (!(pSRB->SRBState & SRB_XFERPAD)) {
		if (scsi_status & PARITYERROR)
			pSRB->SRBStatus |= PARITY_ERROR;
		dLeftCounter += trm_reg_read32(TRMREG_SCSI_COUNTER);
		if ((dLeftCounter == 0) || (scsi_status & SCSIXFERCNT_2_ZERO)) {
			TempDMAstatus = trm_reg_read8(TRMREG_DMA_STATUS);
			while (!(TempDMAstatus & DMAXFERCOMP))
				TempDMAstatus = trm_reg_read8(TRMREG_DMA_STATUS);
			pSRB->SRBTotalXferLength = 0;
		} else {  
	  	  /*
   		   * parsing the case:
	   	   * when a transfer not yet complete 
	   	   * but be disconnected by uper layer
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
			pseg = pSRB->pSRBSGL + pSRB->SRBSGIndex;
			for (SGIndexTemp = pSRB->SRBSGIndex; 
			    SGIndexTemp < pSRB->SRBSGCount;
			    SGIndexTemp++) {
			  /* 
	   		   * find last time which SG transfer be disconnect 
	   		   */
	 			if (TempSRBXferredLength >= pseg->length)
					TempSRBXferredLength -= pseg->length;
				else {
		  		  /*
   				   * update last time disconnected SG list
				   */
					pseg->length -= TempSRBXferredLength;
					/* residue data length  */
					pseg->address += TempSRBXferredLength;
					/* residue data pointer */
					pSRB->SRBSGIndex = SGIndexTemp;
					break;
				} 
				pseg++;
			}
	  	  }
		}
	}
}