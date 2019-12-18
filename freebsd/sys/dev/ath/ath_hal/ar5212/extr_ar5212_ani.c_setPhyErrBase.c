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
struct ar5212AniParams {scalar_t__ ofdmTrigHigh; scalar_t__ cckTrigHigh; scalar_t__ cckPhyErrBase; scalar_t__ ofdmPhyErrBase; } ;

/* Variables and functions */
 scalar_t__ AR_PHY_COUNTMAX ; 
 int /*<<< orphan*/  HALDEBUG (struct ath_hal*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  HAL_DEBUG_ANY ; 

__attribute__((used)) static void
setPhyErrBase(struct ath_hal *ah, struct ar5212AniParams *params)
{
	if (params->ofdmTrigHigh >= AR_PHY_COUNTMAX) {
		HALDEBUG(ah, HAL_DEBUG_ANY,
		    "OFDM Trigger %d is too high for hw counters, using max\n",
		    params->ofdmTrigHigh);
		params->ofdmPhyErrBase = 0;
	} else
		params->ofdmPhyErrBase = AR_PHY_COUNTMAX - params->ofdmTrigHigh;
	if (params->cckTrigHigh >= AR_PHY_COUNTMAX) {
		HALDEBUG(ah, HAL_DEBUG_ANY,
		    "CCK Trigger %d is too high for hw counters, using max\n",
		    params->cckTrigHigh);
		params->cckPhyErrBase = 0;
	} else
		params->cckPhyErrBase = AR_PHY_COUNTMAX - params->cckTrigHigh;
}