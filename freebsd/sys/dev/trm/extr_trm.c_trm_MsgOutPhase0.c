#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int16_t ;
struct TYPE_3__ {int SRBState; } ;
typedef  TYPE_1__* PSRB ;
typedef  int /*<<< orphan*/  PACB ;

/* Variables and functions */
 int /*<<< orphan*/  PH_BUS_FREE ; 
 int SRB_ABORT_SENT ; 
 int SRB_UNEXPECT_RESEL ; 

__attribute__((used)) static void
trm_MsgOutPhase0(PACB pACB, PSRB pSRB, u_int16_t *pscsi_status)
{

	if (pSRB->SRBState & (SRB_UNEXPECT_RESEL+SRB_ABORT_SENT))
		*pscsi_status = PH_BUS_FREE;
	/*.. initial phase*/
}