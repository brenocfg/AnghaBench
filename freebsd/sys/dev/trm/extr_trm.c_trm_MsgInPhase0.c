#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int8_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct TYPE_19__ {int SRBState; scalar_t__* MsgInBuf; int MsgCnt; scalar_t__* pMsgPtr; scalar_t__ TagNumber; TYPE_5__* pSRBDCB; int /*<<< orphan*/ * MsgOutBuf; struct TYPE_19__* pNextSRB; } ;
struct TYPE_21__ {int AdaptType; TYPE_4__ TmpSRB; TYPE_5__* pActiveDCB; } ;
struct TYPE_17__ {int offset; void* period; void* width; } ;
struct TYPE_16__ {int offset; void* period; void* width; } ;
struct TYPE_18__ {TYPE_2__ current; TYPE_1__ goal; } ;
struct TYPE_20__ {int SyncMode; int SyncPeriod; int SyncOffset; int DCBFlag; int MaxNegoPeriod; TYPE_3__ tinfo; TYPE_4__* pActiveSRB; TYPE_4__* pGoingLastSRB; TYPE_4__* pGoingSRB; } ;
typedef  TYPE_4__* PSRB ;
typedef  TYPE_5__* PDCB ;
typedef  TYPE_6__* PACB ;

/* Variables and functions */
 int ABORT_DEV_ ; 
 scalar_t__ ALT_SYNC ; 
 int /*<<< orphan*/  DO_CLRATN ; 
 int /*<<< orphan*/  DO_DATALATCH ; 
 int /*<<< orphan*/  DO_SETATN ; 
 int EN_ATN_STOP ; 
 scalar_t__ LVDS_SYNC ; 
 int /*<<< orphan*/  MSG_ABORT_TAG ; 
 scalar_t__ MSG_DISCONNECT ; 
 scalar_t__ MSG_EXTENDED ; 
 void* MSG_EXT_WDTR_BUS_16_BIT ; 
 void* MSG_EXT_WDTR_BUS_8_BIT ; 
 scalar_t__ MSG_IGNOREWIDE ; 
 scalar_t__ MSG_ORDER_QTAG ; 
 scalar_t__ MSG_REJECT_ ; 
 scalar_t__ MSG_SAVE_PTR ; 
 scalar_t__ MSG_SIMPLE_QTAG ; 
 int /*<<< orphan*/  PH_BUS_FREE ; 
 int SCMD_MSGACCEPT ; 
 int SRB_ABORT_SENT ; 
 int SRB_DATA_XFER ; 
 int SRB_DISCONNECT ; 
 int SRB_DO_SYNC_NEGO ; 
 int SRB_DO_WIDE_NEGO ; 
 int SRB_EXTEND_MSGIN ; 
 int SRB_MSGIN ; 
 int SRB_MSGOUT ; 
 int SRB_UNEXPECT_RESEL ; 
 int SYNC_NEGO_DONE ; 
 int SYNC_NEGO_ENABLE ; 
 int /*<<< orphan*/  TRMREG_SCSI_COMMAND ; 
 int /*<<< orphan*/  TRMREG_SCSI_CONTROL ; 
 int /*<<< orphan*/  TRMREG_SCSI_COUNTER ; 
 int /*<<< orphan*/  TRMREG_SCSI_FIFO ; 
 int /*<<< orphan*/  TRMREG_SCSI_OFFSET ; 
 int /*<<< orphan*/  TRMREG_SCSI_SYNC ; 
 int /*<<< orphan*/  TRM_DPRINTF (char*,...) ; 
 int WIDE_NEGO_DONE ; 
 int WIDE_NEGO_ENABLE ; 
 int WIDE_SYNC ; 
 scalar_t__* dc395u2x_clock_period ; 
 void** dc395u2x_tinfo_period ; 
 scalar_t__* dc395x_clock_period ; 
 void** dc395x_tinfo_period ; 
 int /*<<< orphan*/  trm_EnableMsgOutAbort1 (TYPE_6__*,TYPE_4__*) ; 
 int /*<<< orphan*/  trm_EnableMsgOutAbort2 (TYPE_6__*,TYPE_4__*) ; 
 int /*<<< orphan*/  trm_SetXferRate (TYPE_6__*,TYPE_4__*,TYPE_5__*) ; 
 scalar_t__ trm_reg_read8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trm_reg_write16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trm_reg_write32 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trm_reg_write8 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
trm_MsgInPhase0(PACB pACB, PSRB pSRB, u_int16_t *pscsi_status)
{
	u_int8_t	message_in_code,bIndex,message_in_tag_id;
	PDCB		pDCB;
	PSRB		pSRBTemp;

	pDCB = pACB->pActiveDCB;

	message_in_code = trm_reg_read8(TRMREG_SCSI_FIFO);
	if (!(pSRB->SRBState & SRB_EXTEND_MSGIN)) {
		if (message_in_code == MSG_DISCONNECT) {
			pSRB->SRBState = SRB_DISCONNECT;
			*pscsi_status = PH_BUS_FREE; /* .. initial phase */
			/* it's important for atn stop */
			trm_reg_write16(DO_DATALATCH, TRMREG_SCSI_CONTROL);
			/*
			 * SCSI command
			 */
			trm_reg_write8(SCMD_MSGACCEPT, TRMREG_SCSI_COMMAND);
			return;
		} else if (message_in_code == MSG_SAVE_PTR) {
			*pscsi_status = PH_BUS_FREE; /* .. initial phase */
			/* it's important for atn stop */
			trm_reg_write16(DO_DATALATCH, TRMREG_SCSI_CONTROL);
			/*
			 * SCSI command
			 */
			trm_reg_write8(SCMD_MSGACCEPT, TRMREG_SCSI_COMMAND);
			return;
		} else if ((message_in_code == MSG_EXTENDED) ||
		    ((message_in_code >= MSG_SIMPLE_QTAG) &&
		     (message_in_code <= MSG_ORDER_QTAG))) {
			pSRB->SRBState |= SRB_EXTEND_MSGIN;
		    	pSRB->MsgInBuf[0] = message_in_code;
			/* extended message      (01h) */
			pSRB->MsgCnt = 1;
			pSRB->pMsgPtr = &pSRB->MsgInBuf[1];
			/* extended message length (n) */
			*pscsi_status = PH_BUS_FREE; /* .. initial phase */
			/* it's important for atn stop */
			trm_reg_write16(DO_DATALATCH, TRMREG_SCSI_CONTROL);
			/*
			 * SCSI command
			 */
			trm_reg_write8(SCMD_MSGACCEPT, TRMREG_SCSI_COMMAND);
			return;
		} else if (message_in_code == MSG_REJECT_) {
			/* Reject message */
			if (pDCB->SyncMode & WIDE_NEGO_ENABLE) {
			  /* do wide nego reject */
				pDCB = pSRB->pSRBDCB;
				pDCB->SyncMode |= WIDE_NEGO_DONE;
				pDCB->SyncMode &= ~(SYNC_NEGO_DONE | 
				    EN_ATN_STOP | WIDE_NEGO_ENABLE);
				pSRB->SRBState &= ~(SRB_DO_WIDE_NEGO+SRB_MSGIN);
				if ((pDCB->SyncMode & SYNC_NEGO_ENABLE) 
				    && !(pDCB->SyncMode & SYNC_NEGO_DONE)) {   
				  /* Set ATN, in case ATN was clear */
					pSRB->SRBState |= SRB_MSGOUT;
					trm_reg_write16(
					    DO_SETATN,
					    TRMREG_SCSI_CONTROL);
				} else {   
			  	  /* Clear ATN */
					trm_reg_write16(
					    DO_CLRATN,
					    TRMREG_SCSI_CONTROL);
				}
			} else if (pDCB->SyncMode & SYNC_NEGO_ENABLE) { 
			  /* do sync nego reject */
				trm_reg_write16(DO_CLRATN,TRMREG_SCSI_CONTROL);
				if (pSRB->SRBState & SRB_DO_SYNC_NEGO) {
					pDCB = pSRB->pSRBDCB;
					pDCB->SyncMode &= 
					  ~(SYNC_NEGO_ENABLE+SYNC_NEGO_DONE); 
					pDCB->SyncPeriod = 0;
					pDCB->SyncOffset = 0;
					/*               
					 *
					 *   program SCSI control register
					 *
					 */
					trm_reg_write8(pDCB->SyncPeriod,
					    TRMREG_SCSI_SYNC);
					trm_reg_write8(pDCB->SyncOffset,
					    TRMREG_SCSI_OFFSET);
					trm_SetXferRate(pACB,pSRB,pDCB);
				}
			}
			*pscsi_status = PH_BUS_FREE; /* .. initial phase */
			/* it's important for atn stop */
			trm_reg_write16(DO_DATALATCH, TRMREG_SCSI_CONTROL);
			/*
			 * SCSI command
			 */
			trm_reg_write8(SCMD_MSGACCEPT, TRMREG_SCSI_COMMAND);
			return;
		} else if (message_in_code == MSG_IGNOREWIDE) {
			trm_reg_write32(1, TRMREG_SCSI_COUNTER);
			trm_reg_read8(TRMREG_SCSI_FIFO);
			*pscsi_status = PH_BUS_FREE; /* .. initial phase */
			/* it's important for atn stop */
			trm_reg_write16(DO_DATALATCH, TRMREG_SCSI_CONTROL);
			/*
			 * SCSI command
			 */
			trm_reg_write8(SCMD_MSGACCEPT, TRMREG_SCSI_COMMAND);
			return;
		} else {
	  	  /* Restore data pointer message */
  		  /* Save data pointer message	  */
		  /* Completion message		  */
		  /* NOP message       	          */
			*pscsi_status = PH_BUS_FREE; /* .. initial phase */
			/* it's important for atn stop */
			trm_reg_write16(DO_DATALATCH, TRMREG_SCSI_CONTROL);
			/*
			 * SCSI command
			 */
			trm_reg_write8(SCMD_MSGACCEPT, TRMREG_SCSI_COMMAND);
			return;
		}
	} else {	
	  /* 
   	   * Parsing incoming extented messages 
	   */
		*pSRB->pMsgPtr = message_in_code;
		pSRB->MsgCnt++;
		pSRB->pMsgPtr++;
		TRM_DPRINTF("pSRB->MsgInBuf[0]=%2x \n ",pSRB->MsgInBuf[0]);
		TRM_DPRINTF("pSRB->MsgInBuf[1]=%2x \n ",pSRB->MsgInBuf[1]);
		TRM_DPRINTF("pSRB->MsgInBuf[2]=%2x \n ",pSRB->MsgInBuf[2]);
		TRM_DPRINTF("pSRB->MsgInBuf[3]=%2x \n ",pSRB->MsgInBuf[3]);
		TRM_DPRINTF("pSRB->MsgInBuf[4]=%2x \n ",pSRB->MsgInBuf[4]);
	    	if ((pSRB->MsgInBuf[0] >= MSG_SIMPLE_QTAG)
		    && (pSRB->MsgInBuf[0] <= MSG_ORDER_QTAG)) {
		  /*
	   	   * is QUEUE tag message :
   		   *
	   	   * byte 0:
	   	   * HEAD    QUEUE TAG (20h)
	   	   * ORDERED QUEUE TAG (21h)
	   	   * SIMPLE  QUEUE TAG (22h)
	   	   * byte 1:
	   	   * Queue tag (00h - FFh)
	   	   */
			if (pSRB->MsgCnt == 2) {
				pSRB->SRBState = 0;
				message_in_tag_id = pSRB->MsgInBuf[1];
				pSRB = pDCB->pGoingSRB;
				pSRBTemp = pDCB->pGoingLastSRB;
				if (pSRB) {
					for (;;) {
						if (pSRB->TagNumber != 
						    message_in_tag_id) {
							if (pSRB == pSRBTemp) {
								goto  mingx0;
							}
							pSRB = pSRB->pNextSRB;
						} else
							break;
					}
					if (pDCB->DCBFlag & ABORT_DEV_) {
						pSRB->SRBState = SRB_ABORT_SENT;
						trm_EnableMsgOutAbort1(
						    pACB, pSRB);
					}
					if (!(pSRB->SRBState & SRB_DISCONNECT)) {
						TRM_DPRINTF("SRB not yet disconnect........ \n ");
						goto  mingx0;
					}
					pDCB->pActiveSRB = pSRB;
					pSRB->SRBState = SRB_DATA_XFER;
				} else {
mingx0:
	     				pSRB = &pACB->TmpSRB;
					pSRB->SRBState = SRB_UNEXPECT_RESEL;
					pDCB->pActiveSRB = pSRB;
					pSRB->MsgOutBuf[0] = MSG_ABORT_TAG;
					trm_EnableMsgOutAbort2(
					    pACB,
					    pSRB);
				}
			}
			*pscsi_status = PH_BUS_FREE;
			/* .. initial phase */
			trm_reg_write16(DO_DATALATCH, TRMREG_SCSI_CONTROL);
			/* it's important for atn stop */
			/*
			 * SCSI command 
			 */
			trm_reg_write8(SCMD_MSGACCEPT, TRMREG_SCSI_COMMAND);
			return;
		} else if ((pSRB->MsgInBuf[0] == MSG_EXTENDED) &&
		    (pSRB->MsgInBuf[2] == 3) && (pSRB->MsgCnt == 4)) {
		  /*
	   	   * is Wide data xfer Extended message :
	   	   * ======================================
	   	   * WIDE DATA TRANSFER REQUEST
   		   * ======================================
		   * byte 0 :  Extended message (01h)
		   * byte 1 :  Extended message length (02h)
		   * byte 2 :  WIDE DATA TRANSFER code (03h)
		   * byte 3 :  Transfer width exponent 
		   */
			pDCB = pSRB->pSRBDCB;
			pSRB->SRBState &= ~(SRB_EXTEND_MSGIN+SRB_DO_WIDE_NEGO);
			if ((pSRB->MsgInBuf[1] != 2)) {
			  /* Length is wrong, reject it  */
				pDCB->SyncMode &=
				  ~(WIDE_NEGO_ENABLE+WIDE_NEGO_DONE); 
				pSRB->MsgCnt = 1;
				pSRB->MsgInBuf[0] = MSG_REJECT_;
				trm_reg_write16(DO_SETATN, TRMREG_SCSI_CONTROL);
				*pscsi_status = PH_BUS_FREE; /* .. initial phase */
				/* it's important for atn stop */
				trm_reg_write16(DO_DATALATCH, TRMREG_SCSI_CONTROL);
				/*
				 * SCSI command
				 */
				trm_reg_write8(SCMD_MSGACCEPT, TRMREG_SCSI_COMMAND);
				return;
			}
			if (pDCB->SyncMode & WIDE_NEGO_ENABLE) {		
			  /* Do wide negoniation */
				if (pSRB->MsgInBuf[3] > 2) {
				  /* > 32 bit	*/
				  /* reject_msg: */
					pDCB->SyncMode &= 
					  ~(WIDE_NEGO_ENABLE+WIDE_NEGO_DONE); 
					pSRB->MsgCnt = 1;
					pSRB->MsgInBuf[0] = MSG_REJECT_;
					trm_reg_write16(DO_SETATN,
					    TRMREG_SCSI_CONTROL);
					*pscsi_status = PH_BUS_FREE; /* .. initial phase */
					/* it's important for atn stop */
					trm_reg_write16(DO_DATALATCH, TRMREG_SCSI_CONTROL);
					/*
					 * SCSI command
					 */
					trm_reg_write8(SCMD_MSGACCEPT, TRMREG_SCSI_COMMAND);
					return;
				}
				if (pSRB->MsgInBuf[3] == 2) {
					pSRB->MsgInBuf[3] = 1;
					/* do 16 bits	*/
				} else {
					if (!(pDCB->SyncMode 
					      & WIDE_NEGO_DONE)) {
						pSRB->SRBState &=
						  ~(SRB_DO_WIDE_NEGO+SRB_MSGIN);
						pDCB->SyncMode |= 
						  WIDE_NEGO_DONE;
						pDCB->SyncMode &=
						  ~(SYNC_NEGO_DONE |
						      EN_ATN_STOP |
						      WIDE_NEGO_ENABLE);
						if (pSRB->MsgInBuf[3] != 0) {
						  /* is Wide data xfer */
							pDCB->SyncPeriod |=
							  WIDE_SYNC;
							pDCB->tinfo.current.width 
							  = MSG_EXT_WDTR_BUS_16_BIT;
							pDCB->tinfo.goal.width
							  = MSG_EXT_WDTR_BUS_16_BIT;
						}
					}
				}
			} else
				pSRB->MsgInBuf[3] = 0;
			pSRB->SRBState |= SRB_MSGOUT;
			trm_reg_write16(DO_SETATN,TRMREG_SCSI_CONTROL);
			*pscsi_status = PH_BUS_FREE; /* .. initial phase */
			/* it's important for atn stop */
			trm_reg_write16(DO_DATALATCH, TRMREG_SCSI_CONTROL);
			/*
			 * SCSI command
			 */
			trm_reg_write8(SCMD_MSGACCEPT, TRMREG_SCSI_COMMAND);
			return;
		} else if ((pSRB->MsgInBuf[0] == MSG_EXTENDED) &&
		    (pSRB->MsgInBuf[2] == 1) && (pSRB->MsgCnt == 5)) {
			/*
			 * is 8bit transfer Extended message :
			 * =================================
			 * SYNCHRONOUS DATA TRANSFER REQUEST
			 * =================================
			 * byte 0 :  Extended message (01h)
			 * byte 1 :  Extended message length (03)
			 * byte 2 :  SYNCHRONOUS DATA TRANSFER code (01h)
			 * byte 3 :  Transfer period factor 
			 * byte 4 :  REQ/ACK offset  
			 */
			pSRB->SRBState &= ~(SRB_EXTEND_MSGIN+SRB_DO_SYNC_NEGO);
			if ((pSRB->MsgInBuf[1] != 3) ||
			    (pSRB->MsgInBuf[2] != 1)) {
			  /* reject_msg: */
				pSRB->MsgCnt = 1;
				pSRB->MsgInBuf[0] = MSG_REJECT_;
				trm_reg_write16(DO_SETATN, TRMREG_SCSI_CONTROL);
				*pscsi_status = PH_BUS_FREE;
				/* .. initial phase */
				trm_reg_write16(DO_DATALATCH, TRMREG_SCSI_CONTROL);
				/* it's important for atn stop */
				/*
				 * SCSI cammand 
				 */
				trm_reg_write8(SCMD_MSGACCEPT, TRMREG_SCSI_COMMAND);
				return;
			} else if (!(pSRB->MsgInBuf[3]) || !(pSRB->MsgInBuf[4])) {
				/* set async */
				pDCB = pSRB->pSRBDCB;
				/* disable sync & sync nego */
				pDCB->SyncMode &= 
				  ~(SYNC_NEGO_ENABLE+SYNC_NEGO_DONE);
				pDCB->SyncPeriod = 0;
				pDCB->SyncOffset = 0;
				pDCB->tinfo.goal.period = 0;
				pDCB->tinfo.goal.offset = 0;
				pDCB->tinfo.current.period = 0;
				pDCB->tinfo.current.offset = 0;
				pDCB->tinfo.current.width = 
				  MSG_EXT_WDTR_BUS_8_BIT;
				/*               
				 *
				 *   program SCSI control register
				 *
				 */
				trm_reg_write8(pDCB->SyncPeriod,TRMREG_SCSI_SYNC);
				trm_reg_write8(pDCB->SyncOffset,TRMREG_SCSI_OFFSET);
				trm_SetXferRate(pACB,pSRB,pDCB);
				*pscsi_status = PH_BUS_FREE;
				/* .. initial phase */
				trm_reg_write16(DO_DATALATCH, TRMREG_SCSI_CONTROL);
				/* it's important for atn stop */
				/*
				 * SCSI cammand 
				 */
				trm_reg_write8(SCMD_MSGACCEPT, TRMREG_SCSI_COMMAND);
				return;
			} else {
				/* set sync */
				pDCB = pSRB->pSRBDCB;
				pDCB->SyncMode |= 
				  SYNC_NEGO_ENABLE+SYNC_NEGO_DONE;
				pDCB->MaxNegoPeriod = pSRB->MsgInBuf[3];
				/* Transfer period factor */
				pDCB->SyncOffset = pSRB->MsgInBuf[4]; 
				/* REQ/ACK offset */
				if (pACB->AdaptType == 1) {
					for(bIndex = 0; bIndex < 7; bIndex++) {
						if (pSRB->MsgInBuf[3] <=
					   dc395u2x_clock_period[bIndex]) {
				            pDCB->tinfo.goal.period =
						dc395u2x_tinfo_period[bIndex];
				            pDCB->tinfo.current.period =
						dc395u2x_tinfo_period[bIndex];
			                pDCB->tinfo.goal.offset = 
					    pDCB->SyncOffset;
					pDCB->tinfo.current.offset = 
					    pDCB->SyncOffset;
					pDCB->SyncPeriod |= (bIndex|LVDS_SYNC);
					break;
						}
					}
				} else {
					for(bIndex = 0; bIndex < 7; bIndex++) {
						if (pSRB->MsgInBuf[3] <=
						 dc395x_clock_period[bIndex]) {
						   pDCB->tinfo.goal.period =
						dc395x_tinfo_period[bIndex];
						   pDCB->tinfo.current.period =
						dc395x_tinfo_period[bIndex];
						   pDCB->tinfo.goal.offset =
						pDCB->SyncOffset;
						   pDCB->tinfo.current.offset =
					     	       pDCB->SyncOffset;
					     	   pDCB->SyncPeriod |=
				     		       (bIndex|ALT_SYNC);
			     			   break;
						}
					}
				}
				/*               
				 *
	 			 *   program SCSI control register
	 			 *
	 			 */
				trm_reg_write8(pDCB->SyncPeriod,
				    TRMREG_SCSI_SYNC);
				trm_reg_write8(pDCB->SyncOffset,
				    TRMREG_SCSI_OFFSET);
				trm_SetXferRate(pACB,pSRB,pDCB);
				*pscsi_status=PH_BUS_FREE;/*.. initial phase*/
				trm_reg_write16(DO_DATALATCH,TRMREG_SCSI_CONTROL);/* it's important for atn stop*/
	            /*
	            ** SCSI command 
	            */
				trm_reg_write8(SCMD_MSGACCEPT,TRMREG_SCSI_COMMAND);
				return;
			}
		}
	*pscsi_status = PH_BUS_FREE;
	/* .. initial phase */
	trm_reg_write16(DO_DATALATCH, TRMREG_SCSI_CONTROL);
	/* it's important for atn stop */
	/*
	 * SCSI cammand 
	 */
	trm_reg_write8(SCMD_MSGACCEPT, TRMREG_SCSI_COMMAND);
	}
}