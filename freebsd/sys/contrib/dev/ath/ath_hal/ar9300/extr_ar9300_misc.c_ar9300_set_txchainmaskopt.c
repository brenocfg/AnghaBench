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
typedef  int u_int8_t ;
struct ath_hal_9300 {int ah_tx_chainmask; int ah_tx_chainmaskopt; } ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 
 int /*<<< orphan*/  ath_hal_printf (struct ath_hal*,char*,int,int) ; 

void
ar9300_set_txchainmaskopt(struct ath_hal *ah, u_int8_t mask)
{
    struct ath_hal_9300 *ahp = AH9300(ah);

    /* optional txchainmask should be subset of primary txchainmask */
    if ((mask & ahp->ah_tx_chainmask) != mask) {
        ahp->ah_tx_chainmaskopt = 0;
        ath_hal_printf(ah, "Error: ah_tx_chainmask=%d, mask=%d\n", ahp->ah_tx_chainmask, mask);
        return;
    }
    
    ahp->ah_tx_chainmaskopt = mask;
}