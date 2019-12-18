#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ guestId; TYPE_1__* p_FmPcdPrs; } ;
typedef  TYPE_2__ t_FmPcd ;
struct fman_prs_regs {int dummy; } ;
struct TYPE_4__ {scalar_t__ p_FmPcdPrsRegs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 scalar_t__ NCSW_MASTER_ID ; 
 int /*<<< orphan*/  fman_prs_enable (struct fman_prs_regs*) ; 

void PrsEnable(t_FmPcd *p_FmPcd)
{
    struct fman_prs_regs *PrsRegs = (struct fman_prs_regs *)p_FmPcd->p_FmPcdPrs->p_FmPcdPrsRegs;

    ASSERT_COND(p_FmPcd->guestId == NCSW_MASTER_ID);
    fman_prs_enable(PrsRegs);
}