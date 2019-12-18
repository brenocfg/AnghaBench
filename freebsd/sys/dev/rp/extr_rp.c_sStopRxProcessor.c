#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* R; } ;
typedef  TYPE_1__ CHANNEL_T ;
typedef  int Byte_t ;

/* Variables and functions */
 int /*<<< orphan*/  _INDX_ADDR ; 
 int /*<<< orphan*/  le32dec (int*) ; 
 int /*<<< orphan*/  rp_writech4 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sStopRxProcessor(CHANNEL_T *ChP)
{
   Byte_t R[4];

   R[0] = ChP->R[0];
   R[1] = ChP->R[1];
   R[2] = 0x0a;
   R[3] = ChP->R[3];
   rp_writech4(ChP,_INDX_ADDR,le32dec(R));
}