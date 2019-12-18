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
struct ar9300_txs {scalar_t__ status8; scalar_t__ status7; scalar_t__ status6; scalar_t__ status5; scalar_t__ status4; scalar_t__ status3; scalar_t__ status2; scalar_t__ status1; } ;

/* Variables and functions */
 struct ar9300_txs* AR9300TXS (void*) ; 

void
ar9300_clear_tx_desc_status(struct ath_hal *ah, void *ds)
{
    struct ar9300_txs *ads = AR9300TXS(ds);
    ads->status1 = ads->status2 = 0;
    ads->status3 = ads->status4 = 0;
    ads->status5 = ads->status6 = 0;
    ads->status7 = ads->status8 = 0;
}