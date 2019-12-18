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
struct netmap_kring {size_t nkr_num_slots; struct mbuf** tx_pool; int /*<<< orphan*/  tx_event_lock; struct mbuf* tx_event; int /*<<< orphan*/  nr_hwtail; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int MBUF_REFCNT (struct mbuf*) ; 
 int /*<<< orphan*/  SET_MBUF_DESTRUCTOR (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_mbuf_destructor ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 size_t nm_next (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  nm_prdis (char*,size_t,struct mbuf*,int) ; 
 size_t ring_middle (size_t,size_t,size_t) ; 
 int /*<<< orphan*/  smp_mb () ; 

__attribute__((used)) static void
generic_set_tx_event(struct netmap_kring *kring, u_int hwcur)
{
	u_int lim = kring->nkr_num_slots - 1;
	struct mbuf *m;
	u_int e;
	u_int ntc = nm_next(kring->nr_hwtail, lim); /* next to clean */

	if (ntc == hwcur) {
		return; /* all buffers are free */
	}

	/*
	 * We have pending packets in the driver between hwtail+1
	 * and hwcur, and we have to chose one of these slot to
	 * generate a notification.
	 * There is a race but this is only called within txsync which
	 * does a double check.
	 */
#if 0
	/* Choose a slot in the middle, so that we don't risk ending
	 * up in a situation where the client continuously wake up,
	 * fills one or a few TX slots and go to sleep again. */
	e = ring_middle(ntc, hwcur, lim);
#else
	/* Choose the first pending slot, to be safe against driver
	 * reordering mbuf transmissions. */
	e = ntc;
#endif

	m = kring->tx_pool[e];
	if (m == NULL) {
		/* An event is already in place. */
		return;
	}

	mtx_lock_spin(&kring->tx_event_lock);
	if (kring->tx_event) {
		/* An event is already in place. */
		mtx_unlock_spin(&kring->tx_event_lock);
		return;
	}

	SET_MBUF_DESTRUCTOR(m, generic_mbuf_destructor);
	kring->tx_event = m;
	mtx_unlock_spin(&kring->tx_event_lock);

	kring->tx_pool[e] = NULL;

	nm_prdis("Request Event at %d mbuf %p refcnt %d", e, m, m ? MBUF_REFCNT(m) : -2 );

	/* Decrement the refcount. This will free it if we lose the race
	 * with the driver. */
	m_freem(m);
	smp_mb();
}