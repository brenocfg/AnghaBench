#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int uint64_t ;
typedef  TYPE_2__* t_Handle ;
struct TYPE_24__ {scalar_t__ high; scalar_t__ low; } ;
typedef  TYPE_3__ t_FmPhysAddr ;
typedef  int /*<<< orphan*/  t_FmPcdPrs ;
typedef  int /*<<< orphan*/  t_FmPcdPlcr ;
struct TYPE_25__ {int /*<<< orphan*/  h_App; int /*<<< orphan*/  f_ExceptionId; int /*<<< orphan*/  f_Exception; scalar_t__ prsSupport; scalar_t__ plcrSupport; scalar_t__ kgSupport; int /*<<< orphan*/  hc; scalar_t__ useHostCommand; int /*<<< orphan*/  h_Fm; } ;
typedef  TYPE_4__ t_FmPcdParams ;
typedef  int /*<<< orphan*/  t_FmPcdKg ;
typedef  int /*<<< orphan*/  t_FmPcdHcParams ;
struct TYPE_23__ {scalar_t__ guestId; int physicalMuramBase; void* h_ShadowSpinlock; scalar_t__ ccShadowAlign; scalar_t__ ccShadowSize; int /*<<< orphan*/ * p_CcShadow; int /*<<< orphan*/  h_App; int /*<<< orphan*/  f_FmPcdIndexedException; int /*<<< orphan*/  f_Exception; scalar_t__ numOfEnabledGuestPartitionsPcds; int /*<<< orphan*/  acquiredLocksLst; int /*<<< orphan*/  freeLocksLst; void* h_Spinlock; int /*<<< orphan*/ * p_FmPcdPrs; int /*<<< orphan*/ * p_FmPcdPlcr; int /*<<< orphan*/ * p_FmPcdKg; int /*<<< orphan*/  h_Hc; int /*<<< orphan*/  params; struct TYPE_23__* h_FmPcd; int /*<<< orphan*/  h_Fm; TYPE_1__* netEnvs; scalar_t__ h_FmMuram; struct TYPE_23__* p_FmPcdDriverParam; } ;
typedef  TYPE_2__ t_FmPcdDriverParam ;
typedef  TYPE_2__ t_FmPcd ;
typedef  TYPE_2__ t_FmHcParams ;
typedef  int /*<<< orphan*/  hcParams ;
struct TYPE_22__ {int /*<<< orphan*/  clsPlanGrpId; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_INVALID_STATE ; 
 int /*<<< orphan*/  E_NO_MEMORY ; 
 size_t FM_MAX_NUM_OF_PORTS ; 
 int /*<<< orphan*/  FM_PCD_Free (TYPE_2__*) ; 
 scalar_t__ FmGetGuestId (int /*<<< orphan*/ ) ; 
 scalar_t__ FmGetMuramHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FmGetPhysicalMuramBase (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  FmHcConfigAndInit (TYPE_2__*) ; 
 int /*<<< orphan*/  ILLEGAL_CLS_PLAN ; 
 int /*<<< orphan*/  INIT_LIST (int /*<<< orphan*/ *) ; 
 scalar_t__ KgConfig (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  MAJOR ; 
 scalar_t__ NCSW_MASTER_ID ; 
 scalar_t__ PlcrConfig (TYPE_2__*,TYPE_4__*) ; 
 scalar_t__ PrsConfig (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_VALUE (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XX_Free (TYPE_2__*) ; 
 void* XX_InitSpinlock () ; 
 scalar_t__ XX_Malloc (int) ; 
 int /*<<< orphan*/  memcpy (size_t*,size_t*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

t_Handle FM_PCD_Config(t_FmPcdParams *p_FmPcdParams)
{
    t_FmPcd             *p_FmPcd = NULL;
    t_FmPhysAddr        physicalMuramBase;
    uint8_t             i;

    SANITY_CHECK_RETURN_VALUE(p_FmPcdParams, E_INVALID_HANDLE,NULL);

    p_FmPcd = (t_FmPcd *) XX_Malloc(sizeof(t_FmPcd));
    if (!p_FmPcd)
    {
        REPORT_ERROR(MAJOR, E_NO_MEMORY, ("FM PCD"));
        return NULL;
    }
    memset(p_FmPcd, 0, sizeof(t_FmPcd));

    p_FmPcd->p_FmPcdDriverParam = (t_FmPcdDriverParam *) XX_Malloc(sizeof(t_FmPcdDriverParam));
    if (!p_FmPcd->p_FmPcdDriverParam)
    {
        XX_Free(p_FmPcd);
        REPORT_ERROR(MAJOR, E_NO_MEMORY, ("FM PCD Driver Param"));
        return NULL;
    }
    memset(p_FmPcd->p_FmPcdDriverParam, 0, sizeof(t_FmPcdDriverParam));

    p_FmPcd->h_Fm = p_FmPcdParams->h_Fm;
    p_FmPcd->guestId = FmGetGuestId(p_FmPcd->h_Fm);
    p_FmPcd->h_FmMuram = FmGetMuramHandle(p_FmPcd->h_Fm);
    if (p_FmPcd->h_FmMuram)
    {
        FmGetPhysicalMuramBase(p_FmPcdParams->h_Fm, &physicalMuramBase);
        p_FmPcd->physicalMuramBase = (uint64_t)((uint64_t)(&physicalMuramBase)->low | ((uint64_t)(&physicalMuramBase)->high << 32));
    }

    for (i = 0; i<FM_MAX_NUM_OF_PORTS; i++)
        p_FmPcd->netEnvs[i].clsPlanGrpId = ILLEGAL_CLS_PLAN;

    if (p_FmPcdParams->useHostCommand)
    {
        t_FmHcParams    hcParams;

        memset(&hcParams, 0, sizeof(hcParams));
        hcParams.h_Fm = p_FmPcd->h_Fm;
        hcParams.h_FmPcd = (t_Handle)p_FmPcd;
        memcpy((uint8_t*)&hcParams.params, (uint8_t*)&p_FmPcdParams->hc, sizeof(t_FmPcdHcParams));
        p_FmPcd->h_Hc = FmHcConfigAndInit(&hcParams);
        if (!p_FmPcd->h_Hc)
        {
            REPORT_ERROR(MAJOR, E_NO_MEMORY, ("FM PCD HC"));
            FM_PCD_Free(p_FmPcd);
            return NULL;
        }
    }
    else if (p_FmPcd->guestId != NCSW_MASTER_ID)
        REPORT_ERROR(MAJOR, E_INVALID_STATE, ("No Host Command defined for a guest partition."));

    if (p_FmPcdParams->kgSupport)
    {
        p_FmPcd->p_FmPcdKg = (t_FmPcdKg *)KgConfig(p_FmPcd, p_FmPcdParams);
        if (!p_FmPcd->p_FmPcdKg)
        {
            REPORT_ERROR(MAJOR, E_NO_MEMORY, ("FM PCD Keygen"));
            FM_PCD_Free(p_FmPcd);
            return NULL;
        }
    }

    if (p_FmPcdParams->plcrSupport)
    {
        p_FmPcd->p_FmPcdPlcr = (t_FmPcdPlcr *)PlcrConfig(p_FmPcd, p_FmPcdParams);
        if (!p_FmPcd->p_FmPcdPlcr)
        {
            REPORT_ERROR(MAJOR, E_NO_MEMORY, ("FM PCD Policer"));
            FM_PCD_Free(p_FmPcd);
            return NULL;
        }
    }

    if (p_FmPcdParams->prsSupport)
    {
        p_FmPcd->p_FmPcdPrs = (t_FmPcdPrs *)PrsConfig(p_FmPcd, p_FmPcdParams);
        if (!p_FmPcd->p_FmPcdPrs)
        {
            REPORT_ERROR(MAJOR, E_NO_MEMORY, ("FM PCD Parser"));
            FM_PCD_Free(p_FmPcd);
            return NULL;
        }
    }

    p_FmPcd->h_Spinlock = XX_InitSpinlock();
    if (!p_FmPcd->h_Spinlock)
    {
        REPORT_ERROR(MAJOR, E_NO_MEMORY, ("FM PCD spinlock"));
        FM_PCD_Free(p_FmPcd);
        return NULL;
    }
    INIT_LIST(&p_FmPcd->freeLocksLst);
    INIT_LIST(&p_FmPcd->acquiredLocksLst);

    p_FmPcd->numOfEnabledGuestPartitionsPcds = 0;

    p_FmPcd->f_Exception                = p_FmPcdParams->f_Exception;
    p_FmPcd->f_FmPcdIndexedException    = p_FmPcdParams->f_ExceptionId;
    p_FmPcd->h_App                      = p_FmPcdParams->h_App;

    p_FmPcd->p_CcShadow                 = NULL;
    p_FmPcd->ccShadowSize               = 0;
    p_FmPcd->ccShadowAlign              = 0;

    p_FmPcd->h_ShadowSpinlock = XX_InitSpinlock();
    if (!p_FmPcd->h_ShadowSpinlock)
    {
        REPORT_ERROR(MAJOR, E_NO_MEMORY, ("FM PCD shadow spinlock"));
        FM_PCD_Free(p_FmPcd);
        return NULL;
    }

    return p_FmPcd;
}