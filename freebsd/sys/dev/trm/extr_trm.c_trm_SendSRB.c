#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct TYPE_15__ {int ACBFlag; scalar_t__ pActiveDCB; } ;
struct TYPE_14__ {scalar_t__ MaxActiveCommandCnt; scalar_t__ GoingSRBCnt; TYPE_1__* pGoingLastSRB; TYPE_1__* pGoingSRB; TYPE_1__* pWaitingSRB; } ;
struct TYPE_13__ {struct TYPE_13__* pNextSRB; TYPE_2__* pSRBDCB; } ;
typedef  TYPE_1__* PSRB ;
typedef  TYPE_2__* PDCB ;
typedef  TYPE_3__* PACB ;

/* Variables and functions */
 int RESET_DETECT ; 
 int RESET_DEV ; 
 int RESET_DONE ; 
 int /*<<< orphan*/  TRM_DPRINTF (char*,int) ; 
 int /*<<< orphan*/  trm_RewaitSRB0 (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  trm_SRBwaiting (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  trm_StartSCSI (TYPE_3__*,TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static void
trm_SendSRB(PACB pACB, PSRB pSRB)
{
	PDCB	pDCB;

	pDCB = pSRB->pSRBDCB;
	if (!(pDCB->MaxActiveCommandCnt > pDCB->GoingSRBCnt) || (pACB->pActiveDCB)
	    || (pACB->ACBFlag & (RESET_DETECT+RESET_DONE+RESET_DEV))) {
		TRM_DPRINTF("pDCB->MaxCommand=%d \n",pDCB->MaxActiveCommandCnt);        
		TRM_DPRINTF("pDCB->GoingSRBCnt=%d \n",pDCB->GoingSRBCnt);
		TRM_DPRINTF("pACB->pActiveDCB=%8x \n",(u_int)pACB->pActiveDCB);
		TRM_DPRINTF("pACB->ACBFlag=%x \n",pACB->ACBFlag);
	    	trm_SRBwaiting(pDCB, pSRB);
		goto SND_EXIT;
	}

	if (pDCB->pWaitingSRB) {
		trm_SRBwaiting(pDCB, pSRB);
		pSRB = pDCB->pWaitingSRB;
		pDCB->pWaitingSRB = pSRB->pNextSRB;
		pSRB->pNextSRB = NULL;
	}

	if (!trm_StartSCSI(pACB, pDCB, pSRB)) { 
	/* 
	 * If trm_StartSCSI return 0 :
	 * current interrupt status is interrupt enable 
	 * It's said that SCSI processor is unoccupied 
	 */
		pDCB->GoingSRBCnt++; /* stack waiting SRB*/
		if (pDCB->pGoingSRB) {
			pDCB->pGoingLastSRB->pNextSRB = pSRB;
			pDCB->pGoingLastSRB = pSRB;
		} else {
			pDCB->pGoingSRB = pSRB;
			pDCB->pGoingLastSRB = pSRB;
		}
	} else {
	/* 
	 * If trm_StartSCSI return 1 :
	 * current interrupt status is interrupt disreenable 
	 * It's said that SCSI processor has more one SRB need to do
	 */
		trm_RewaitSRB0(pDCB, pSRB);
	}
SND_EXIT:
	return;
}