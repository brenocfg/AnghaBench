#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ t_Handle ;
struct TYPE_8__ {scalar_t__ guestId; scalar_t__ h_ShadowSpinlock; scalar_t__ h_Spinlock; int /*<<< orphan*/  h_Fm; int /*<<< orphan*/  fmPcdModuleName; int /*<<< orphan*/ * h_Hc; struct TYPE_8__* p_FmPcdPrs; struct TYPE_8__* p_FmPcdPlcr; struct TYPE_8__* p_FmPcdKg; struct TYPE_8__* p_FmPcdDriverParam; scalar_t__ enabled; scalar_t__ capwapFrameIdAddr; int /*<<< orphan*/  h_FmMuram; scalar_t__ ipv6FrameIdAddr; } ;
typedef  TYPE_1__ t_FmPcd ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  FM_MURAM_FreeMem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FM_PCD_Disable (TYPE_1__*) ; 
 int /*<<< orphan*/  FmHcFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FmUnregisterPcd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KgFree (TYPE_1__*) ; 
 int /*<<< orphan*/  MINOR ; 
 scalar_t__ NCSW_MASTER_ID ; 
 int /*<<< orphan*/  NO_MSG ; 
 int /*<<< orphan*/  PlcrFree (TYPE_1__*) ; 
 int /*<<< orphan*/  PrsFree (TYPE_1__*) ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseFreeLocksLst (TYPE_1__*) ; 
 int /*<<< orphan*/  UINT_TO_PTR (scalar_t__) ; 
 int /*<<< orphan*/  XX_Free (TYPE_1__*) ; 
 int /*<<< orphan*/  XX_FreeSpinlock (scalar_t__) ; 
 int /*<<< orphan*/  XX_IpcUnregisterMsgHandler (int /*<<< orphan*/ ) ; 

t_Error FM_PCD_Free(t_Handle h_FmPcd)
{
    t_FmPcd                             *p_FmPcd =(t_FmPcd *)h_FmPcd;
    t_Error                             err = E_OK;

    if (p_FmPcd->ipv6FrameIdAddr)
        FM_MURAM_FreeMem(p_FmPcd->h_FmMuram, UINT_TO_PTR(p_FmPcd->ipv6FrameIdAddr));

    if (p_FmPcd->capwapFrameIdAddr)
        FM_MURAM_FreeMem(p_FmPcd->h_FmMuram, UINT_TO_PTR(p_FmPcd->capwapFrameIdAddr));

    if (p_FmPcd->enabled)
        FM_PCD_Disable(p_FmPcd);

    if (p_FmPcd->p_FmPcdDriverParam)
    {
        XX_Free(p_FmPcd->p_FmPcdDriverParam);
        p_FmPcd->p_FmPcdDriverParam = NULL;
    }

    if (p_FmPcd->p_FmPcdKg)
    {
        if ((err = KgFree(p_FmPcd)) != E_OK)
            RETURN_ERROR(MINOR, err, NO_MSG);
        XX_Free(p_FmPcd->p_FmPcdKg);
        p_FmPcd->p_FmPcdKg = NULL;
    }

    if (p_FmPcd->p_FmPcdPlcr)
    {
        PlcrFree(p_FmPcd);
        XX_Free(p_FmPcd->p_FmPcdPlcr);
        p_FmPcd->p_FmPcdPlcr = NULL;
    }

    if (p_FmPcd->p_FmPcdPrs)
    {
        if (p_FmPcd->guestId == NCSW_MASTER_ID)
            PrsFree(p_FmPcd);
        XX_Free(p_FmPcd->p_FmPcdPrs);
        p_FmPcd->p_FmPcdPrs = NULL;
    }

    if (p_FmPcd->h_Hc)
    {
        FmHcFree(p_FmPcd->h_Hc);
        p_FmPcd->h_Hc = NULL;
    }

    XX_IpcUnregisterMsgHandler(p_FmPcd->fmPcdModuleName);

    FmUnregisterPcd(p_FmPcd->h_Fm);

    ReleaseFreeLocksLst(p_FmPcd);

    if (p_FmPcd->h_Spinlock)
        XX_FreeSpinlock(p_FmPcd->h_Spinlock);

    if (p_FmPcd->h_ShadowSpinlock)
        XX_FreeSpinlock(p_FmPcd->h_ShadowSpinlock);

    XX_Free(p_FmPcd);

    return E_OK;
}