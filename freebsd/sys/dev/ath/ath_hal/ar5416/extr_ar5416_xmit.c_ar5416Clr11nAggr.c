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
struct ar5416_desc {int ds_ctl1; int /*<<< orphan*/  ds_ctl6; } ;

/* Variables and functions */
 struct ar5416_desc* AR5416DESC (struct ath_desc*) ; 
 int /*<<< orphan*/  AR_AggrLen ; 
 int AR_IsAggr ; 
 int AR_MoreAggr ; 
 int /*<<< orphan*/  AR_PadDelim ; 

void
ar5416Clr11nAggr(struct ath_hal *ah, struct ath_desc *ds)
{
	struct ar5416_desc *ads = AR5416DESC(ds);

	ads->ds_ctl1 &= (~AR_IsAggr & ~AR_MoreAggr);
	ads->ds_ctl6 &= ~AR_PadDelim;
	ads->ds_ctl6 &= ~AR_AggrLen;
}