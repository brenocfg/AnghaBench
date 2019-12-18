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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  ast_ani_cckerrs; int /*<<< orphan*/  ast_ani_ofdmerrs; } ;
struct ath_hal_5212 {TYPE_1__ ah_stats; int /*<<< orphan*/  ah_mibStats; int /*<<< orphan*/  ah_hasHwPhyCounters; } ;
struct ath_hal {int dummy; } ;
struct ar5212AniState {scalar_t__ ofdmPhyErrCount; scalar_t__ cckPhyErrCount; struct ar5212AniParams* params; } ;
struct ar5212AniParams {scalar_t__ ofdmPhyErrBase; scalar_t__ cckPhyErrBase; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 struct ath_hal_5212* AH5212 (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_PHYCNT1 ; 
 int /*<<< orphan*/  AR_PHYCNT2 ; 
 scalar_t__ AR_PHY_COUNTMAX ; 
 int /*<<< orphan*/  HALASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HALDEBUG (struct ath_hal*,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  HAL_DEBUG_ANI ; 
 scalar_t__ OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar5212UpdateMibCounters (struct ath_hal*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
updateMIBStats(struct ath_hal *ah, struct ar5212AniState *aniState)
{
	struct ath_hal_5212 *ahp = AH5212(ah);
	const struct ar5212AniParams *params = aniState->params;
	uint32_t phyCnt1, phyCnt2;
	int32_t ofdmPhyErrCnt, cckPhyErrCnt;

	HALASSERT(ahp->ah_hasHwPhyCounters);

	/* Clear the mib counters and save them in the stats */
	ar5212UpdateMibCounters(ah, &ahp->ah_mibStats);

	/* NB: these are not reset-on-read */
	phyCnt1 = OS_REG_READ(ah, AR_PHYCNT1);
	phyCnt2 = OS_REG_READ(ah, AR_PHYCNT2);

	/* NB: these are spec'd to never roll-over */
	ofdmPhyErrCnt = phyCnt1 - params->ofdmPhyErrBase;
	if (ofdmPhyErrCnt < 0) {
		HALDEBUG(ah, HAL_DEBUG_ANI, "OFDM phyErrCnt %d phyCnt1 0x%x\n",
		    ofdmPhyErrCnt, phyCnt1);
		ofdmPhyErrCnt = AR_PHY_COUNTMAX;
	}
	ahp->ah_stats.ast_ani_ofdmerrs +=
	     ofdmPhyErrCnt - aniState->ofdmPhyErrCount;
	aniState->ofdmPhyErrCount = ofdmPhyErrCnt;

	cckPhyErrCnt = phyCnt2 - params->cckPhyErrBase;
	if (cckPhyErrCnt < 0) {
		HALDEBUG(ah, HAL_DEBUG_ANI, "CCK phyErrCnt %d phyCnt2 0x%x\n",
		    cckPhyErrCnt, phyCnt2);
		cckPhyErrCnt = AR_PHY_COUNTMAX;
	}
	ahp->ah_stats.ast_ani_cckerrs +=
		cckPhyErrCnt - aniState->cckPhyErrCount;
	aniState->cckPhyErrCount = cckPhyErrCnt;
}