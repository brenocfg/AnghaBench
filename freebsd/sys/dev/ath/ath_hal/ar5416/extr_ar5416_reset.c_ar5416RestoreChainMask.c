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
struct TYPE_2__ {int ah_rx_chainmask; } ;

/* Variables and functions */
 TYPE_1__* AH5416 (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_PHY_CAL_CHAINMASK ; 
 int /*<<< orphan*/  AR_PHY_RX_CHAINMASK ; 
 scalar_t__ IS_5416V1 (struct ath_hal*) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 

void
ar5416RestoreChainMask(struct ath_hal *ah)
{
	int rx_chainmask = AH5416(ah)->ah_rx_chainmask;

	if (IS_5416V1(ah) && (rx_chainmask == 0x5 || rx_chainmask == 0x3)) {
		OS_REG_WRITE(ah, AR_PHY_RX_CHAINMASK, rx_chainmask);
		OS_REG_WRITE(ah, AR_PHY_CAL_CHAINMASK, rx_chainmask);
	}
}