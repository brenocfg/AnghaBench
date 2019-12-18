#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ath_hal_5212 {int /*<<< orphan*/  ah_stats; int /*<<< orphan*/  ah_mibStats; } ;
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  HAL_ANI_STATS ;

/* Variables and functions */
 struct ath_hal_5212* AH5212 (struct ath_hal*) ; 
 int /*<<< orphan*/  ar5212UpdateMibCounters (struct ath_hal*,int /*<<< orphan*/ *) ; 

HAL_ANI_STATS *
ar5212AniGetCurrentStats(struct ath_hal *ah)
{
	struct ath_hal_5212 *ahp = AH5212(ah);

	/* update mib stats so we return current data */
	/* XXX? side-effects to doing this here? */
	ar5212UpdateMibCounters(ah, &ahp->ah_mibStats);
	return &ahp->ah_stats;
}