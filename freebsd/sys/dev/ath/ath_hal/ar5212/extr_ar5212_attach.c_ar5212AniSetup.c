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
struct ath_hal {int dummy; } ;
typedef  struct ar5212AniParams {int maxNoiseImmunityLevel; int maxSpurImmunityLevel; int maxFirstepLevel; int ofdmTrigHigh; int ofdmTrigLow; int cckTrigHigh; int cckTrigLow; int rssiThrHigh; int rssiThrLow; int period; int /*<<< orphan*/  firstep; int /*<<< orphan*/  cycPwrThr1; int /*<<< orphan*/  firpwr; int /*<<< orphan*/  coarseLow; int /*<<< orphan*/  coarseHigh; int /*<<< orphan*/  totalSizeDesired; } const ar5212AniParams ;
struct TYPE_4__ {int /*<<< orphan*/  ah_aniControl; } ;
struct TYPE_3__ {scalar_t__ ah_macVersion; } ;

/* Variables and functions */
 TYPE_2__* AH5212 (struct ath_hal*) ; 
 TYPE_1__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_TRUE ; 
 scalar_t__ AR_SREV_VERSION_GRIFFIN ; 
 int /*<<< orphan*/  OS_MEMCPY (struct ar5212AniParams const*,struct ar5212AniParams const*,int) ; 
 int /*<<< orphan*/  ar5212AniAttach (struct ath_hal*,struct ar5212AniParams const*,struct ar5212AniParams const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar5212AniControl ; 

__attribute__((used)) static void
ar5212AniSetup(struct ath_hal *ah)
{
	static const struct ar5212AniParams aniparams = {
		.maxNoiseImmunityLevel	= 4,	/* levels 0..4 */
		.totalSizeDesired	= { -55, -55, -55, -55, -62 },
		.coarseHigh		= { -14, -14, -14, -14, -12 },
		.coarseLow		= { -64, -64, -64, -64, -70 },
		.firpwr			= { -78, -78, -78, -78, -80 },
		.maxSpurImmunityLevel	= 2,	/* NB: depends on chip rev */
		.cycPwrThr1		= { 2, 4, 6, 8, 10, 12, 14, 16 },
		.maxFirstepLevel	= 2,	/* levels 0..2 */
		.firstep		= { 0, 4, 8 },
		.ofdmTrigHigh		= 500,
		.ofdmTrigLow		= 200,
		.cckTrigHigh		= 200,
		.cckTrigLow		= 100,
		.rssiThrHigh		= 40,
		.rssiThrLow		= 7,
		.period			= 100,
	};
	if (AH_PRIVATE(ah)->ah_macVersion < AR_SREV_VERSION_GRIFFIN) {
		struct ar5212AniParams tmp;
		OS_MEMCPY(&tmp, &aniparams, sizeof(struct ar5212AniParams));
		tmp.maxSpurImmunityLevel = 7;	/* Venice and earlier */
		ar5212AniAttach(ah, &tmp, &tmp, AH_TRUE);
	} else
		ar5212AniAttach(ah, &aniparams, &aniparams, AH_TRUE);

	/* Set overridable ANI methods */
	AH5212(ah)->ah_aniControl = ar5212AniControl;
}