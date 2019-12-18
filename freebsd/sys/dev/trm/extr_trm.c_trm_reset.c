#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int16_t ;
struct TYPE_7__ {int /*<<< orphan*/ * ppath; scalar_t__ ACBFlag; int /*<<< orphan*/ * pActiveDCB; } ;
typedef  TYPE_1__* PACB ;

/* Variables and functions */
 int /*<<< orphan*/  AC_BUS_RESET ; 
 int CLRXFIFO ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  DO_CLRFIFO ; 
 int EN_SCSIINTR ; 
 int /*<<< orphan*/  TRMREG_DMA_CONTROL ; 
 int /*<<< orphan*/  TRMREG_DMA_INTEN ; 
 int /*<<< orphan*/  TRMREG_SCSI_CONTROL ; 
 int /*<<< orphan*/  TRMREG_SCSI_INTEN ; 
 int /*<<< orphan*/  TRM_DPRINTF (char*) ; 
 int splcam () ; 
 int /*<<< orphan*/  splx (int) ; 
 int /*<<< orphan*/  trm_DoWaitingSRB (TYPE_1__*) ; 
 int /*<<< orphan*/  trm_DoingSRB_Done (TYPE_1__*) ; 
 int /*<<< orphan*/  trm_ResetDevParam (TYPE_1__*) ; 
 int /*<<< orphan*/  trm_ResetSCSIBus (TYPE_1__*) ; 
 int /*<<< orphan*/  trm_reg_write16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trm_reg_write8 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_async (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
trm_reset(PACB pACB)
{
	int		intflag;
	u_int16_t	i;

    	TRM_DPRINTF("trm: RESET");
    	intflag = splcam();
	trm_reg_write8(0x00, TRMREG_DMA_INTEN);
	trm_reg_write8(0x00, TRMREG_SCSI_INTEN);

	trm_ResetSCSIBus(pACB);
	for (i = 0; i < 500; i++)
		DELAY(1000);
    	trm_reg_write8(0x7F, TRMREG_SCSI_INTEN); 
	/* Enable DMA interrupt	*/
	trm_reg_write8(EN_SCSIINTR, TRMREG_DMA_INTEN);
	/* Clear DMA FIFO */
	trm_reg_write8(CLRXFIFO, TRMREG_DMA_CONTROL);
	/* Clear SCSI FIFO */
	trm_reg_write16(DO_CLRFIFO,TRMREG_SCSI_CONTROL);
	trm_ResetDevParam(pACB);
	trm_DoingSRB_Done(pACB);
	pACB->pActiveDCB = NULL;
	pACB->ACBFlag = 0;/* RESET_DETECT, RESET_DONE ,RESET_DEV */
	trm_DoWaitingSRB(pACB);
	/* Tell the XPT layer that a bus reset occurred    */
	if (pACB->ppath != NULL)
		xpt_async(AC_BUS_RESET, pACB->ppath, NULL);
	splx(intflag);
    	return;
}