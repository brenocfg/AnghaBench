#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  statsTableAddr; } ;
typedef  TYPE_1__ t_AdOfTypeStats ;

/* Variables and functions */
 int FM_PCD_AD_STATS_COUNTERS_ADDR_MASK ; 
 int /*<<< orphan*/  WRITE_UINT32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void SetStatsCounters(t_AdOfTypeStats *p_StatsAd,
                             uint32_t statsCountersAddr)
{
    uint32_t tmp = (statsCountersAddr & FM_PCD_AD_STATS_COUNTERS_ADDR_MASK);

    WRITE_UINT32(p_StatsAd->statsTableAddr, tmp);
}