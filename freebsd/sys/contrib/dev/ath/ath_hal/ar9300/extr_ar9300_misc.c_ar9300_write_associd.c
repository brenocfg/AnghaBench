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
typedef  int u_int16_t ;
struct ath_hal_9300 {int ah_assoc_id; scalar_t__ ah_bssid; } ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_BSS_ID0 ; 
 int /*<<< orphan*/  AR_BSS_ID1 ; 
 int AR_BSS_ID1_AID_S ; 
 int /*<<< orphan*/  IEEE80211_ADDR_LEN ; 
 int LE_READ_2 (scalar_t__) ; 
 int LE_READ_4 (scalar_t__) ; 
 int /*<<< orphan*/  OS_MEMCPY (scalar_t__,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 

void
ar9300_write_associd(struct ath_hal *ah, const u_int8_t *bssid,
    u_int16_t assoc_id)
{
    struct ath_hal_9300 *ahp = AH9300(ah);

    /* save bssid and assoc_id for restore on reset */
    OS_MEMCPY(ahp->ah_bssid, bssid, IEEE80211_ADDR_LEN);
    ahp->ah_assoc_id = assoc_id;

    OS_REG_WRITE(ah, AR_BSS_ID0, LE_READ_4(ahp->ah_bssid));
    OS_REG_WRITE(ah, AR_BSS_ID1, LE_READ_2(ahp->ah_bssid + 4) |
                                 ((assoc_id & 0x3fff) << AR_BSS_ID1_AID_S));
}