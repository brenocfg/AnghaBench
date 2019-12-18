#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_FmPcdKgIndirectAccessRegs ;
typedef  TYPE_1__* t_Handle ;
struct TYPE_11__ {scalar_t__ numOfSchemes; int /*<<< orphan*/  h_Fm; } ;
typedef  TYPE_2__ t_FmPcdParams ;
struct TYPE_10__ {scalar_t__ numOfSchemes; int /*<<< orphan*/  emptyClsPlanGrpId; struct fman_kg_regs* p_FmPcdKgRegs; int /*<<< orphan*/ * p_IndirectAccessRegs; } ;
typedef  TYPE_1__ t_FmPcdKg ;
struct TYPE_12__ {scalar_t__ guestId; int /*<<< orphan*/  exceptions; int /*<<< orphan*/  h_Fm; } ;
typedef  TYPE_4__ t_FmPcd ;
struct fman_kg_regs {int /*<<< orphan*/ * fmkg_indirect; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DEFAULT_fmPcdKgErrorExceptions ; 
 int /*<<< orphan*/  E_INVALID_VALUE ; 
 int /*<<< orphan*/  E_NO_MEMORY ; 
 scalar_t__ FM_PCD_KG_NUM_OF_SCHEMES ; 
 int /*<<< orphan*/  FmGetPcdKgBaseAddr (int /*<<< orphan*/ ) ; 
 scalar_t__ FmIsMaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILLEGAL_CLS_PLAN ; 
 int /*<<< orphan*/  MAJOR ; 
 scalar_t__ NCSW_MASTER_ID ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ UINT_TO_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNUSED (TYPE_4__*) ; 
 int /*<<< orphan*/  WARNING ; 
 scalar_t__ XX_Malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

t_Handle KgConfig( t_FmPcd *p_FmPcd, t_FmPcdParams *p_FmPcdParams)
{
    t_FmPcdKg   *p_FmPcdKg;

    UNUSED(p_FmPcd);

    if (p_FmPcdParams->numOfSchemes > FM_PCD_KG_NUM_OF_SCHEMES)
    {
        REPORT_ERROR(MAJOR, E_INVALID_VALUE,
                     ("numOfSchemes should not exceed %d", FM_PCD_KG_NUM_OF_SCHEMES));
        return NULL;
    }

    p_FmPcdKg = (t_FmPcdKg *)XX_Malloc(sizeof(t_FmPcdKg));
    if (!p_FmPcdKg)
    {
        REPORT_ERROR(MAJOR, E_NO_MEMORY, ("FM Keygen allocation FAILED"));
        return NULL;
    }
    memset(p_FmPcdKg, 0, sizeof(t_FmPcdKg));


    if (FmIsMaster(p_FmPcd->h_Fm))
    {
        p_FmPcdKg->p_FmPcdKgRegs  = (struct fman_kg_regs *)UINT_TO_PTR(FmGetPcdKgBaseAddr(p_FmPcdParams->h_Fm));
        p_FmPcd->exceptions |= DEFAULT_fmPcdKgErrorExceptions;
        p_FmPcdKg->p_IndirectAccessRegs = (u_FmPcdKgIndirectAccessRegs *)&p_FmPcdKg->p_FmPcdKgRegs->fmkg_indirect[0];
    }

    p_FmPcdKg->numOfSchemes = p_FmPcdParams->numOfSchemes;
    if ((p_FmPcd->guestId == NCSW_MASTER_ID) && !p_FmPcdKg->numOfSchemes)
    {
        p_FmPcdKg->numOfSchemes = FM_PCD_KG_NUM_OF_SCHEMES;
        DBG(WARNING, ("numOfSchemes was defined 0 by user, re-defined by driver to FM_PCD_KG_NUM_OF_SCHEMES"));
    }

    p_FmPcdKg->emptyClsPlanGrpId = ILLEGAL_CLS_PLAN;

    return p_FmPcdKg;
}