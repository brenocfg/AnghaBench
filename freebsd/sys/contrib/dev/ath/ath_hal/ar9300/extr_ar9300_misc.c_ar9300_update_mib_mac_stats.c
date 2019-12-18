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
struct TYPE_4__ {int /*<<< orphan*/  beacons; int /*<<< orphan*/  rts_good; int /*<<< orphan*/  fcs_bad; int /*<<< orphan*/  rts_bad; int /*<<< orphan*/  ackrcv_bad; } ;
struct TYPE_3__ {TYPE_2__ ast_mibstats; } ;
struct ath_hal_9300 {TYPE_1__ ah_stats; } ;
struct ath_hal {int dummy; } ;
typedef  TYPE_2__ HAL_MIB_STATS ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_ACK_FAIL ; 
 int /*<<< orphan*/  AR_BEACON_CNT ; 
 int /*<<< orphan*/  AR_FCS_FAIL ; 
 int /*<<< orphan*/  AR_RTS_FAIL ; 
 int /*<<< orphan*/  AR_RTS_OK ; 
 scalar_t__ OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 

void
ar9300_update_mib_mac_stats(struct ath_hal *ah)
{
    struct ath_hal_9300 *ahp = AH9300(ah);
    HAL_MIB_STATS* stats = &ahp->ah_stats.ast_mibstats;

    stats->ackrcv_bad += OS_REG_READ(ah, AR_ACK_FAIL);
    stats->rts_bad    += OS_REG_READ(ah, AR_RTS_FAIL);
    stats->fcs_bad    += OS_REG_READ(ah, AR_FCS_FAIL);
    stats->rts_good   += OS_REG_READ(ah, AR_RTS_OK);
    stats->beacons    += OS_REG_READ(ah, AR_BEACON_CNT);
}