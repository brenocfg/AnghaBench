#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t_Handle ;
struct TYPE_12__ {int /*<<< orphan*/ * h_Ipv4Ad; int /*<<< orphan*/ * h_Ipv6Ad; int /*<<< orphan*/ * p_Ipv6ReassTbl; int /*<<< orphan*/ * p_Ipv4ReassTbl; scalar_t__ ipv6AutoLearnSetLockTblAddr; scalar_t__ ipv4AutoLearnSetLockTblAddr; scalar_t__ ipv6AutoLearnHashTblAddr; scalar_t__ ipv4AutoLearnHashTblAddr; } ;
struct TYPE_13__ {scalar_t__ hdr; TYPE_3__ ip; scalar_t__ internalBufferPoolAddr; scalar_t__ internalBufferPoolManagementIndexAddr; scalar_t__ reassFrmDescrIndxPoolTblAddr; int /*<<< orphan*/ * p_ReassCommonTbl; scalar_t__ reassFrmDescrPoolTblAddr; scalar_t__ timeOutTblAddr; } ;
struct TYPE_11__ {int /*<<< orphan*/ * p_Frag; int /*<<< orphan*/  scratchBpid; } ;
struct TYPE_10__ {int /*<<< orphan*/ * p_TimeOutTbl; int /*<<< orphan*/ * p_ReassmFrmDescrIndxPoolTbl; int /*<<< orphan*/ * p_ReassmFrmDescrPoolTbl; int /*<<< orphan*/ * p_AutoLearnHashTbl; } ;
struct TYPE_14__ {int /*<<< orphan*/ * p_StatsTbl; TYPE_4__ reassmParams; scalar_t__ reassm; TYPE_2__ fragParams; scalar_t__ frag; int /*<<< orphan*/ * h_Frag; TYPE_1__ capwapFragParams; int /*<<< orphan*/ * p_Template; int /*<<< orphan*/ * h_Ad; scalar_t__ muramAllocate; } ;
typedef  TYPE_5__ t_FmPcdManip ;
struct TYPE_15__ {int /*<<< orphan*/  h_FmMuram; } ;
typedef  TYPE_6__ t_FmPcd ;

/* Variables and functions */
 int /*<<< orphan*/  FM_MURAM_FreeMem (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FmPcdFragHcScratchPoolEmpty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FmPcdUnregisterReassmPort (TYPE_6__*,int /*<<< orphan*/ *) ; 
 scalar_t__ HEADER_TYPE_CAPWAP ; 
 int /*<<< orphan*/ * UINT_TO_PTR (scalar_t__) ; 
 int /*<<< orphan*/  XX_Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XX_FreeSmart (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ReleaseManipHandler(t_FmPcdManip *p_Manip, t_FmPcd *p_FmPcd)
{
    if (p_Manip->h_Ad)
    {
        if (p_Manip->muramAllocate)
            FM_MURAM_FreeMem(p_FmPcd->h_FmMuram, p_Manip->h_Ad);
        else
            XX_Free(p_Manip->h_Ad);
        p_Manip->h_Ad = NULL;
    }
    if (p_Manip->p_Template)
    {
        FM_MURAM_FreeMem(p_FmPcd->h_FmMuram, p_Manip->p_Template);
        p_Manip->p_Template = NULL;
    }
#if (defined(FM_CAPWAP_SUPPORT) && (DPAA_VERSION == 10))
    if (p_Manip->h_Frag)
    {
        if (p_Manip->capwapFragParams.p_AutoLearnHashTbl)
        FM_MURAM_FreeMem(p_FmPcd->h_FmMuram,
                p_Manip->capwapFragParams.p_AutoLearnHashTbl);
        if (p_Manip->capwapFragParams.p_ReassmFrmDescrPoolTbl)
        FM_MURAM_FreeMem(p_FmPcd->h_FmMuram,
                p_Manip->capwapFragParams.p_ReassmFrmDescrPoolTbl);
        if (p_Manip->capwapFragParams.p_ReassmFrmDescrIndxPoolTbl)
        FM_MURAM_FreeMem(p_FmPcd->h_FmMuram,
                p_Manip->capwapFragParams.p_ReassmFrmDescrIndxPoolTbl);
        if (p_Manip->capwapFragParams.p_TimeOutTbl)
        FM_MURAM_FreeMem(p_FmPcd->h_FmMuram,
                p_Manip->capwapFragParams.p_TimeOutTbl);
        FM_MURAM_FreeMem(p_FmPcd->h_FmMuram, p_Manip->h_Frag);

    }
#endif /* (defined(FM_CAPWAP_SUPPORT) && (DPAA_VERSION == 10)) */
    if (p_Manip->frag)
    {
        if (p_Manip->fragParams.p_Frag)
        {
#if (DPAA_VERSION == 10)
            FmPcdFragHcScratchPoolEmpty((t_Handle)p_FmPcd, p_Manip->fragParams.scratchBpid);
#endif /* (DPAA_VERSION == 10) */

            FM_MURAM_FreeMem(p_FmPcd->h_FmMuram, p_Manip->fragParams.p_Frag);
        }
    }
    else
        if (p_Manip->reassm)
        {
            FmPcdUnregisterReassmPort(p_FmPcd,
                                      p_Manip->reassmParams.p_ReassCommonTbl);

            if (p_Manip->reassmParams.timeOutTblAddr)
                FM_MURAM_FreeMem(
                        p_FmPcd->h_FmMuram,
                        UINT_TO_PTR(p_Manip->reassmParams.timeOutTblAddr));
            if (p_Manip->reassmParams.reassFrmDescrPoolTblAddr)
                XX_FreeSmart(
                        UINT_TO_PTR(p_Manip->reassmParams.reassFrmDescrPoolTblAddr));
            if (p_Manip->reassmParams.p_ReassCommonTbl)
                FM_MURAM_FreeMem(p_FmPcd->h_FmMuram,
                                 p_Manip->reassmParams.p_ReassCommonTbl);
            if (p_Manip->reassmParams.reassFrmDescrIndxPoolTblAddr)
                FM_MURAM_FreeMem(
                        p_FmPcd->h_FmMuram,
                        UINT_TO_PTR(p_Manip->reassmParams.reassFrmDescrIndxPoolTblAddr));
            if (p_Manip->reassmParams.internalBufferPoolManagementIndexAddr)
                FM_MURAM_FreeMem(
                        p_FmPcd->h_FmMuram,
                        UINT_TO_PTR(p_Manip->reassmParams.internalBufferPoolManagementIndexAddr));
            if (p_Manip->reassmParams.internalBufferPoolAddr)
                FM_MURAM_FreeMem(
                        p_FmPcd->h_FmMuram,
                        UINT_TO_PTR(p_Manip->reassmParams.internalBufferPoolAddr));
            if (p_Manip->reassmParams.hdr == HEADER_TYPE_CAPWAP)
            {

            }
            else
            {
                if (p_Manip->reassmParams.ip.ipv4AutoLearnHashTblAddr)
                    XX_FreeSmart(
                            UINT_TO_PTR(p_Manip->reassmParams.ip.ipv4AutoLearnHashTblAddr));
                if (p_Manip->reassmParams.ip.ipv6AutoLearnHashTblAddr)
                    XX_FreeSmart(
                            UINT_TO_PTR(p_Manip->reassmParams.ip.ipv6AutoLearnHashTblAddr));
                if (p_Manip->reassmParams.ip.ipv4AutoLearnSetLockTblAddr)
                    XX_FreeSmart(
                            UINT_TO_PTR(p_Manip->reassmParams.ip.ipv4AutoLearnSetLockTblAddr));
                if (p_Manip->reassmParams.ip.ipv6AutoLearnSetLockTblAddr)
                    XX_FreeSmart(
                            UINT_TO_PTR(p_Manip->reassmParams.ip.ipv6AutoLearnSetLockTblAddr));
                if (p_Manip->reassmParams.ip.p_Ipv4ReassTbl)
                    FM_MURAM_FreeMem(p_FmPcd->h_FmMuram,
                                     p_Manip->reassmParams.ip.p_Ipv4ReassTbl);
                if (p_Manip->reassmParams.ip.p_Ipv6ReassTbl)
                    FM_MURAM_FreeMem(p_FmPcd->h_FmMuram,
                                     p_Manip->reassmParams.ip.p_Ipv6ReassTbl);
                if (p_Manip->reassmParams.ip.h_Ipv6Ad)
                    XX_FreeSmart(p_Manip->reassmParams.ip.h_Ipv6Ad);
                if (p_Manip->reassmParams.ip.h_Ipv4Ad)
                    XX_FreeSmart(p_Manip->reassmParams.ip.h_Ipv4Ad);
            }
        }

    if (p_Manip->p_StatsTbl)
        FM_MURAM_FreeMem(p_FmPcd->h_FmMuram, p_Manip->p_StatsTbl);
}