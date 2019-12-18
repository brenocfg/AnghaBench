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
struct ath_tx_status {int ts_finaltsi; void* ts_rate; } ;
struct ath_hal {int dummy; } ;
struct ar9300_txc {int /*<<< orphan*/  ds_ctl14; } ;

/* Variables and functions */
 struct ar9300_txc* AR9300TXC (void*) ; 
 int /*<<< orphan*/  AR_xmit_rate0 ; 
 int /*<<< orphan*/  AR_xmit_rate1 ; 
 int /*<<< orphan*/  AR_xmit_rate2 ; 
 int /*<<< orphan*/  AR_xmit_rate3 ; 
 void* MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9300_set_selfgenrate_limit (struct ath_hal*,void*) ; 

void
ar9300_get_tx_rate_code(struct ath_hal *ah, void *ds, struct ath_tx_status *ts)
{
    struct ar9300_txc *ads = AR9300TXC(ds);

    switch (ts->ts_finaltsi) {
    case 0:
        ts->ts_rate = MS(ads->ds_ctl14, AR_xmit_rate0);
        break;
    case 1:
        ts->ts_rate = MS(ads->ds_ctl14, AR_xmit_rate1);
        break;
    case 2:
        ts->ts_rate = MS(ads->ds_ctl14, AR_xmit_rate2);
        break;
    case 3:
        ts->ts_rate = MS(ads->ds_ctl14, AR_xmit_rate3);
        break;
    }

    ar9300_set_selfgenrate_limit(ah, ts->ts_rate);
}