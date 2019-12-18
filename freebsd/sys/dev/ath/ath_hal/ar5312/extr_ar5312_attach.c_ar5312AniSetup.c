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
struct ath_hal {int dummy; } ;
struct ar5212AniParams {int maxNoiseImmunityLevel; int maxSpurImmunityLevel; int maxFirstepLevel; int ofdmTrigHigh; int ofdmTrigLow; int cckTrigHigh; int cckTrigLow; int rssiThrHigh; int rssiThrLow; int period; int /*<<< orphan*/  firstep; int /*<<< orphan*/  cycPwrThr1; int /*<<< orphan*/  firpwr; int /*<<< orphan*/  coarseLow; int /*<<< orphan*/  coarseHigh; int /*<<< orphan*/  totalSizeDesired; } ;

/* Variables and functions */
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  ar5212AniAttach (struct ath_hal*,struct ar5212AniParams const*,struct ar5212AniParams const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ar5312AniSetup(struct ath_hal *ah)
{
	static const struct ar5212AniParams aniparams = {
		.maxNoiseImmunityLevel	= 4,	/* levels 0..4 */
		.totalSizeDesired	= { -41, -41, -48, -48, -48 },
		.coarseHigh		= { -18, -18, -16, -14, -12 },
		.coarseLow		= { -56, -56, -60, -60, -60 },
		.firpwr			= { -72, -72, -75, -78, -80 },
		.maxSpurImmunityLevel	= 2,
		.cycPwrThr1		= { 2, 4, 6 },
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
	ar5212AniAttach(ah, &aniparams, &aniparams, AH_TRUE);
}