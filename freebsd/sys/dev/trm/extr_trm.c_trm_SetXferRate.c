#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  path; } ;
union ccb {TYPE_5__ ccb_h; } ;
typedef  scalar_t__ u_int8_t ;
typedef  scalar_t__ u_int16_t ;
struct TYPE_14__ {int valid; int /*<<< orphan*/  sync_offset; int /*<<< orphan*/  sync_period; } ;
struct TYPE_15__ {TYPE_3__ spi; } ;
struct ccb_trans_settings {int /*<<< orphan*/  ccb_h; TYPE_4__ xport_specific; } ;
typedef  int /*<<< orphan*/  neg ;
struct TYPE_19__ {scalar_t__ DeviceCnt; TYPE_7__* pLinkDCB; } ;
struct TYPE_12__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  period; } ;
struct TYPE_13__ {TYPE_1__ goal; } ;
struct TYPE_18__ {int IdentifyMsg; scalar_t__ TargetID; struct TYPE_18__* pNextDCB; int /*<<< orphan*/  SyncMode; int /*<<< orphan*/  SyncOffset; int /*<<< orphan*/  SyncPeriod; TYPE_2__ tinfo; } ;
struct TYPE_17__ {union ccb* pccb; } ;
typedef  TYPE_6__* PSRB ;
typedef  TYPE_7__* PDCB ;
typedef  TYPE_8__* PACB ;

/* Variables and functions */
 int /*<<< orphan*/  AC_TRANSFER_NEG ; 
 int CTS_SPI_VALID_SYNC_OFFSET ; 
 int CTS_SPI_VALID_SYNC_RATE ; 
 int /*<<< orphan*/  TRM_DPRINTF (char*) ; 
 int /*<<< orphan*/  memset (struct ccb_trans_settings*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xpt_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ccb_trans_settings*) ; 
 int /*<<< orphan*/  xpt_setup_ccb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
trm_SetXferRate(PACB pACB,PSRB pSRB, PDCB pDCB)
{
	union ccb	*pccb;
	struct ccb_trans_settings neg;
	u_int16_t	cnt, i;
	u_int8_t	bval;
	PDCB		pDCBTemp;

	/*
	 * set all lun device's  period , offset
	 */
	TRM_DPRINTF("trm_SetXferRate\n");
	pccb = pSRB->pccb;
	memset(&neg, 0, sizeof (neg));
	neg.xport_specific.spi.sync_period = pDCB->tinfo.goal.period;
	neg.xport_specific.spi.sync_offset = pDCB->tinfo.goal.offset;
	neg.xport_specific.spi.valid =
	    CTS_SPI_VALID_SYNC_RATE | CTS_SPI_VALID_SYNC_OFFSET;
	xpt_setup_ccb(&neg.ccb_h, pccb->ccb_h.path, /* priority */1);
	xpt_async(AC_TRANSFER_NEG, pccb->ccb_h.path, &neg);
	if (!(pDCB->IdentifyMsg & 0x07)) {
		pDCBTemp = pACB->pLinkDCB;
		cnt = pACB->DeviceCnt;
		bval = pDCB->TargetID;
		for (i = 0; i < cnt; i++) {
			if (pDCBTemp->TargetID == bval) {
				pDCBTemp->SyncPeriod = pDCB->SyncPeriod;
				pDCBTemp->SyncOffset = pDCB->SyncOffset;
				pDCBTemp->SyncMode = pDCB->SyncMode;
			}
			pDCBTemp = pDCBTemp->pNextDCB;
		}
	}
	return;
}