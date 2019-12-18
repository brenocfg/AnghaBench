#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_5__ {scalar_t__ h_StatsCounters; scalar_t__ h_StatsFLRs; scalar_t__ h_StatsAd; } ;
typedef  TYPE_1__ t_FmPcdCcStatsParams ;
struct TYPE_6__ {int /*<<< orphan*/  nextActionIndx; int /*<<< orphan*/  profileTableAddr; } ;
typedef  TYPE_2__ t_AdOfTypeStats ;

/* Variables and functions */
 int FM_PCD_AD_STATS_FLR_ADDR_MASK ; 
 int FM_PCD_AD_STATS_FLR_EN ; 
 int FM_PCD_AD_STATS_NAD_EN ; 
 int FM_PCD_AD_STATS_NEXT_ACTION_MASK ; 
 int FM_PCD_AD_STATS_NEXT_ACTION_SHIFT ; 
 int FM_PCD_AD_STATS_OP_CODE ; 
 int FM_PCD_AD_STATS_TYPE ; 
 int /*<<< orphan*/  SetStatsCounters (TYPE_2__*,int) ; 
 int /*<<< orphan*/  WRITE_UINT32 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ XX_VirtToPhys (scalar_t__) ; 

__attribute__((used)) static void UpdateStatsAd(t_FmPcdCcStatsParams *p_FmPcdCcStatsParams,
                          t_Handle h_Ad, uint64_t physicalMuramBase)
{
    t_AdOfTypeStats *p_StatsAd;
    uint32_t statsCountersAddr, nextActionAddr, tmp;
#if (DPAA_VERSION >= 11)
    uint32_t frameLengthRangesAddr;
#endif /* (DPAA_VERSION >= 11) */

    p_StatsAd = (t_AdOfTypeStats *)p_FmPcdCcStatsParams->h_StatsAd;

    tmp = FM_PCD_AD_STATS_TYPE;

#if (DPAA_VERSION >= 11)
    if (p_FmPcdCcStatsParams->h_StatsFLRs)
    {
        frameLengthRangesAddr = (uint32_t)((XX_VirtToPhys(
                p_FmPcdCcStatsParams->h_StatsFLRs) - physicalMuramBase));
        tmp |= (frameLengthRangesAddr & FM_PCD_AD_STATS_FLR_ADDR_MASK);
    }
#endif /* (DPAA_VERSION >= 11) */
    WRITE_UINT32(p_StatsAd->profileTableAddr, tmp);

    nextActionAddr = (uint32_t)((XX_VirtToPhys(h_Ad) - physicalMuramBase));
    tmp = 0;
    tmp |= (uint32_t)((nextActionAddr << FM_PCD_AD_STATS_NEXT_ACTION_SHIFT)
            & FM_PCD_AD_STATS_NEXT_ACTION_MASK);
    tmp |= (FM_PCD_AD_STATS_NAD_EN | FM_PCD_AD_STATS_OP_CODE);

#if (DPAA_VERSION >= 11)
    if (p_FmPcdCcStatsParams->h_StatsFLRs)
        tmp |= FM_PCD_AD_STATS_FLR_EN;
#endif /* (DPAA_VERSION >= 11) */

    WRITE_UINT32(p_StatsAd->nextActionIndx, tmp);

    statsCountersAddr = (uint32_t)((XX_VirtToPhys(
            p_FmPcdCcStatsParams->h_StatsCounters) - physicalMuramBase));
    SetStatsCounters(p_StatsAd, statsCountersAddr);
}