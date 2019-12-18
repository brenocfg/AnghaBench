#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_channel {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  ns_avgbrssi; } ;
struct TYPE_6__ {TYPE_1__ ast_nodestats; } ;
struct ath_hal_9300 {TYPE_2__ ah_stats; } ;
struct ath_hal {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  ns_avgbrssi; } ;
typedef  TYPE_3__ HAL_NODE_STATS ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 

void
ar9300_ani_rxmonitor_freebsd(struct ath_hal *ah, const HAL_NODE_STATS *stats,
    const struct ieee80211_channel *chan)
{
	struct ath_hal_9300 *ahp = AH9300(ah);

	ahp->ah_stats.ast_nodestats.ns_avgbrssi = stats->ns_avgbrssi;
}