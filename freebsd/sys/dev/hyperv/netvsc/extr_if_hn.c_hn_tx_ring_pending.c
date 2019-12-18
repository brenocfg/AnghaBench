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
struct hn_tx_ring {scalar_t__ hn_txdesc_avail; scalar_t__ hn_txdesc_cnt; int /*<<< orphan*/  hn_txdesc_br; int /*<<< orphan*/  hn_txlist_spin; } ;

/* Variables and functions */
 int /*<<< orphan*/  buf_ring_full (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
hn_tx_ring_pending(struct hn_tx_ring *txr)
{
	bool pending = false;

#ifndef HN_USE_TXDESC_BUFRING
	mtx_lock_spin(&txr->hn_txlist_spin);
	if (txr->hn_txdesc_avail != txr->hn_txdesc_cnt)
		pending = true;
	mtx_unlock_spin(&txr->hn_txlist_spin);
#else
	if (!buf_ring_full(txr->hn_txdesc_br))
		pending = true;
#endif
	return (pending);
}