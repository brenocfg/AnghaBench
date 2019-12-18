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
typedef  int /*<<< orphan*/  u_int32_t ;
struct ath_hal_9300 {size_t ts_tail; struct ar9300_txs* ts_ring; } ;
struct ath_hal {int dummy; } ;
struct ar9300_txs {int dummy; } ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 
 int /*<<< orphan*/  OS_MEMCPY (int /*<<< orphan*/ *,struct ar9300_txs*,int) ; 

void
ar9300_get_raw_tx_desc(struct ath_hal *ah, u_int32_t *txstatus)
{
    struct ath_hal_9300 *ahp = AH9300(ah);
    struct ar9300_txs *ads;

    ads = &ahp->ts_ring[ahp->ts_tail];

    OS_MEMCPY(txstatus, ads, sizeof(struct ar9300_txs));
}