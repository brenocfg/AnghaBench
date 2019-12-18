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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_int ;
struct ath_hal {int dummy; } ;
struct ath_desc {int dummy; } ;
struct ar5416_desc {int ds_ctl1; int /*<<< orphan*/  ds_ctl6; } ;

/* Variables and functions */
 struct ar5416_desc* AR5416DESC (struct ath_desc*) ; 
 int /*<<< orphan*/ * AR5416_DS_TXSTATUS (struct ath_hal*,struct ar5416_desc*) ; 
 int /*<<< orphan*/  AR_AggrLen ; 
 int AR_IsAggr ; 
 int AR_MoreAggr ; 
 int /*<<< orphan*/  AR_PadDelim ; 
 int /*<<< orphan*/  AR_TxDone ; 
 int /*<<< orphan*/  SM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ar5416Set11nAggrMiddle(struct ath_hal *ah, struct ath_desc *ds, u_int numDelims)
{
	struct ar5416_desc *ads = AR5416DESC(ds);
	uint32_t *ds_txstatus = AR5416_DS_TXSTATUS(ah,ads);

	ads->ds_ctl1 |= (AR_IsAggr | AR_MoreAggr);

	ads->ds_ctl6 &= ~AR_PadDelim;
	ads->ds_ctl6 |= SM(numDelims, AR_PadDelim);
	ads->ds_ctl6 &= ~AR_AggrLen;

	/*
	 * Clear the TxDone status here, may need to change
	 * func name to reflect this
	 */
	ds_txstatus[9] &= ~AR_TxDone;
}