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
struct ath_hal {int dummy; } ;
struct ath_desc {int dummy; } ;
struct ar5212_desc {int /*<<< orphan*/  ds_ctl0; } ;

/* Variables and functions */
 struct ar5212_desc* AR5212DESC (struct ath_desc*) ; 
 int /*<<< orphan*/  AR_TxInterReq ; 
 int /*<<< orphan*/  __bswap32 (int /*<<< orphan*/ ) ; 

void
ar5212IntrReqTxDesc(struct ath_hal *ah, struct ath_desc *ds)
{
	struct ar5212_desc *ads = AR5212DESC(ds);

#ifdef AH_NEED_DESC_SWAP
	ads->ds_ctl0 |= __bswap32(AR_TxInterReq);
#else
	ads->ds_ctl0 |= AR_TxInterReq;
#endif
}