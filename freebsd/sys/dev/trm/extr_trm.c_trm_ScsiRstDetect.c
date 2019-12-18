#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct TYPE_6__ {int ACBFlag; int /*<<< orphan*/ * pActiveDCB; } ;
typedef  TYPE_1__* PACB ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  DO_CLRFIFO ; 
 int RESET_DETECT ; 
 int RESET_DEV ; 
 int RESET_DONE ; 
 int /*<<< orphan*/  STOPDMAXFER ; 
 int /*<<< orphan*/  TRMREG_DMA_CONTROL ; 
 int /*<<< orphan*/  TRMREG_SCSI_CONTROL ; 
 int /*<<< orphan*/  TRM_DPRINTF (char*) ; 
 int splcam () ; 
 int /*<<< orphan*/  splx (int) ; 
 int /*<<< orphan*/  trm_DoWaitingSRB (TYPE_1__*) ; 
 int /*<<< orphan*/  trm_RecoverSRB (TYPE_1__*) ; 
 int /*<<< orphan*/  trm_ResetDevParam (TYPE_1__*) ; 
 int /*<<< orphan*/  trm_reg_write16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trm_reg_write8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void 
trm_ScsiRstDetect(PACB pACB)
{
	int	intflag;
	u_long	wlval;

	TRM_DPRINTF("trm_ScsiRstDetect \n");
	wlval = 1000;
	while (--wlval)
		DELAY(1000);
	intflag = splcam();
    	trm_reg_write8(STOPDMAXFER,TRMREG_DMA_CONTROL);

	trm_reg_write16(DO_CLRFIFO,TRMREG_SCSI_CONTROL);

	if (pACB->ACBFlag & RESET_DEV)
		pACB->ACBFlag |= RESET_DONE;
	else {
		pACB->ACBFlag |= RESET_DETECT;
		trm_ResetDevParam(pACB);
		/*	trm_DoingSRB_Done(pACB); ???? */
		trm_RecoverSRB(pACB);
		pACB->pActiveDCB = NULL;
		pACB->ACBFlag = 0;
		trm_DoWaitingSRB(pACB);
	}
	splx(intflag);
    	return;
}