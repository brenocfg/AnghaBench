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
struct ar9300_txc {int /*<<< orphan*/  ds_ctl12; } ;

/* Variables and functions */
 struct ar9300_txc* AR9300TXC (void*) ; 
 int /*<<< orphan*/  AR_paprd_chain_mask ; 
 int /*<<< orphan*/  SM (int,int /*<<< orphan*/ ) ; 

void
ar9300_set_paprd_tx_desc(struct ath_hal *ah, void *ds, int chain_num)
{
    struct ar9300_txc *ads = AR9300TXC(ds);

    ads->ds_ctl12 |= SM((1 << chain_num), AR_paprd_chain_mask);
}