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
typedef  int Word_t ;
struct TYPE_6__ {int* RxControl; int* TxControl; size_t ChanNum; } ;
typedef  TYPE_1__ CHANNEL_T ;
typedef  int Byte_t ;

/* Variables and functions */
 int CHANINT_EN ; 
 int MCINT_EN ; 
 int RXINT_EN ; 
 int SRCINT_EN ; 
 int TXINT_EN ; 
 int /*<<< orphan*/  _INDX_ADDR ; 
 int /*<<< orphan*/  _INT_MASK ; 
 int /*<<< orphan*/  le32dec (int*) ; 
 int rp_readch1 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int* rp_sBitMapSetTbl ; 
 int /*<<< orphan*/  rp_writech1 (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rp_writech4 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sEnInterrupts(CHANNEL_T *ChP,Word_t Flags)
{
   Byte_t Mask; 		/* Interrupt Mask Register */

   ChP->RxControl[2] |=
      ((Byte_t)Flags & (RXINT_EN | SRCINT_EN | MCINT_EN));

   rp_writech4(ChP,_INDX_ADDR,le32dec(ChP->RxControl));

   ChP->TxControl[2] |= ((Byte_t)Flags & TXINT_EN);

   rp_writech4(ChP,_INDX_ADDR,le32dec(ChP->TxControl));

   if(Flags & CHANINT_EN)
   {
      Mask = rp_readch1(ChP,_INT_MASK) | rp_sBitMapSetTbl[ChP->ChanNum];
      rp_writech1(ChP,_INT_MASK,Mask);
   }
}