#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_3__* p_Ipv6ReassTbl; TYPE_1__* p_Ipv4ReassTbl; } ;
struct TYPE_15__ {TYPE_4__ ip; TYPE_6__* p_ReassCommonTbl; } ;
struct TYPE_16__ {TYPE_5__ reassmParams; TYPE_2__* specificHdrStatistics; int /*<<< orphan*/  totalNCSPCounter; void* nonConsistentSp; int /*<<< orphan*/  totalDmaSemaphoreDepletionCounter; void* dmaSemaphoreDepletion; int /*<<< orphan*/  totalSgFragmentCounter; void* sgFragments; int /*<<< orphan*/  totalExternalBufferBusy; void* externalBufferBusy; int /*<<< orphan*/  totalInternalBufferBusy; void* internalBufferBusy; int /*<<< orphan*/  totalRfdPoolBusyCounter; void* rfdPoolBusy; int /*<<< orphan*/  totalTimeOutCounter; void* timeout; } ;
typedef  TYPE_6__ t_FmPcdManipReassemIpStats ;
typedef  TYPE_6__ t_FmPcdManip ;
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_13__ {int /*<<< orphan*/  totalMoreThan16FramesCounter; int /*<<< orphan*/  totalDiscardedFragsCounter; int /*<<< orphan*/  totalSetBusyCounter; int /*<<< orphan*/  totalMalformdFragCounter; int /*<<< orphan*/  totalProcessedFragCounter; int /*<<< orphan*/  totalValidFragmentCounter; int /*<<< orphan*/  totalSuccessfullyReasmFramesCounter; } ;
struct TYPE_12__ {void* moreThan16Fragments; void* discardedFragments; void* autoLearnBusy; void* malformedFragments; void* processedFragments; void* validFragments; void* successfullyReassembled; } ;
struct TYPE_11__ {int /*<<< orphan*/  totalMoreThan16FramesCounter; int /*<<< orphan*/  totalDiscardedFragsCounter; int /*<<< orphan*/  totalSetBusyCounter; int /*<<< orphan*/  totalMalformdFragCounter; int /*<<< orphan*/  totalProcessedFragCounter; int /*<<< orphan*/  totalValidFragmentCounter; int /*<<< orphan*/  totalSuccessfullyReasmFramesCounter; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_6__*) ; 
 int /*<<< orphan*/  E_OK ; 
 void* GET_UINT32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static t_Error IpReassemblyStats(t_FmPcdManip *p_Manip,
                                 t_FmPcdManipReassemIpStats *p_Stats)
{
    ASSERT_COND(p_Manip);
    ASSERT_COND(p_Stats);
    ASSERT_COND(p_Manip->reassmParams.p_ReassCommonTbl);

    p_Stats->timeout =
            GET_UINT32(p_Manip->reassmParams.p_ReassCommonTbl->totalTimeOutCounter);
    p_Stats->rfdPoolBusy =
            GET_UINT32(p_Manip->reassmParams.p_ReassCommonTbl->totalRfdPoolBusyCounter);
    p_Stats->internalBufferBusy =
            GET_UINT32(p_Manip->reassmParams.p_ReassCommonTbl->totalInternalBufferBusy);
    p_Stats->externalBufferBusy =
            GET_UINT32(p_Manip->reassmParams.p_ReassCommonTbl->totalExternalBufferBusy);
    p_Stats->sgFragments =
            GET_UINT32(p_Manip->reassmParams.p_ReassCommonTbl->totalSgFragmentCounter);
    p_Stats->dmaSemaphoreDepletion =
            GET_UINT32(p_Manip->reassmParams.p_ReassCommonTbl->totalDmaSemaphoreDepletionCounter);
#if (DPAA_VERSION >= 11)
    p_Stats->nonConsistentSp =
            GET_UINT32(p_Manip->reassmParams.p_ReassCommonTbl->totalNCSPCounter);
#endif /* (DPAA_VERSION >= 11) */

    if (p_Manip->reassmParams.ip.p_Ipv4ReassTbl)
    {
        p_Stats->specificHdrStatistics[0].successfullyReassembled =
                GET_UINT32(p_Manip->reassmParams.ip.p_Ipv4ReassTbl->totalSuccessfullyReasmFramesCounter);
        p_Stats->specificHdrStatistics[0].validFragments =
                GET_UINT32(p_Manip->reassmParams.ip.p_Ipv4ReassTbl->totalValidFragmentCounter);
        p_Stats->specificHdrStatistics[0].processedFragments =
                GET_UINT32(p_Manip->reassmParams.ip.p_Ipv4ReassTbl->totalProcessedFragCounter);
        p_Stats->specificHdrStatistics[0].malformedFragments =
                GET_UINT32(p_Manip->reassmParams.ip.p_Ipv4ReassTbl->totalMalformdFragCounter);
        p_Stats->specificHdrStatistics[0].autoLearnBusy =
                GET_UINT32(p_Manip->reassmParams.ip.p_Ipv4ReassTbl->totalSetBusyCounter);
        p_Stats->specificHdrStatistics[0].discardedFragments =
                GET_UINT32(p_Manip->reassmParams.ip.p_Ipv4ReassTbl->totalDiscardedFragsCounter);
        p_Stats->specificHdrStatistics[0].moreThan16Fragments =
                GET_UINT32(p_Manip->reassmParams.ip.p_Ipv4ReassTbl->totalMoreThan16FramesCounter);
    }
    if (p_Manip->reassmParams.ip.p_Ipv6ReassTbl)
    {
        p_Stats->specificHdrStatistics[1].successfullyReassembled =
                GET_UINT32(p_Manip->reassmParams.ip.p_Ipv6ReassTbl->totalSuccessfullyReasmFramesCounter);
        p_Stats->specificHdrStatistics[1].validFragments =
                GET_UINT32(p_Manip->reassmParams.ip.p_Ipv6ReassTbl->totalValidFragmentCounter);
        p_Stats->specificHdrStatistics[1].processedFragments =
                GET_UINT32(p_Manip->reassmParams.ip.p_Ipv6ReassTbl->totalProcessedFragCounter);
        p_Stats->specificHdrStatistics[1].malformedFragments =
                GET_UINT32(p_Manip->reassmParams.ip.p_Ipv6ReassTbl->totalMalformdFragCounter);
        p_Stats->specificHdrStatistics[1].autoLearnBusy =
                GET_UINT32(p_Manip->reassmParams.ip.p_Ipv6ReassTbl->totalSetBusyCounter);
        p_Stats->specificHdrStatistics[1].discardedFragments =
                GET_UINT32(p_Manip->reassmParams.ip.p_Ipv6ReassTbl->totalDiscardedFragsCounter);
        p_Stats->specificHdrStatistics[1].moreThan16Fragments =
                GET_UINT32(p_Manip->reassmParams.ip.p_Ipv6ReassTbl->totalMoreThan16FramesCounter);
    }
    return E_OK;
}