#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int u_int16_t ;
struct TYPE_9__ {int SRBState; int /*<<< orphan*/  ScsiPhase; } ;
struct TYPE_11__ {int /*<<< orphan*/  AdaptSCSIID; TYPE_1__ TmpSRB; TYPE_2__* pActiveDCB; TYPE_2__* pLinkDCB; } ;
struct TYPE_10__ {int SyncMode; int DCBFlag; int /*<<< orphan*/  SyncOffset; int /*<<< orphan*/  SyncPeriod; TYPE_1__* pActiveSRB; struct TYPE_10__* pNextDCB; int /*<<< orphan*/  TargetID; } ;
typedef  TYPE_1__* PSRB ;
typedef  TYPE_2__* PDCB ;
typedef  TYPE_3__* PACB ;

/* Variables and functions */
 int ABORT_DEV_ ; 
 int /*<<< orphan*/  DO_DATALATCH ; 
 int EN_TAG_QUEUING ; 
 int /*<<< orphan*/  PH_BUS_FREE ; 
 int /*<<< orphan*/  SCMD_MSGACCEPT ; 
 int SRB_ABORT_SENT ; 
 int SRB_DATA_XFER ; 
 int SRB_DISCONNECT ; 
 int SRB_READY ; 
 int SRB_UNEXPECT_RESEL ; 
 int /*<<< orphan*/  TRMREG_SCSI_COMMAND ; 
 int /*<<< orphan*/  TRMREG_SCSI_CONTROL ; 
 int /*<<< orphan*/  TRMREG_SCSI_HOSTID ; 
 int /*<<< orphan*/  TRMREG_SCSI_OFFSET ; 
 int /*<<< orphan*/  TRMREG_SCSI_SYNC ; 
 int /*<<< orphan*/  TRMREG_SCSI_TARGETID ; 
 int /*<<< orphan*/  TRM_DPRINTF (char*) ; 
 int /*<<< orphan*/  trm_EnableMsgOutAbort1 (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  trm_RewaitSRB (TYPE_2__*,TYPE_1__*) ; 
 int trm_reg_read16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trm_reg_write16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trm_reg_write8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
trm_Reselect(PACB pACB)
{
	PDCB		pDCB;
	PSRB		pSRB;
	u_int16_t	RselTarLunId;

	TRM_DPRINTF("trm_Reselect................. \n");
	pDCB = pACB->pActiveDCB;
	if (pDCB) {
	  /* Arbitration lost but Reselection win */
		pSRB = pDCB->pActiveSRB;
		pSRB->SRBState = SRB_READY;
		trm_RewaitSRB(pDCB, pSRB);
	}
	/* Read Reselected Target Id and LUN */
	RselTarLunId = trm_reg_read16(TRMREG_SCSI_TARGETID) & 0x1FFF;
	pDCB = pACB->pLinkDCB;
	while (RselTarLunId != *((u_int16_t *) &pDCB->TargetID)) {
	  /* get pDCB of the reselect id */
		pDCB = pDCB->pNextDCB;
	}

	pACB->pActiveDCB = pDCB;
	if (pDCB->SyncMode & EN_TAG_QUEUING) {
		pSRB = &pACB->TmpSRB;
		pDCB->pActiveSRB = pSRB;
	} else {
		pSRB = pDCB->pActiveSRB;
		if (!pSRB || !(pSRB->SRBState & SRB_DISCONNECT)) {
		  /*
	   	   * abort command
   		   */
			pSRB = &pACB->TmpSRB;
			pSRB->SRBState = SRB_UNEXPECT_RESEL;
			pDCB->pActiveSRB = pSRB;
			trm_EnableMsgOutAbort1(pACB, pSRB);
		} else {
			if (pDCB->DCBFlag & ABORT_DEV_) {
				pSRB->SRBState = SRB_ABORT_SENT;
				trm_EnableMsgOutAbort1(pACB, pSRB);
			} else 
				pSRB->SRBState = SRB_DATA_XFER;
		}
	}
	pSRB->ScsiPhase = PH_BUS_FREE;
	/* SCSI bus free Phase */
	/* 
	 * Program HA ID, target ID, period and offset
	 */
	trm_reg_write8((u_int8_t) RselTarLunId,TRMREG_SCSI_TARGETID);
	/* target ID */
	trm_reg_write8(pACB->AdaptSCSIID,TRMREG_SCSI_HOSTID);
	/* host   ID */
	trm_reg_write8(pDCB->SyncPeriod,TRMREG_SCSI_SYNC);
	/* period    */
	trm_reg_write8(pDCB->SyncOffset,TRMREG_SCSI_OFFSET); 
	/* offset    */
	trm_reg_write16(DO_DATALATCH, TRMREG_SCSI_CONTROL);
	/* it's important for atn stop*/
	/*
	 * SCSI cammand 
	 */
	trm_reg_write8(SCMD_MSGACCEPT, TRMREG_SCSI_COMMAND);
	/* to rls the /ACK signal */
}