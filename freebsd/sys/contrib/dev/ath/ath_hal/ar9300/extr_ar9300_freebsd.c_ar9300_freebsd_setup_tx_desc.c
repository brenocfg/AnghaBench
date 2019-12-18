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
typedef  size_t u_int ;
struct ath_hal_9300 {int /*<<< orphan*/ * ah_keytype; } ;
struct ath_hal {int dummy; } ;
struct ath_desc {int dummy; } ;
typedef  int /*<<< orphan*/  HAL_PKT_TYPE ;
typedef  int /*<<< orphan*/  HAL_KEY_TYPE ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_TRUE ; 
 size_t HAL_TXKEYIX_INVALID ; 
 int /*<<< orphan*/  ar9300_set_11n_tx_desc (struct ath_hal*,struct ath_desc*,size_t,int /*<<< orphan*/ ,size_t,size_t,int /*<<< orphan*/ ,size_t) ; 

HAL_BOOL
ar9300_freebsd_setup_tx_desc(struct ath_hal *ah, struct ath_desc *ds,
    u_int pktLen, u_int hdrLen, HAL_PKT_TYPE type, u_int txPower,
    u_int txRate0, u_int txTries0, u_int keyIx, u_int antMode, u_int flags,
    u_int rtsctsRate, u_int rtsCtsDuration, u_int compicvLen,
    u_int compivLen, u_int comp)
{
	struct ath_hal_9300 *ahp = AH9300(ah);

	HAL_KEY_TYPE keyType = 0;	/* XXX No padding */

	if (keyIx != HAL_TXKEYIX_INVALID)
		keyType = ahp->ah_keytype[keyIx];

	/* XXX bounds check keyix */
	ar9300_set_11n_tx_desc(ah, ds, pktLen, type, txPower, keyIx,
	    keyType, flags);

	return AH_TRUE;
}