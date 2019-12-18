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
struct ar9300_txc {int /*<<< orphan*/  ds_ctl17; int /*<<< orphan*/  ds_ctl12; } ;

/* Variables and functions */
 struct ar9300_txc* AR9300TXC (struct ath_desc*) ; 
 int /*<<< orphan*/  AR_is_aggr ; 
 int /*<<< orphan*/  AR_more_aggr ; 
 int /*<<< orphan*/  AR_pad_delim ; 

void
ar9300_set_11n_aggr_last(struct ath_hal *ah, struct ath_desc *ds)
{
    struct ar9300_txc *ads = AR9300TXC(ds);

    ads->ds_ctl12 |= AR_is_aggr;
    ads->ds_ctl12 &= ~AR_more_aggr;
    ads->ds_ctl17 &= ~AR_pad_delim;
}