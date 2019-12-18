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
typedef  size_t u_int ;
struct netmap_kring {size_t nkr_num_slots; size_t nr_hwtail; size_t nr_hwcur; int /*<<< orphan*/  tx_event_lock; int /*<<< orphan*/ * tx_event; struct mbuf** tx_pool; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 scalar_t__ MBUF_QUEUED (struct mbuf*) ; 
 int MBUF_REFCNT (struct mbuf*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 size_t nm_next (size_t,size_t const) ; 
 int /*<<< orphan*/  nm_prdis (char*,size_t,size_t) ; 
 size_t nm_prev (size_t,size_t const) ; 
 int /*<<< orphan*/  nm_prlim (int,char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int
generic_netmap_tx_clean(struct netmap_kring *kring, int txqdisc)
{
	u_int const lim = kring->nkr_num_slots - 1;
	u_int nm_i = nm_next(kring->nr_hwtail, lim);
	u_int hwcur = kring->nr_hwcur;
	u_int n = 0;
	struct mbuf **tx_pool = kring->tx_pool;

	nm_prdis("hwcur = %d, hwtail = %d", kring->nr_hwcur, kring->nr_hwtail);

	while (nm_i != hwcur) { /* buffers not completed */
		struct mbuf *m = tx_pool[nm_i];

		if (txqdisc) {
			if (m == NULL) {
				/* Nothing to do, this is going
				 * to be replenished. */
				nm_prlim(3, "Is this happening?");

			} else if (MBUF_QUEUED(m)) {
				break; /* Not dequeued yet. */

			} else if (MBUF_REFCNT(m) != 1) {
				/* This mbuf has been dequeued but is still busy
				 * (refcount is 2).
				 * Leave it to the driver and replenish. */
				m_freem(m);
				tx_pool[nm_i] = NULL;
			}

		} else {
			if (unlikely(m == NULL)) {
				int event_consumed;

				/* This slot was used to place an event. */
				mtx_lock_spin(&kring->tx_event_lock);
				event_consumed = (kring->tx_event == NULL);
				mtx_unlock_spin(&kring->tx_event_lock);
				if (!event_consumed) {
					/* The event has not been consumed yet,
					 * still busy in the driver. */
					break;
				}
				/* The event has been consumed, we can go
				 * ahead. */

			} else if (MBUF_REFCNT(m) != 1) {
				/* This mbuf is still busy: its refcnt is 2. */
				break;
			}
		}

		n++;
		nm_i = nm_next(nm_i, lim);
	}
	kring->nr_hwtail = nm_prev(nm_i, lim);
	nm_prdis("tx completed [%d] -> hwtail %d", n, kring->nr_hwtail);

	return n;
}