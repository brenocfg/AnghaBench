#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ath_rx_status {scalar_t__ rs_phyerr; } ;
struct TYPE_2__ {int /*<<< orphan*/  ast_ani_cckerrs; int /*<<< orphan*/  ast_ani_ofdmerrs; } ;
struct ath_hal_5212 {TYPE_1__ ah_stats; struct ar5212AniState* ah_curani; int /*<<< orphan*/  ah_hasHwPhyCounters; } ;
struct ath_hal {int dummy; } ;
struct ar5212AniState {scalar_t__ ofdmPhyErrCount; scalar_t__ cckPhyErrCount; struct ar5212AniParams* params; } ;
struct ar5212AniParams {scalar_t__ ofdmTrigHigh; scalar_t__ cckTrigHigh; } ;

/* Variables and functions */
 struct ath_hal_5212* AH5212 (struct ath_hal*) ; 
 struct ath_rx_status const* AH_NULL ; 
 int /*<<< orphan*/  HALASSERT (int) ; 
 scalar_t__ HAL_PHYERR_CCK_TIMING ; 
 scalar_t__ HAL_PHYERR_OFDM_TIMING ; 
 int /*<<< orphan*/  ar5212AniCckErrTrigger (struct ath_hal*) ; 
 int /*<<< orphan*/  ar5212AniOfdmErrTrigger (struct ath_hal*) ; 
 int /*<<< orphan*/  ar5212AniRestart (struct ath_hal*,struct ar5212AniState*) ; 

void 
ar5212AniPhyErrReport(struct ath_hal *ah, const struct ath_rx_status *rs)
{
	struct ath_hal_5212 *ahp = AH5212(ah);
	struct ar5212AniState *aniState;
	const struct ar5212AniParams *params;

	HALASSERT(!ahp->ah_hasHwPhyCounters && rs != AH_NULL);

	aniState = ahp->ah_curani;
	params = aniState->params;
	if (rs->rs_phyerr == HAL_PHYERR_OFDM_TIMING) {
		aniState->ofdmPhyErrCount++;
		ahp->ah_stats.ast_ani_ofdmerrs++;
		if (aniState->ofdmPhyErrCount > params->ofdmTrigHigh) {
			ar5212AniOfdmErrTrigger(ah);
			ar5212AniRestart(ah, aniState);
		}
	} else if (rs->rs_phyerr == HAL_PHYERR_CCK_TIMING) {
		aniState->cckPhyErrCount++;
		ahp->ah_stats.ast_ani_cckerrs++;
		if (aniState->cckPhyErrCount > params->cckTrigHigh) {
			ar5212AniCckErrTrigger(ah);
			ar5212AniRestart(ah, aniState);
		}
	}
}