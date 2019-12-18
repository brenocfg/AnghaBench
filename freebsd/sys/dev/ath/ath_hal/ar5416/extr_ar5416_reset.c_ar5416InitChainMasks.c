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
struct ath_hal {int dummy; } ;
struct TYPE_2__ {int ah_rx_chainmask; int ah_tx_chainmask; } ;

/* Variables and functions */
 TYPE_1__* AH5416 (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_PHY_ANALOG_SWAP ; 
 int /*<<< orphan*/  AR_PHY_CAL_CHAINMASK ; 
 int /*<<< orphan*/  AR_PHY_RX_CHAINMASK ; 
 int /*<<< orphan*/  AR_PHY_SWAP_ALT_CHAIN ; 
 int /*<<< orphan*/  AR_SELFGEN_MASK ; 
 scalar_t__ AR_SREV_HOWL (struct ath_hal*) ; 
 scalar_t__ IS_5416V1 (struct ath_hal*) ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_SET_BIT (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 

void
ar5416InitChainMasks(struct ath_hal *ah)
{
	int rx_chainmask = AH5416(ah)->ah_rx_chainmask;

	/* Flip this for this chainmask regardless of chip */
	if (rx_chainmask == 0x5)
		OS_REG_SET_BIT(ah, AR_PHY_ANALOG_SWAP, AR_PHY_SWAP_ALT_CHAIN);

	/*
	 * Workaround for OWL 1.0 calibration failure; enable multi-chain;
	 * then set true mask after calibration.
	 */
	if (IS_5416V1(ah) && (rx_chainmask == 0x5 || rx_chainmask == 0x3)) {
		OS_REG_WRITE(ah, AR_PHY_RX_CHAINMASK, 0x7);
		OS_REG_WRITE(ah, AR_PHY_CAL_CHAINMASK, 0x7);
	} else {
		OS_REG_WRITE(ah, AR_PHY_RX_CHAINMASK, AH5416(ah)->ah_rx_chainmask);
		OS_REG_WRITE(ah, AR_PHY_CAL_CHAINMASK, AH5416(ah)->ah_rx_chainmask);
	}
	OS_REG_WRITE(ah, AR_SELFGEN_MASK, AH5416(ah)->ah_tx_chainmask);

	if (AH5416(ah)->ah_tx_chainmask == 0x5)
		OS_REG_SET_BIT(ah, AR_PHY_ANALOG_SWAP, AR_PHY_SWAP_ALT_CHAIN);

	if (AR_SREV_HOWL(ah)) {
		OS_REG_WRITE(ah, AR_PHY_ANALOG_SWAP,
		OS_REG_READ(ah, AR_PHY_ANALOG_SWAP) | 0x00000001);
	}
}