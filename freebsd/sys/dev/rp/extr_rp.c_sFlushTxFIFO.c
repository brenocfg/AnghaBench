#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int* TxControl; int /*<<< orphan*/  TxFIFOPtrs; } ;
typedef  TYPE_1__ CHANNEL_T ;
typedef  int Byte_t ;

/* Variables and functions */
 int FALSE ; 
 int RESTXFCNT ; 
 int TRUE ; 
 int TX_ENABLE ; 
 int /*<<< orphan*/  _CMD_REG ; 
 int /*<<< orphan*/  _INDX_ADDR ; 
 int /*<<< orphan*/  _INDX_DATA ; 
 int /*<<< orphan*/  _INT_CHAN ; 
 int /*<<< orphan*/  rp_readch1 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rp_writech1 (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rp_writech2 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sDisTransmit (TYPE_1__*) ; 
 int /*<<< orphan*/  sEnTransmit (TYPE_1__*) ; 
 scalar_t__ sGetChanNum (TYPE_1__*) ; 
 scalar_t__ sGetTxCnt (TYPE_1__*) ; 
 int /*<<< orphan*/  sStartRxProcessor (TYPE_1__*) ; 
 int /*<<< orphan*/  sStopRxProcessor (TYPE_1__*) ; 

void sFlushTxFIFO(CHANNEL_T *ChP)
{
   int i;
   Byte_t Ch;			/* channel number within AIOP */
   int TxEnabled;		       /* TRUE if transmitter enabled */

   if(sGetTxCnt(ChP) == 0)	       /* Tx FIFO empty */
      return;			       /* don't need to flush */

   TxEnabled = FALSE;
   if(ChP->TxControl[3] & TX_ENABLE)
   {
      TxEnabled = TRUE;
      sDisTransmit(ChP);	       /* disable transmitter */
   }
   sStopRxProcessor(ChP);	       /* stop Rx processor */
   for(i = 0; i < 4000/200; i++)	 /* delay 4 uS to allow proc to stop */
      rp_readch1(ChP,_INT_CHAN);	/* depends on bus i/o timing */
   Ch = (Byte_t)sGetChanNum(ChP);
   rp_writech1(ChP,_CMD_REG,Ch | RESTXFCNT);     /* apply reset Tx FIFO count */
   rp_writech1(ChP,_CMD_REG,Ch);		       /* remove reset Tx FIFO count */
   rp_writech2(ChP,_INDX_ADDR,ChP->TxFIFOPtrs); /* clear Tx in/out ptrs */
   rp_writech2(ChP,_INDX_DATA,0);
   if(TxEnabled)
      sEnTransmit(ChP); 	       /* enable transmitter */
   sStartRxProcessor(ChP);	       /* restart Rx processor */
}