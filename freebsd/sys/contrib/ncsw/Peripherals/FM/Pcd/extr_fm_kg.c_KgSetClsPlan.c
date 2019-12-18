#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_9__ {int baseEntry; int numOfClsPlanEntries; int /*<<< orphan*/ * vectors; } ;
typedef  TYPE_2__ t_FmPcdKgInterModuleClsPlanSet ;
struct TYPE_10__ {TYPE_6__* p_FmPcdKg; int /*<<< orphan*/  h_Fm; } ;
typedef  TYPE_3__ t_FmPcd ;
struct fman_kg_cp_regs {int /*<<< orphan*/ * kgcpe; } ;
struct TYPE_11__ {TYPE_1__* p_IndirectAccessRegs; } ;
struct TYPE_8__ {struct fman_kg_cp_regs clsPlanRegs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int /*<<< orphan*/ ) ; 
 int CLS_PLAN_NUM_PER_GRP ; 
 int /*<<< orphan*/  E_INVALID_STATE ; 
 scalar_t__ E_OK ; 
 scalar_t__ FM_PCD_MAX_NUM_OF_CLS_PLANS ; 
 int /*<<< orphan*/  FmIsMaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FmPcdKgBuildWriteClsPlanBlockActionReg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IN_RANGE (int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  KgHwLock (TYPE_6__*) ; 
 int /*<<< orphan*/  KgHwUnlock (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WRITE_UINT32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ WriteKgarWait (TYPE_3__*,int /*<<< orphan*/ ) ; 

void KgSetClsPlan(t_Handle h_FmPcd, t_FmPcdKgInterModuleClsPlanSet *p_Set)
{
    t_FmPcd                 *p_FmPcd = (t_FmPcd *)h_FmPcd;
    struct fman_kg_cp_regs  *p_FmPcdKgPortRegs;
    uint32_t                tmpKgarReg = 0, intFlags;
    uint16_t                i, j;

    /* This routine is protected by the calling routine ! */
    ASSERT_COND(FmIsMaster(p_FmPcd->h_Fm));
    p_FmPcdKgPortRegs = &p_FmPcd->p_FmPcdKg->p_IndirectAccessRegs->clsPlanRegs;

    intFlags = KgHwLock(p_FmPcd->p_FmPcdKg);
    for (i=p_Set->baseEntry;i<p_Set->baseEntry+p_Set->numOfClsPlanEntries;i+=8)
    {
        tmpKgarReg = FmPcdKgBuildWriteClsPlanBlockActionReg((uint8_t)(i / CLS_PLAN_NUM_PER_GRP));

        for (j = i; j < i+8; j++)
        {
            ASSERT_COND(IN_RANGE(0, (j - p_Set->baseEntry), FM_PCD_MAX_NUM_OF_CLS_PLANS-1));
            WRITE_UINT32(p_FmPcdKgPortRegs->kgcpe[j % CLS_PLAN_NUM_PER_GRP],p_Set->vectors[j - p_Set->baseEntry]);
        }

        if (WriteKgarWait(p_FmPcd, tmpKgarReg) != E_OK)
        {
            REPORT_ERROR(MAJOR, E_INVALID_STATE, ("WriteKgarWait FAILED"));
            KgHwUnlock(p_FmPcd->p_FmPcdKg, intFlags);
            return;
        }
    }
    KgHwUnlock(p_FmPcd->p_FmPcdKg, intFlags);
}