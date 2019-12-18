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
struct TYPE_3__ {scalar_t__ guestId; int /*<<< orphan*/  h_Fm; } ;
typedef  TYPE_1__ t_FmPcd ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int /*<<< orphan*/  FmUnregisterIntr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NCSW_MASTER_ID ; 
 int /*<<< orphan*/  e_FM_INTR_TYPE_ERR ; 
 int /*<<< orphan*/  e_FM_INTR_TYPE_NORMAL ; 
 int /*<<< orphan*/  e_FM_MOD_PRS ; 

void PrsFree(t_FmPcd *p_FmPcd)
{
    ASSERT_COND(p_FmPcd->guestId == NCSW_MASTER_ID);
    FmUnregisterIntr(p_FmPcd->h_Fm, e_FM_MOD_PRS, 0, e_FM_INTR_TYPE_ERR);
    /* register even if no interrupts enabled, to allow future enablement */
    FmUnregisterIntr(p_FmPcd->h_Fm, e_FM_MOD_PRS, 0, e_FM_INTR_TYPE_NORMAL);
}