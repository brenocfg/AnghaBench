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
typedef  int /*<<< orphan*/  u_int ;
struct ath_hal {int dummy; } ;
struct ath_desc {int dummy; } ;
struct ar9300_txc {int /*<<< orphan*/  ds_ctl13; } ;

/* Variables and functions */
 struct ar9300_txc* AR9300TXC (struct ath_desc*) ; 
 int /*<<< orphan*/  AR_burst_dur ; 
 int /*<<< orphan*/  SM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ar9300_set_11n_burst_duration(struct ath_hal *ah, struct ath_desc *ds,
    u_int burst_duration)
{
    struct ar9300_txc *ads = AR9300TXC(ds);

    ads->ds_ctl13 &= ~AR_burst_dur;
    ads->ds_ctl13 |= SM(burst_duration, AR_burst_dur);
}