#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  TxPrioCnt; int /*<<< orphan*/  TxPrioBuf; } ;
typedef  TYPE_1__ CHANNEL_T ;
typedef  int Byte_t ;

/* Variables and functions */
 int PRI_PEND ; 
 int /*<<< orphan*/  _INDX_ADDR ; 
 int /*<<< orphan*/  _INDX_DATA ; 
 int /*<<< orphan*/  le16enc (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32dec (int*) ; 
 int rp_readch1 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rp_writech2 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rp_writech4 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sGetTxCnt (TYPE_1__*) ; 
 int /*<<< orphan*/  sGetTxRxDataIO (TYPE_1__*) ; 
 int /*<<< orphan*/  sWriteTxByte (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int sWriteTxPrioByte(CHANNEL_T *ChP, Byte_t Data)
{
   Byte_t DWBuf[4];		/* buffer for double word writes */

   if(sGetTxCnt(ChP) > 1)	       /* write it to Tx priority buffer */
   {
      rp_writech2(ChP,_INDX_ADDR,ChP->TxPrioCnt); /* get priority buffer status */
      if(rp_readch1(ChP,_INDX_DATA) & PRI_PEND) /* priority buffer busy */
	 return(0);		       /* nothing sent */

      le16enc(DWBuf,ChP->TxPrioBuf);   /* data byte address */

      DWBuf[2] = Data;		       /* data byte value */
      DWBuf[3] = 0;		       /* priority buffer pointer */
      rp_writech4(ChP,_INDX_ADDR,le32dec(DWBuf)); /* write it out */

      le16enc(DWBuf,ChP->TxPrioCnt);   /* Tx priority count address */

      DWBuf[2] = PRI_PEND + 1;	       /* indicate 1 byte pending */
      DWBuf[3] = 0;		       /* priority buffer pointer */
      rp_writech4(ChP,_INDX_ADDR,le32dec(DWBuf)); /* write it out */
   }
   else 			       /* write it to Tx FIFO */
   {
      sWriteTxByte(ChP,sGetTxRxDataIO(ChP),Data);
   }
   return(1);			       /* 1 byte sent */
}