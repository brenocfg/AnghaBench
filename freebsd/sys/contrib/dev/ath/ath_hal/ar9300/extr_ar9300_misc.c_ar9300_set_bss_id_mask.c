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
typedef  int /*<<< orphan*/  u_int8_t ;
struct ath_hal_9300 {scalar_t__ ah_bssid_mask; } ;
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  AR_BSSMSKL ; 
 int /*<<< orphan*/  AR_BSSMSKU ; 
 int /*<<< orphan*/  IEEE80211_ADDR_LEN ; 
 int /*<<< orphan*/  LE_READ_2 (scalar_t__) ; 
 int /*<<< orphan*/  LE_READ_4 (scalar_t__) ; 
 int /*<<< orphan*/  OS_MEMCPY (scalar_t__,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

HAL_BOOL
ar9300_set_bss_id_mask(struct ath_hal *ah, const u_int8_t *mask)
{
    struct ath_hal_9300 *ahp = AH9300(ah);

    /* save it since it must be rewritten on reset */
    OS_MEMCPY(ahp->ah_bssid_mask, mask, IEEE80211_ADDR_LEN);

    OS_REG_WRITE(ah, AR_BSSMSKL, LE_READ_4(ahp->ah_bssid_mask));
    OS_REG_WRITE(ah, AR_BSSMSKU, LE_READ_2(ahp->ah_bssid_mask + 4));
    return AH_TRUE;
}