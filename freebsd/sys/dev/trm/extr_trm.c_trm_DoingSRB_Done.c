#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  status; } ;
union ccb {TYPE_1__ ccb_h; } ;
typedef  scalar_t__ u_int16_t ;
struct TYPE_9__ {TYPE_2__* pFreeSRB; TYPE_3__* pLinkDCB; } ;
struct TYPE_8__ {scalar_t__ GoingSRBCnt; struct TYPE_8__* pNextDCB; TYPE_2__* pGoingSRB; } ;
struct TYPE_7__ {struct TYPE_7__* pNextSRB; union ccb* pccb; } ;
typedef  TYPE_2__* PSRB ;
typedef  TYPE_3__* PDCB ;
typedef  TYPE_4__* PACB ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_SEL_TIMEOUT ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 

__attribute__((used)) static void
trm_DoingSRB_Done(PACB pACB)
{
	PDCB		pDCB, pdcb;
	PSRB		psrb, psrb2;
	u_int16_t	cnt, i;
	union ccb 	*pccb;

	pDCB = pACB->pLinkDCB;
	if (pDCB == NULL) 
  		return;
	pdcb = pDCB;
    	do {
		cnt = pdcb->GoingSRBCnt;
		psrb = pdcb->pGoingSRB;
		for (i = 0; i < cnt; i++) {
			psrb2 = psrb->pNextSRB;
		    	pccb = psrb->pccb;
			pccb->ccb_h.status = CAM_SEL_TIMEOUT;
			/*  ReleaseSRB(pDCB, pSRB); */
			psrb->pNextSRB = pACB->pFreeSRB;
			pACB->pFreeSRB = psrb;
			xpt_done(pccb);
			psrb  = psrb2;
		}
		pdcb->GoingSRBCnt = 0;
		pdcb->pGoingSRB = NULL;
		pdcb = pdcb->pNextDCB;
	}
	while (pdcb != pDCB);
}