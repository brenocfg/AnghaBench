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
typedef  int uint32_t ;
struct ath_hal_5212 {int ah_miscMode; } ;
struct ath_hal {int dummy; } ;
struct TYPE_3__ {scalar_t__ halBssidMatchSupport; } ;
struct TYPE_4__ {TYPE_1__ ah_caps; } ;

/* Variables and functions */
 struct ath_hal_5212* AH5212 (struct ath_hal*) ; 
 TYPE_2__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_MISC_MODE ; 
 int AR_MISC_MODE_BSSID_MATCH_FORCE ; 
 int /*<<< orphan*/  AR_PHY_ERR ; 
 int AR_PHY_ERR_CCK_TIMING ; 
 int AR_PHY_ERR_OFDM_TIMING ; 
 int AR_PHY_ERR_RADAR ; 
 int /*<<< orphan*/  AR_RXCFG ; 
 int AR_RXCFG_ZLFDMA ; 
 int /*<<< orphan*/  AR_RX_FILTER ; 
 int HAL_RX_FILTER_BSSID ; 
 int HAL_RX_FILTER_PHYERR ; 
 int HAL_RX_FILTER_PHYRADAR ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 

void
ar5212SetRxFilter(struct ath_hal *ah, uint32_t bits)
{
	struct ath_hal_5212 *ahp = AH5212(ah);
	uint32_t phybits;

	OS_REG_WRITE(ah, AR_RX_FILTER,
	    bits &~ (HAL_RX_FILTER_PHYRADAR|HAL_RX_FILTER_PHYERR|
	    HAL_RX_FILTER_BSSID));
	phybits = 0;
	if (bits & HAL_RX_FILTER_PHYRADAR)
		phybits |= AR_PHY_ERR_RADAR;
	if (bits & HAL_RX_FILTER_PHYERR)
		phybits |= AR_PHY_ERR_OFDM_TIMING | AR_PHY_ERR_CCK_TIMING;
	OS_REG_WRITE(ah, AR_PHY_ERR, phybits);
	if (phybits) {
		OS_REG_WRITE(ah, AR_RXCFG,
			OS_REG_READ(ah, AR_RXCFG) | AR_RXCFG_ZLFDMA);
	} else {
		OS_REG_WRITE(ah, AR_RXCFG,
			OS_REG_READ(ah, AR_RXCFG) &~ AR_RXCFG_ZLFDMA);
	}
	if (AH_PRIVATE(ah)->ah_caps.halBssidMatchSupport) {
		if (bits & HAL_RX_FILTER_BSSID)
			ahp->ah_miscMode |= AR_MISC_MODE_BSSID_MATCH_FORCE;
		else
			ahp->ah_miscMode &= ~AR_MISC_MODE_BSSID_MATCH_FORCE;
		OS_REG_WRITE(ah, AR_MISC_MODE, OS_REG_READ(ah, AR_MISC_MODE) | ahp->ah_miscMode);
	}
}