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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int u_int ;
struct ath_hal {int dummy; } ;
struct TYPE_2__ {int ah_coverageClass; int /*<<< orphan*/  ah_curchan; } ;

/* Variables and functions */
 int ACK_CTS_TIMEOUT_11A ; 
 TYPE_1__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_D_GBL_IFS_EIFS ; 
 int /*<<< orphan*/  AR_D_GBL_IFS_SLOT ; 
 int /*<<< orphan*/  AR_TIME_OUT ; 
 int /*<<< orphan*/  AR_TIME_OUT_ACK ; 
 int /*<<< orphan*/  AR_TIME_OUT_CTS ; 
 int /*<<< orphan*/  IEEE80211_IS_CHAN_A (int /*<<< orphan*/ ) ; 
 scalar_t__ IEEE80211_IS_CHAN_HALF (int /*<<< orphan*/ ) ; 
 scalar_t__ IEEE80211_IS_CHAN_QUARTER (int /*<<< orphan*/ ) ; 
 scalar_t__ IFS_EIFS_FULL_RATE ; 
 scalar_t__ IFS_EIFS_HALF_RATE ; 
 scalar_t__ IFS_EIFS_QUARTER_RATE ; 
 scalar_t__ IFS_SLOT_FULL_RATE ; 
 scalar_t__ IFS_SLOT_HALF_RATE ; 
 scalar_t__ IFS_SLOT_QUARTER_RATE ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int SM (int,int /*<<< orphan*/ ) ; 
 int ath_hal_mac_clks (struct ath_hal*,int) ; 

void
ar5212SetCoverageClass(struct ath_hal *ah, uint8_t coverageclass, int now)
{
	uint32_t slot, timeout, eifs;
	u_int clkRate;

	AH_PRIVATE(ah)->ah_coverageClass = coverageclass;

	if (now) {
		if (AH_PRIVATE(ah)->ah_coverageClass == 0)
			return;

		/* Don't apply coverage class to non A channels */
		if (!IEEE80211_IS_CHAN_A(AH_PRIVATE(ah)->ah_curchan))
			return;

		/* Get core clock rate */
		clkRate = ath_hal_mac_clks(ah, 1);

		/* Compute EIFS */
		slot = coverageclass * 3 * clkRate;
		eifs = coverageclass * 6 * clkRate;
		if (IEEE80211_IS_CHAN_HALF(AH_PRIVATE(ah)->ah_curchan)) {
			slot += IFS_SLOT_HALF_RATE;
			eifs += IFS_EIFS_HALF_RATE;
		} else if (IEEE80211_IS_CHAN_QUARTER(AH_PRIVATE(ah)->ah_curchan)) {
			slot += IFS_SLOT_QUARTER_RATE;
			eifs += IFS_EIFS_QUARTER_RATE;
		} else { /* full rate */
			slot += IFS_SLOT_FULL_RATE;
			eifs += IFS_EIFS_FULL_RATE;
		}

		/*
		 * Add additional time for air propagation for ACK and CTS
		 * timeouts. This value is in core clocks.
  		 */
		timeout = ACK_CTS_TIMEOUT_11A + (coverageclass * 3 * clkRate);
	
		/*
		 * Write the values: slot, eifs, ack/cts timeouts.
		 */
		OS_REG_WRITE(ah, AR_D_GBL_IFS_SLOT, slot);
		OS_REG_WRITE(ah, AR_D_GBL_IFS_EIFS, eifs);
		OS_REG_WRITE(ah, AR_TIME_OUT,
			  SM(timeout, AR_TIME_OUT_CTS)
			| SM(timeout, AR_TIME_OUT_ACK));
	}
}