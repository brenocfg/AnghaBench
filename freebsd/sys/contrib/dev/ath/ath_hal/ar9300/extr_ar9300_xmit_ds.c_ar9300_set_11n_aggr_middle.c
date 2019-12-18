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
struct ar9300_txc {int ds_ctl12; unsigned int ds_ctl17; } ;

/* Variables and functions */
 struct ar9300_txc* AR9300TXC (struct ath_desc*) ; 
 int AR_is_aggr ; 
 int AR_more_aggr ; 
 unsigned int AR_pad_delim ; 
 unsigned int SM (int /*<<< orphan*/ ,unsigned int) ; 

void
ar9300_set_11n_aggr_middle(struct ath_hal *ah, struct ath_desc *ds,
  u_int num_delims)
{
    struct ar9300_txc *ads = AR9300TXC(ds);
    unsigned int ctl17;

    ads->ds_ctl12 |= (AR_is_aggr | AR_more_aggr);

    /*
     * We use a stack variable to manipulate ctl6 to reduce uncached
     * read modify, modfiy, write.
     */
    ctl17 = ads->ds_ctl17;
    ctl17 &= ~AR_pad_delim;
    ctl17 |= SM(num_delims, AR_pad_delim);
    ads->ds_ctl17 = ctl17;
}