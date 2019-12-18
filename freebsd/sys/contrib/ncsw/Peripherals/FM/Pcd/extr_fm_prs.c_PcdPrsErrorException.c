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
typedef  int uint32_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_4__ {scalar_t__ guestId; int /*<<< orphan*/  h_App; int /*<<< orphan*/  (* f_Exception ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_1__* p_FmPcdPrs; } ;
typedef  TYPE_2__ t_FmPcd ;
struct fman_prs_regs {int dummy; } ;
struct TYPE_3__ {scalar_t__ p_FmPcdPrsRegs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*) ; 
 int FM_PCD_PRS_DOUBLE_ECC ; 
 scalar_t__ NCSW_MASTER_ID ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  e_FM_PCD_PRS_EXCEPTION_DOUBLE_ECC ; 
 int /*<<< orphan*/  fman_prs_ack_err_event (struct fman_prs_regs*,int) ; 
 int fman_prs_get_err_ev_mask (struct fman_prs_regs*) ; 
 int fman_prs_get_err_event (struct fman_prs_regs*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void PcdPrsErrorException(t_Handle h_FmPcd)
{
    t_FmPcd                 *p_FmPcd = (t_FmPcd *)h_FmPcd;
    uint32_t                event, ev_mask;
    struct fman_prs_regs     *PrsRegs = (struct fman_prs_regs *)p_FmPcd->p_FmPcdPrs->p_FmPcdPrsRegs;

    ASSERT_COND(p_FmPcd->guestId == NCSW_MASTER_ID);
    ev_mask = fman_prs_get_err_ev_mask(PrsRegs);

    event = fman_prs_get_err_event(PrsRegs, ev_mask);

    fman_prs_ack_err_event(PrsRegs, event);

    DBG(TRACE, ("parser error - 0x%08x\n",event));

    if(event & FM_PCD_PRS_DOUBLE_ECC)
        p_FmPcd->f_Exception(p_FmPcd->h_App,e_FM_PCD_PRS_EXCEPTION_DOUBLE_ECC);
}