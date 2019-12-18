#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint16_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_6__ {TYPE_2__* p_FmPcdPlcr; } ;
typedef  TYPE_3__ t_FmPcd ;
struct TYPE_5__ {TYPE_1__* portsMapping; } ;
struct TYPE_4__ {scalar_t__ h_FmPort; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (scalar_t__) ; 
 int /*<<< orphan*/  HW_PORT_ID_TO_SW_PORT_INDX (size_t,int /*<<< orphan*/ ) ; 

void   FmPcdPortRegister(t_Handle h_FmPcd, t_Handle h_FmPort, uint8_t hardwarePortId)
{
    t_FmPcd         *p_FmPcd = (t_FmPcd*)h_FmPcd;
    uint16_t        swPortIndex = 0;

    ASSERT_COND(h_FmPcd);
    HW_PORT_ID_TO_SW_PORT_INDX(swPortIndex, hardwarePortId);
    p_FmPcd->p_FmPcdPlcr->portsMapping[swPortIndex].h_FmPort = h_FmPort;
}