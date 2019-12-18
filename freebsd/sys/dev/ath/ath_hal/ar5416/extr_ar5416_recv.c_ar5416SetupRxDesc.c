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
typedef  int uint32_t ;
typedef  int u_int ;
struct ath_hal {int dummy; } ;
struct ath_desc {int dummy; } ;
struct ar5416_desc {int ds_ctl1; int /*<<< orphan*/  u; int /*<<< orphan*/  ds_rxstatus8; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AH_TRUE ; 
 struct ar5416_desc* AR5416DESC (struct ath_desc*) ; 
 int AR_BufLen ; 
 int /*<<< orphan*/  AR_RxDone ; 
 int AR_RxIntrReq ; 
 int /*<<< orphan*/  HALASSERT (int) ; 
 int HAL_RXDESC_INTREQ ; 
 int /*<<< orphan*/  OS_MEMZERO (int /*<<< orphan*/ *,int) ; 

HAL_BOOL
ar5416SetupRxDesc(struct ath_hal *ah, struct ath_desc *ds,
    uint32_t size, u_int flags)
{
	struct ar5416_desc *ads = AR5416DESC(ds);

	HALASSERT((size &~ AR_BufLen) == 0);

	ads->ds_ctl1 = size & AR_BufLen;
	if (flags & HAL_RXDESC_INTREQ)
		ads->ds_ctl1 |= AR_RxIntrReq;

	/* this should be enough */
	ads->ds_rxstatus8 &= ~AR_RxDone;

	/* clear the rest of the status fields */
	OS_MEMZERO(&(ads->u), sizeof(ads->u));

	return AH_TRUE;
}