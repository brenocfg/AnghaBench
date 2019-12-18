#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* u_int8_t ;
typedef  size_t u_int16_t ;
struct TYPE_6__ {int max_id; int max_lun; int TagMaxNum; scalar_t__ ACBFlag; void* AdaptType; scalar_t__ DeviceCnt; scalar_t__ AdaptSCSILUN; int /*<<< orphan*/  AdaptSCSIID; void* AdapterUnit; int /*<<< orphan*/ * pActiveDCB; int /*<<< orphan*/ * pDCBRunRobin; int /*<<< orphan*/ * pLinkDCB; } ;
struct TYPE_5__ {int NvramChannelCfg; int NvramMaxTag; int /*<<< orphan*/  NvramScsiId; } ;
typedef  TYPE_1__* PNVRAMTYPE ;
typedef  TYPE_2__* PACB ;

/* Variables and functions */
 int NAC_SCANLUN ; 
 int /*<<< orphan*/  TRM_DPRINTF (char*,int,int) ; 
 TYPE_1__* trm_eepromBuf ; 

__attribute__((used)) static void
trm_initACB(PACB pACB, u_int8_t adaptType, u_int16_t unit)
{
	PNVRAMTYPE	pEEpromBuf;
    
	pEEpromBuf = &trm_eepromBuf[unit];
	pACB->max_id = 15;
	
	if (pEEpromBuf->NvramChannelCfg & NAC_SCANLUN)
  		pACB->max_lun = 7;
	else
		pACB->max_lun = 0;

	TRM_DPRINTF("trm: pACB->max_id= %d pACB->max_lun= %d \n",
	    pACB->max_id, pACB->max_lun);
	pACB->pLinkDCB = NULL;
	pACB->pDCBRunRobin = NULL;
	pACB->pActiveDCB = NULL;
	pACB->AdapterUnit = (u_int8_t)unit;
	pACB->AdaptSCSIID = pEEpromBuf->NvramScsiId;
	pACB->AdaptSCSILUN = 0;
	pACB->DeviceCnt = 0;
	pACB->AdaptType = adaptType; 
	pACB->TagMaxNum = 2 << pEEpromBuf->NvramMaxTag;
	pACB->ACBFlag = 0;
	return;
}