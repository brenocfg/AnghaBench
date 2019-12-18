#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int ACBFlag; TYPE_2__* pDCBRunRobin; TYPE_2__* pLinkDCB; int /*<<< orphan*/  pActiveDCB; } ;
struct TYPE_9__ {scalar_t__ MaxActiveCommandCnt; scalar_t__ GoingSRBCnt; TYPE_1__* pGoingLastSRB; TYPE_1__* pGoingSRB; TYPE_1__* pWaitingSRB; TYPE_1__* pWaitingLastSRB; struct TYPE_9__* pNextDCB; } ;
struct TYPE_8__ {struct TYPE_8__* pNextSRB; } ;
typedef  TYPE_1__* PSRB ;
typedef  TYPE_2__* PDCB ;
typedef  TYPE_3__* PACB ;

/* Variables and functions */
 int RESET_DETECT ; 
 int RESET_DEV ; 
 int RESET_DONE ; 
 int splcam () ; 
 int /*<<< orphan*/  splx (int) ; 
 int /*<<< orphan*/  trm_StartSCSI (TYPE_3__*,TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static void
trm_DoWaitingSRB(PACB pACB)
{
	int	intflag;
	PDCB	ptr, ptr1;
	PSRB	pSRB;

	intflag = splcam();
    	if (!(pACB->pActiveDCB) && 
	    !(pACB->ACBFlag & (RESET_DETECT+RESET_DONE+RESET_DEV))) {
		ptr = pACB->pDCBRunRobin;
		if (!ptr) {
			ptr = pACB->pLinkDCB;
			pACB->pDCBRunRobin = ptr;
		}
		ptr1 = ptr;
		for (;ptr1 ;) {
			pACB->pDCBRunRobin = ptr1->pNextDCB;
			if (!(ptr1->MaxActiveCommandCnt > ptr1->GoingSRBCnt) 
			    || !(pSRB = ptr1->pWaitingSRB)) {
				if (pACB->pDCBRunRobin == ptr)
					break;
				ptr1 = ptr1->pNextDCB;
			} else {
				if (!trm_StartSCSI(pACB, ptr1, pSRB)) {
				/* 
				 * If trm_StartSCSI return 0 :
				 * current interrupt status is interrupt enable 
				 * It's said that SCSI processor is unoccupied 
				 */
					ptr1->GoingSRBCnt++;
					if (ptr1->pWaitingLastSRB == pSRB) {
						ptr1->pWaitingSRB = NULL;
						ptr1->pWaitingLastSRB = NULL;
					} else
						ptr1->pWaitingSRB = pSRB->pNextSRB;
					pSRB->pNextSRB = NULL;
					if (ptr1->pGoingSRB) 
						ptr1->pGoingLastSRB->pNextSRB = pSRB;
					else
						ptr1->pGoingSRB = pSRB;
					ptr1->pGoingLastSRB = pSRB;
				}
				break;
			}
		}
	}
	splx(intflag);
	return;
}