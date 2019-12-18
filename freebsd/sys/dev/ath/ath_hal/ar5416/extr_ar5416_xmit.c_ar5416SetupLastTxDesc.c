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
struct ath_desc {int dummy; } ;
struct ar5416_desc {void* ds_ctl3; void* ds_ctl2; int /*<<< orphan*/  ds_ctl6; int /*<<< orphan*/  ds_ctl1; } ;
struct TYPE_2__ {void* ds_ctl3; void* ds_ctl2; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AH_TRUE ; 
 struct ar5416_desc* AR5416DESC (struct ath_desc*) ; 
 TYPE_1__* AR5416DESC_CONST (struct ath_desc const*) ; 
 int /*<<< orphan*/  AR_MoreAggr ; 
 int /*<<< orphan*/  AR_PadDelim ; 
 void* __bswap32 (void*) ; 

HAL_BOOL
ar5416SetupLastTxDesc(struct ath_hal *ah, struct ath_desc *ds,
		const struct ath_desc *ds0)
{
	struct ar5416_desc *ads = AR5416DESC(ds);

	ads->ds_ctl1 &= ~AR_MoreAggr;
	ads->ds_ctl6 &= ~AR_PadDelim;

	/* hack to copy rate info to last desc for later processing */
#ifdef AH_NEED_DESC_SWAP
	ads->ds_ctl2 = __bswap32(AR5416DESC_CONST(ds0)->ds_ctl2);
	ads->ds_ctl3 = __bswap32(AR5416DESC_CONST(ds0)->ds_ctl3);
#else
	ads->ds_ctl2 = AR5416DESC_CONST(ds0)->ds_ctl2;
	ads->ds_ctl3 = AR5416DESC_CONST(ds0)->ds_ctl3;
#endif
	return AH_TRUE;
}