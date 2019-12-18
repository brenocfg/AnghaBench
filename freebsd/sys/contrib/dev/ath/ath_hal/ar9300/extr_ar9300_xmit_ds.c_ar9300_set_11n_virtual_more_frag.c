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
typedef  scalar_t__ u_int ;
struct ath_hal {int dummy; } ;
struct ath_desc {int dummy; } ;
struct ar9300_txc {int /*<<< orphan*/  ds_ctl11; } ;

/* Variables and functions */
 struct ar9300_txc* AR9300TXC (struct ath_desc*) ; 
 int /*<<< orphan*/  AR_virt_more_frag ; 

void
ar9300_set_11n_virtual_more_frag(struct ath_hal *ah, struct ath_desc *ds,
                                                  u_int vmf)
{
    struct ar9300_txc *ads = AR9300TXC(ds);

    if (vmf) {
        ads->ds_ctl11 |=  AR_virt_more_frag;
    } else {
        ads->ds_ctl11 &= ~AR_virt_more_frag;
    }
}