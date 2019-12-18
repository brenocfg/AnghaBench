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
typedef  void* u_int32_t ;
typedef  int u_int16_t ;
struct ath_hal_9300 {int ts_size; struct ar9300_txs* ts_ring; void* ts_paddr_end; void* ts_paddr_start; } ;
struct ath_hal {int dummy; } ;
struct ar9300_txs {int dummy; } ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 
 int /*<<< orphan*/  ar9300_reset_tx_status_ring (struct ath_hal*) ; 

void
ar9300_setup_tx_status_ring(struct ath_hal *ah, void *ts_start,
    u_int32_t ts_paddr_start, u_int16_t size)
{
    struct ath_hal_9300 *ahp = AH9300(ah);

    ahp->ts_paddr_start = ts_paddr_start;
    ahp->ts_paddr_end = ts_paddr_start + (size * sizeof(struct ar9300_txs));
    ahp->ts_size = size;
    ahp->ts_ring = (struct ar9300_txs *)ts_start;

    ar9300_reset_tx_status_ring(ah);
}