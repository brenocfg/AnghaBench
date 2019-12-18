#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  TYPE_2__* t_Handle ;
struct TYPE_13__ {int /*<<< orphan*/  fmPcdPrsPortIdStatistics; struct fman_prs_regs* p_FmPcdPrsRegs; int /*<<< orphan*/ * p_SwPrsCode; } ;
typedef  TYPE_2__ t_FmPcdPrs ;
struct TYPE_14__ {scalar_t__ guestId; TYPE_1__* p_FmPcdDriverParam; int /*<<< orphan*/  exceptions; int /*<<< orphan*/  h_Fm; } ;
typedef  TYPE_4__ t_FmPcdParams ;
typedef  TYPE_4__ t_FmPcd ;
struct fman_prs_regs {int dummy; } ;
struct TYPE_15__ {int /*<<< orphan*/  prs_exceptions; int /*<<< orphan*/  max_prs_cyc_lim; int /*<<< orphan*/  port_id_stat; } ;
struct TYPE_12__ {TYPE_7__ dfltCfg; int /*<<< orphan*/  prsMaxParseCycleLimit; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_NO_MEMORY ; 
 uintptr_t FmGetPcdPrsBaseAddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAJOR ; 
 scalar_t__ NCSW_MASTER_ID ; 
 uintptr_t PRS_REGS_OFFSET ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ UINT_TO_PTR (uintptr_t) ; 
 int /*<<< orphan*/  UNUSED (TYPE_4__*) ; 
 scalar_t__ XX_Malloc (int) ; 
 int /*<<< orphan*/  fman_prs_defconfig (TYPE_7__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

t_Handle PrsConfig(t_FmPcd *p_FmPcd,t_FmPcdParams *p_FmPcdParams)
{
    t_FmPcdPrs  *p_FmPcdPrs;
    uintptr_t   baseAddr;

    UNUSED(p_FmPcd);
    UNUSED(p_FmPcdParams);

    p_FmPcdPrs = (t_FmPcdPrs *) XX_Malloc(sizeof(t_FmPcdPrs));
    if (!p_FmPcdPrs)
    {
        REPORT_ERROR(MAJOR, E_NO_MEMORY, ("FM Parser structure allocation FAILED"));
        return NULL;
    }
    memset(p_FmPcdPrs, 0, sizeof(t_FmPcdPrs));
    fman_prs_defconfig(&p_FmPcd->p_FmPcdDriverParam->dfltCfg);

    if (p_FmPcd->guestId == NCSW_MASTER_ID)
    {
        baseAddr = FmGetPcdPrsBaseAddr(p_FmPcdParams->h_Fm);
        p_FmPcdPrs->p_SwPrsCode  = (uint32_t *)UINT_TO_PTR(baseAddr);
        p_FmPcdPrs->p_FmPcdPrsRegs  = (struct fman_prs_regs *)UINT_TO_PTR(baseAddr + PRS_REGS_OFFSET);
    }

    p_FmPcdPrs->fmPcdPrsPortIdStatistics = p_FmPcd->p_FmPcdDriverParam->dfltCfg.port_id_stat;
    p_FmPcd->p_FmPcdDriverParam->prsMaxParseCycleLimit = p_FmPcd->p_FmPcdDriverParam->dfltCfg.max_prs_cyc_lim;
    p_FmPcd->exceptions |= p_FmPcd->p_FmPcdDriverParam->dfltCfg.prs_exceptions;

    return p_FmPcdPrs;
}