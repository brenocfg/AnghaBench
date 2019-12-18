#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
typedef  size_t u_int8_t ;
typedef  size_t u_int32_t ;
typedef  size_t u_int16_t ;
typedef  size_t u_int ;
struct TYPE_20__ {scalar_t__ pLinkDCB; int AdaptType; int Config; TYPE_11__** DCBarray; int /*<<< orphan*/  DeviceCnt; TYPE_6__* pDCBRunRobin; } ;
struct TYPE_16__ {void* width; scalar_t__ offset; scalar_t__ period; } ;
struct TYPE_15__ {int offset; void* width; int /*<<< orphan*/  period; } ;
struct TYPE_17__ {TYPE_3__ current; TYPE_2__ user; int /*<<< orphan*/  disc_tag; } ;
struct TYPE_19__ {size_t TargetID; size_t TargetLUN; int MaxActiveCommandCnt; int DCBstatus; int DevMode; size_t IdentifyMsg; int SyncMode; TYPE_4__ tinfo; int /*<<< orphan*/  MaxNegoPeriod; scalar_t__ SyncOffset; scalar_t__ SyncPeriod; int /*<<< orphan*/  AdpMode; scalar_t__ DCBFlag; int /*<<< orphan*/ * pActiveSRB; scalar_t__ GoingSRBCnt; int /*<<< orphan*/ * pGoingSRB; int /*<<< orphan*/ * pWaitingSRB; struct TYPE_19__* pNextDCB; } ;
struct TYPE_18__ {TYPE_1__* NvramTarget; int /*<<< orphan*/  NvramChannelCfg; } ;
struct TYPE_14__ {int NvmTarCfg0; int NvmTarPeriod; } ;
struct TYPE_13__ {int DCBstatus; } ;
typedef  int /*<<< orphan*/  TRM_DCB ;
typedef  TYPE_5__* PNVRAMTYPE ;
typedef  TYPE_6__* PDCB ;
typedef  TYPE_7__* PACB ;

/* Variables and functions */
 int DS_IN_QUEUE ; 
 int HCC_WIDE_CARD ; 
 void* MSG_EXT_WDTR_BUS_16_BIT ; 
 void* MSG_EXT_WDTR_BUS_8_BIT ; 
 int NTC_DO_DISCONNECT ; 
 int NTC_DO_SYNC_NEGO ; 
 int NTC_DO_WIDE_NEGO ; 
 int SYNC_NEGO_ENABLE ; 
 int TAG_QUEUING_ ; 
 int /*<<< orphan*/  TRM_USR_DISCENB ; 
 int /*<<< orphan*/  TRM_USR_TAGENB ; 
 int WIDE_NEGO_ENABLE ; 
 int /*<<< orphan*/  bcopy (TYPE_11__*,TYPE_6__*,int) ; 
 int /*<<< orphan*/ * dc395u2x_clock_period ; 
 int /*<<< orphan*/ * dc395x_clock_period ; 
 int splcam () ; 
 int /*<<< orphan*/  splx (int) ; 
 TYPE_5__* trm_eepromBuf ; 

__attribute__((used)) static void
trm_initDCB(PACB pACB, PDCB pDCB, u_int16_t unit,u_int32_t i,u_int32_t j)
{
	PNVRAMTYPE 	pEEpromBuf;
	u_int8_t	bval,PeriodIndex;
	u_int		target_id,target_lun;
	PDCB		pTempDCB;
	int		intflag;
    
    	target_id  = i;
	target_lun = j;

	/*
	 *  Using the lun 0 device to init other DCB first, if the device 
	 *  has been initialized.
	 *  I don't want init sync arguments one by one, it is the same.
	 */
	if (target_lun != 0 && 
	    (pACB->DCBarray[target_id][0].DCBstatus & DS_IN_QUEUE))
		bcopy(&pACB->DCBarray[target_id][0], pDCB, 
		    sizeof(TRM_DCB));
	intflag = splcam();
	if (pACB->pLinkDCB == 0) {
		pACB->pLinkDCB = pDCB;
		/* 
		 * RunRobin impersonate the role 
		 * that let each device had good proportion 
		 * about SCSI command proceeding 
		 */
		pACB->pDCBRunRobin = pDCB;
		pDCB->pNextDCB = pDCB;
	} else {
		pTempDCB=pACB->pLinkDCB;
		/* search the last nod of DCB link */
		while (pTempDCB->pNextDCB != pACB->pLinkDCB)
			pTempDCB = pTempDCB->pNextDCB;
		/* connect current DCB with last DCB tail */
		pTempDCB->pNextDCB = pDCB;
		/* connect current DCB tail to this DCB Q head */
		pDCB->pNextDCB=pACB->pLinkDCB;
	}
	splx(intflag);

	pACB->DeviceCnt++;
	pDCB->TargetID = target_id;
	pDCB->TargetLUN =  target_lun;
	pDCB->pWaitingSRB = NULL;
	pDCB->pGoingSRB = NULL;
	pDCB->GoingSRBCnt = 0;
	pDCB->pActiveSRB = NULL;
	pDCB->MaxActiveCommandCnt = 1;
	pDCB->DCBFlag = 0;
	pDCB->DCBstatus |= DS_IN_QUEUE;
	/* $$$$$$$ */
	pEEpromBuf = &trm_eepromBuf[unit];
	pDCB->DevMode = pEEpromBuf->NvramTarget[target_id].NvmTarCfg0;
	pDCB->AdpMode = pEEpromBuf->NvramChannelCfg;
	/* $$$$$$$ */
	/* 
	 * disconnect enable ?
	 */
	if (pDCB->DevMode & NTC_DO_DISCONNECT) {
		bval = 0xC0;
		pDCB->tinfo.disc_tag |= TRM_USR_DISCENB ;
	} else {
		bval = 0x80;
		pDCB->tinfo.disc_tag &= ~(TRM_USR_DISCENB);
	}
	bval |= target_lun;
	pDCB->IdentifyMsg = bval;
	if (target_lun != 0 && 
	    (pACB->DCBarray[target_id][0].DCBstatus & DS_IN_QUEUE))
		return;
	/* $$$$$$$ */
	/*
	 * tag Qing enable ?
	 */
	if (pDCB->DevMode & TAG_QUEUING_) {
		pDCB->tinfo.disc_tag |= TRM_USR_TAGENB ;
	} else
		pDCB->tinfo.disc_tag &= ~(TRM_USR_TAGENB);
	/* $$$$$$$ */
	/*
	 * wide nego ,sync nego enable ?
	 */
	pDCB->SyncPeriod = 0;
	pDCB->SyncOffset = 0;
	PeriodIndex = pEEpromBuf->NvramTarget[target_id].NvmTarPeriod & 0x07;
	if (pACB->AdaptType==1) {/* is U2? */
	    pDCB->MaxNegoPeriod=dc395u2x_clock_period[ PeriodIndex ];
	    pDCB->tinfo.user.period=pDCB->MaxNegoPeriod;
	    pDCB->tinfo.user.offset=(pDCB->SyncMode & SYNC_NEGO_ENABLE) ? 31 : 0;
	} else {
        pDCB->MaxNegoPeriod=dc395x_clock_period[ PeriodIndex ];
	    pDCB->tinfo.user.period=pDCB->MaxNegoPeriod;
	    pDCB->tinfo.user.offset=(pDCB->SyncMode & SYNC_NEGO_ENABLE) ? 15 : 0;
	}
	pDCB->SyncMode = 0;
	if ((pDCB->DevMode & NTC_DO_WIDE_NEGO) && 
	    (pACB->Config & HCC_WIDE_CARD))
		pDCB->SyncMode |= WIDE_NEGO_ENABLE;
	/* enable wide nego */
   	if (pDCB->DevMode & NTC_DO_SYNC_NEGO)
		pDCB->SyncMode |= SYNC_NEGO_ENABLE;
	/* enable sync nego */
	/* $$$$$$$ */
	/*
	 *	Fill in tinfo structure.
	 */
	pDCB->tinfo.user.width  = (pDCB->SyncMode & WIDE_NEGO_ENABLE) ? 
	  MSG_EXT_WDTR_BUS_16_BIT : MSG_EXT_WDTR_BUS_8_BIT;

	pDCB->tinfo.current.period = 0;
	pDCB->tinfo.current.offset = 0;
	pDCB->tinfo.current.width = MSG_EXT_WDTR_BUS_8_BIT;
}