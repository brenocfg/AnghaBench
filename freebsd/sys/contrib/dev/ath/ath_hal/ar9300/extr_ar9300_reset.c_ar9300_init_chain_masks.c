#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ath_hal {int dummy; } ;
struct TYPE_6__ {scalar_t__ green_ap_ps_on; } ;
struct TYPE_4__ {scalar_t__ halApmEnable; } ;
struct TYPE_5__ {TYPE_1__ ah_caps; } ;

/* Variables and functions */
 TYPE_3__* AH9300 (struct ath_hal*) ; 
 TYPE_2__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_PHY_ANALOG_SWAP ; 
 int /*<<< orphan*/  AR_PHY_CAL_CHAINMASK ; 
 int /*<<< orphan*/  AR_PHY_RX_CHAINMASK ; 
 int /*<<< orphan*/  AR_PHY_SWAP_ALT_CHAIN ; 
 int /*<<< orphan*/  AR_SELFGEN_MASK ; 
 int HAL_GREEN_AP_RX_MASK ; 
 int /*<<< orphan*/  OS_REG_SET_BIT (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
ar9300_init_chain_masks(struct ath_hal *ah, int rx_chainmask, int tx_chainmask)
{
    if (AH9300(ah)->green_ap_ps_on) {
        rx_chainmask = HAL_GREEN_AP_RX_MASK;
    }
    if (rx_chainmask == 0x5) {
        OS_REG_SET_BIT(ah, AR_PHY_ANALOG_SWAP, AR_PHY_SWAP_ALT_CHAIN);
    }
    OS_REG_WRITE(ah, AR_PHY_RX_CHAINMASK, rx_chainmask);
    OS_REG_WRITE(ah, AR_PHY_CAL_CHAINMASK, rx_chainmask);

    /*
     * Adaptive Power Management:
     * Some 3 stream chips exceed the PCIe power requirements.
     * This workaround will reduce power consumption by using 2 tx chains
     * for 1 and 2 stream rates (5 GHz only).
     *
     * Set the self gen mask to 2 tx chains when APM is enabled.
     *
     */
    if (AH_PRIVATE(ah)->ah_caps.halApmEnable && (tx_chainmask == 0x7)) {
        OS_REG_WRITE(ah, AR_SELFGEN_MASK, 0x3);
    }
    else {
        OS_REG_WRITE(ah, AR_SELFGEN_MASK, tx_chainmask);
    }

    if (tx_chainmask == 0x5) {
        OS_REG_SET_BIT(ah, AR_PHY_ANALOG_SWAP, AR_PHY_SWAP_ALT_CHAIN);
    }
}