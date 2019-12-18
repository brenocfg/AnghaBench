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
struct ar5416_desc {int /*<<< orphan*/  ds_ctl6; int /*<<< orphan*/  ds_ctl1; } ;

/* Variables and functions */
 struct ar5416_desc* AR5416DESC (struct ath_desc*) ; 
 int /*<<< orphan*/  AR_IsAggr ; 
 int /*<<< orphan*/  AR_MoreAggr ; 
 int /*<<< orphan*/  AR_PadDelim ; 

void
ar5416Set11nAggrLast(struct ath_hal *ah, struct ath_desc *ds)
{
	struct ar5416_desc *ads = AR5416DESC(ds);

	ads->ds_ctl1 |= AR_IsAggr;
	ads->ds_ctl1 &= ~AR_MoreAggr;
	ads->ds_ctl6 &= ~AR_PadDelim;
}