#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int* R; scalar_t__ RxFIFOPtrs; } ;
typedef  TYPE_1__ CHANNEL_T ;
typedef  int Byte_t ;

/* Variables and functions */
 int FALSE ; 
 int RESRXFCNT ; 
 int TRUE ; 
 int /*<<< orphan*/  _CMD_REG ; 
 int /*<<< orphan*/  _INDX_ADDR ; 
 int /*<<< orphan*/  _INDX_DATA ; 
 int /*<<< orphan*/  _INT_CHAN ; 
 int /*<<< orphan*/  rp_readch1 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rp_writech1 (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rp_writech2 (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sDisRxFIFO (TYPE_1__*) ; 
 int /*<<< orphan*/  sEnRxFIFO (TYPE_1__*) ; 
 scalar_t__ sGetChanNum (TYPE_1__*) ; 
 int /*<<< orphan*/  sGetChanStatus (TYPE_1__*) ; 
 scalar_t__ sGetRxCnt (TYPE_1__*) ; 

void sFlushRxFIFO(CHANNEL_T *ChP)
{
   int i;
   Byte_t Ch;			/* channel number within AIOP */
   int RxFIFOEnabled;		       /* TRUE if Rx FIFO enabled */

   if(sGetRxCnt(ChP) == 0)	       /* Rx FIFO empty */
      return;			       /* don't need to flush */

   RxFIFOEnabled = FALSE;
   if(ChP->R[0x32] == 0x08) /* Rx FIFO is enabled */
   {
      RxFIFOEnabled = TRUE;
      sDisRxFIFO(ChP);		       /* disable it */
      for(i=0; i < 2000/200; i++)	/* delay 2 uS to allow proc to disable FIFO*/
	 rp_readch1(ChP,_INT_CHAN);		/* depends on bus i/o timing */
   }
   sGetChanStatus(ChP); 	 /* clear any pending Rx errors in chan stat */
   Ch = (Byte_t)sGetChanNum(ChP);
   rp_writech1(ChP,_CMD_REG,Ch | RESRXFCNT);     /* apply reset Rx FIFO count */
   rp_writech1(ChP,_CMD_REG,Ch);		       /* remove reset Rx FIFO count */
   rp_writech2(ChP,_INDX_ADDR,ChP->RxFIFOPtrs); /* clear Rx out ptr */
   rp_writech2(ChP,_INDX_DATA,0);
   rp_writech2(ChP,_INDX_ADDR,ChP->RxFIFOPtrs + 2); /* clear Rx in ptr */
   rp_writech2(ChP,_INDX_DATA,0);
   if(RxFIFOEnabled)
      sEnRxFIFO(ChP);		       /* enable Rx FIFO */
}