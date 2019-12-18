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
typedef  scalar_t__ u_int16_t ;
struct TYPE_7__ {TYPE_2__* pLinkDCB; } ;
struct TYPE_6__ {scalar_t__ GoingSRBCnt; struct TYPE_6__* pNextDCB; TYPE_1__* pGoingSRB; TYPE_1__* pWaitingLastSRB; TYPE_1__* pWaitingSRB; } ;
struct TYPE_5__ {struct TYPE_5__* pNextSRB; } ;
typedef  TYPE_1__* PSRB ;
typedef  TYPE_2__* PDCB ;
typedef  TYPE_3__* PACB ;

/* Variables and functions */

__attribute__((used)) static void
trm_RecoverSRB(PACB pACB)
{
	PDCB		pDCB, pdcb;
	PSRB		psrb, psrb2;
       	u_int16_t	cnt, i;

	pDCB = pACB->pLinkDCB;
	if (pDCB == NULL)
		return;
	pdcb = pDCB;
	do {
		cnt = pdcb->GoingSRBCnt;
		psrb = pdcb->pGoingSRB;
		for (i = 0; i < cnt; i++) {
			psrb2 = psrb;
			psrb = psrb->pNextSRB;
			if (pdcb->pWaitingSRB) {
				psrb2->pNextSRB = pdcb->pWaitingSRB;
				pdcb->pWaitingSRB = psrb2;
			} else {
				pdcb->pWaitingSRB = psrb2;
				pdcb->pWaitingLastSRB = psrb2;
				psrb2->pNextSRB = NULL;
			}
		}
		pdcb->GoingSRBCnt = 0;
		pdcb->pGoingSRB = NULL;
		pdcb = pdcb->pNextDCB;
	}
	while (pdcb != pDCB);
}