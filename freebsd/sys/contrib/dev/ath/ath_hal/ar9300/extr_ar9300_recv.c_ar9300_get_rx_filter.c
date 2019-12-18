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
 int /*<<< orphan*/  AR_RX_FILTER ; 
 int HAL_RX_FILTER_PHYERR ; 
 int HAL_RX_FILTER_PHYRADAR ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 

u_int32_t
ar9300_get_rx_filter(struct ath_hal *ah)
{
    u_int32_t bits = OS_REG_READ(ah, AR_RX_FILTER);
    u_int32_t phybits = OS_REG_READ(ah, AR_PHY_ERR);
    if (phybits & AR_PHY_ERR_RADAR) {
        bits |= HAL_RX_FILTER_PHYRADAR;
    }
    if (phybits & (AR_PHY_ERR_OFDM_TIMING | AR_PHY_ERR_CCK_TIMING)) {
        bits |= HAL_RX_FILTER_PHYERR;
    }
    return bits;
}