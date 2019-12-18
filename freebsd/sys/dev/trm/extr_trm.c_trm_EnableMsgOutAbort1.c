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
struct TYPE_4__ {int /*<<< orphan*/ * MsgOutBuf; } ;
typedef  TYPE_1__* PSRB ;
typedef  int /*<<< orphan*/  PACB ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ABORT ; 
 int /*<<< orphan*/  trm_EnableMsgOutAbort2 (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void
trm_EnableMsgOutAbort1(PACB pACB, PSRB pSRB)
{
  
	pSRB->MsgOutBuf[0] = MSG_ABORT;
	trm_EnableMsgOutAbort2(pACB, pSRB);
}