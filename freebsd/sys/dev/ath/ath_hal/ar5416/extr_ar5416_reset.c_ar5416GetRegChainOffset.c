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
 scalar_t__ AR_SREV_5416_V20_OR_LATER (struct ath_hal*) ; 

int
ar5416GetRegChainOffset(struct ath_hal *ah, int i)
{
	int regChainOffset;

	if (AR_SREV_5416_V20_OR_LATER(ah) && 
	    (AH5416(ah)->ah_rx_chainmask == 0x5 ||
	    AH5416(ah)->ah_tx_chainmask == 0x5) && (i != 0)) {
		/* Regs are swapped from chain 2 to 1 for 5416 2_0 with 
		 * only chains 0 and 2 populated 
		 */
		regChainOffset = (i == 1) ? 0x2000 : 0x1000;
	} else {
		regChainOffset = i * 0x1000;
	}

	return regChainOffset;
}