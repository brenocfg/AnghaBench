#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_4__ {scalar_t__ guestId; TYPE_1__* fmanCtrlIntr; } ;
typedef  TYPE_2__ t_Fm ;
struct TYPE_3__ {int /*<<< orphan*/ * h_SrcHandle; int /*<<< orphan*/  f_Isr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int /*<<< orphan*/  E_NOT_SUPPORTED ; 
 size_t FM_NUM_OF_FMAN_CTRL_EVENT_REGS ; 
 int /*<<< orphan*/  MAJOR ; 
 scalar_t__ NCSW_MASTER_ID ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  UnimplementedFmanCtrlIsr ; 

void  FmUnregisterFmanCtrlIntr(t_Handle h_Fm, uint8_t eventRegId)
{
    t_Fm       *p_Fm = (t_Fm*)h_Fm;

    ASSERT_COND(eventRegId<FM_NUM_OF_FMAN_CTRL_EVENT_REGS);

    if (p_Fm->guestId != NCSW_MASTER_ID)
    {
        REPORT_ERROR(MAJOR, E_NOT_SUPPORTED, ("FM in guest-mode"));
        return;
    }

    p_Fm->fmanCtrlIntr[eventRegId].f_Isr = UnimplementedFmanCtrlIsr;
    p_Fm->fmanCtrlIntr[eventRegId].h_SrcHandle = NULL;
}