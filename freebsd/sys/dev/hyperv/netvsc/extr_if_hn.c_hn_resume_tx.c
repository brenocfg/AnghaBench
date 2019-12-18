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
struct hn_tx_ring {int /*<<< orphan*/  hn_tx_lock; scalar_t__ hn_suspended; } ;
struct hn_softc {int hn_tx_ring_cnt; struct hn_tx_ring* hn_tx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
hn_resume_tx(struct hn_softc *sc, int tx_ring_cnt)
{
	int i;

	KASSERT(tx_ring_cnt <= sc->hn_tx_ring_cnt,
	    ("invalid TX ring count %d", tx_ring_cnt));

	for (i = 0; i < tx_ring_cnt; ++i) {
		struct hn_tx_ring *txr = &sc->hn_tx_ring[i];

		mtx_lock(&txr->hn_tx_lock);
		txr->hn_suspended = 0;
		mtx_unlock(&txr->hn_tx_lock);
	}
}