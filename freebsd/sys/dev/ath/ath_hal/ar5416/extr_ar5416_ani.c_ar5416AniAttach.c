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
struct ath_hal_5212 {int /*<<< orphan*/  ah_procPhyErr; int /*<<< orphan*/  ah_aniParams24; int /*<<< orphan*/  ah_ani; int /*<<< orphan*/  ah_aniParams5; } ;
struct ath_hal {int dummy; } ;
struct ar5212AniParams {int dummy; } ;
typedef  scalar_t__ HAL_BOOL ;

/* Variables and functions */
 struct ath_hal_5212* AH5212 (struct ath_hal*) ; 
 struct ar5212AniParams const* AH_NULL ; 
 int /*<<< orphan*/  HALASSERT (int) ; 
 int /*<<< orphan*/  HAL_ANI_ENA ; 
 int /*<<< orphan*/  OS_MEMCPY (int /*<<< orphan*/ *,struct ar5212AniParams const*,int) ; 
 int /*<<< orphan*/  OS_MEMZERO (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  enableAniMIBCounters (struct ath_hal*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setPhyErrBase (struct ath_hal*,int /*<<< orphan*/ *) ; 

void
ar5416AniAttach(struct ath_hal *ah, const struct ar5212AniParams *params24,
	const struct ar5212AniParams *params5, HAL_BOOL enable)
{
	struct ath_hal_5212 *ahp = AH5212(ah);

	if (params24 != AH_NULL) {
		OS_MEMCPY(&ahp->ah_aniParams24, params24, sizeof(*params24));
		setPhyErrBase(ah, &ahp->ah_aniParams24);
	}
	if (params5 != AH_NULL) {
		OS_MEMCPY(&ahp->ah_aniParams5, params5, sizeof(*params5));
		setPhyErrBase(ah, &ahp->ah_aniParams5);
	}

	OS_MEMZERO(ahp->ah_ani, sizeof(ahp->ah_ani));
	/* Enable MIB Counters */
	enableAniMIBCounters(ah, &ahp->ah_aniParams24 /*XXX*/);

	if (enable) {		/* Enable ani now */
		HALASSERT(params24 != AH_NULL && params5 != AH_NULL);
		ahp->ah_procPhyErr |= HAL_ANI_ENA;
	} else {
		ahp->ah_procPhyErr &= ~HAL_ANI_ENA;
	}
}