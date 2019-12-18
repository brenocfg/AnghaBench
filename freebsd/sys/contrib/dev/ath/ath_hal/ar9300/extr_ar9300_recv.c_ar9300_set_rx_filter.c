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
typedef  int u_int32_t ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_ERR ; 
 int AR_PHY_ERR_CCK_TIMING ; 
 int AR_PHY_ERR_OFDM_TIMING ; 
 int AR_PHY_ERR_RADAR ; 
 int /*<<< orphan*/  AR_RXCFG ; 
 int AR_RXCFG_ZLFDMA ; 
 int AR_RX_4ADDRESS ; 
 int AR_RX_COMPR_BAR ; 
 int AR_RX_CONTROL_WRAPPER ; 
 int /*<<< orphan*/  AR_RX_FILTER ; 
 int AR_RX_UNCOM_BA_BAR ; 
 scalar_t__ AR_SREV_APHRODITE (struct ath_hal*) ; 
 scalar_t__ AR_SREV_HONEYBEE (struct ath_hal*) ; 
 scalar_t__ AR_SREV_JUPITER (struct ath_hal*) ; 
 scalar_t__ AR_SREV_SCORPION (struct ath_hal*) ; 
 int HAL_RX_FILTER_PHYERR ; 
 int HAL_RX_FILTER_PHYRADAR ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 

void
ar9300_set_rx_filter(struct ath_hal *ah, u_int32_t bits)
{
    u_int32_t phybits;

    if (AR_SREV_SCORPION(ah) || AR_SREV_HONEYBEE(ah)) {
        /* Enable Rx for 4 address frames */
        bits |= AR_RX_4ADDRESS;
    }
    if (AR_SREV_JUPITER(ah) || AR_SREV_APHRODITE(ah)) {
        /* HW fix for rx hang and corruption. */
        bits |= AR_RX_CONTROL_WRAPPER;
    }
    OS_REG_WRITE(ah, AR_RX_FILTER,
        bits | AR_RX_UNCOM_BA_BAR | AR_RX_COMPR_BAR);
    phybits = 0;
    if (bits & HAL_RX_FILTER_PHYRADAR) {
        phybits |= AR_PHY_ERR_RADAR;
    }
    if (bits & HAL_RX_FILTER_PHYERR) {
        phybits |= AR_PHY_ERR_OFDM_TIMING | AR_PHY_ERR_CCK_TIMING;
    }
    OS_REG_WRITE(ah, AR_PHY_ERR, phybits);
    if (phybits) {
        OS_REG_WRITE(ah, AR_RXCFG,
            OS_REG_READ(ah, AR_RXCFG) | AR_RXCFG_ZLFDMA);
    } else {
        OS_REG_WRITE(ah, AR_RXCFG,
            OS_REG_READ(ah, AR_RXCFG) &~ AR_RXCFG_ZLFDMA);
    }
}