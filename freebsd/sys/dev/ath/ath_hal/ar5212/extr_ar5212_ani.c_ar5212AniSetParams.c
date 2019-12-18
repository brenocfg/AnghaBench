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
struct ath_hal_5212 {int ah_procPhyErr; int /*<<< orphan*/  ah_ani; int /*<<< orphan*/  ah_aniParams5; int /*<<< orphan*/  ah_aniParams24; } ;
struct ath_hal {int dummy; } ;
struct ar5212AniParams {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ah_opmode; int /*<<< orphan*/  ah_curchan; } ;
typedef  int HAL_BOOL ;

/* Variables and functions */
 struct ath_hal_5212* AH5212 (struct ath_hal*) ; 
 int AH_FALSE ; 
 TYPE_1__* AH_PRIVATE (struct ath_hal*) ; 
 int AH_TRUE ; 
 int HAL_ANI_ENA ; 
 int /*<<< orphan*/  HAL_ANI_MODE ; 
 int /*<<< orphan*/  OS_MEMCPY (int /*<<< orphan*/ *,struct ar5212AniParams const*,int) ; 
 int /*<<< orphan*/  OS_MEMZERO (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ar5212AniControl (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ar5212AniReset (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setPhyErrBase (struct ath_hal*,int /*<<< orphan*/ *) ; 

HAL_BOOL
ar5212AniSetParams(struct ath_hal *ah, const struct ar5212AniParams *params24,
	const struct ar5212AniParams *params5)
{
	struct ath_hal_5212 *ahp = AH5212(ah);
	HAL_BOOL ena = (ahp->ah_procPhyErr & HAL_ANI_ENA) != 0;

	ar5212AniControl(ah, HAL_ANI_MODE, AH_FALSE);

	OS_MEMCPY(&ahp->ah_aniParams24, params24, sizeof(*params24));
	setPhyErrBase(ah, &ahp->ah_aniParams24);
	OS_MEMCPY(&ahp->ah_aniParams5, params5, sizeof(*params5));
	setPhyErrBase(ah, &ahp->ah_aniParams5);

	OS_MEMZERO(ahp->ah_ani, sizeof(ahp->ah_ani));
	ar5212AniReset(ah, AH_PRIVATE(ah)->ah_curchan,
	    AH_PRIVATE(ah)->ah_opmode, AH_FALSE);

	ar5212AniControl(ah, HAL_ANI_MODE, ena);

	return AH_TRUE;
}