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
struct netmap_kring {int /*<<< orphan*/  tx_event_lock; struct mbuf* tx_event; } ;
struct netmap_adapter {unsigned int num_tx_rings; struct netmap_kring** tx_rings; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN_TX_MBUF_IFP (struct mbuf*) ; 
 unsigned int MBUF_TXQ (struct mbuf*) ; 
 struct netmap_adapter* NA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netmap_generic_irq (struct netmap_adapter*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nm_netmap_on (struct netmap_adapter*) ; 
 int /*<<< orphan*/  nm_prerr (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nm_prlim (int,char*,struct mbuf*,...) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  void_mbuf_dtor (struct mbuf*,...) ; 

__attribute__((used)) static void
generic_mbuf_destructor(struct mbuf *m)
{
	struct netmap_adapter *na = NA(GEN_TX_MBUF_IFP(m));
	struct netmap_kring *kring;
	unsigned int r = MBUF_TXQ(m);
	unsigned int r_orig = r;

	if (unlikely(!nm_netmap_on(na) || r >= na->num_tx_rings)) {
		nm_prerr("Error: no netmap adapter on device %p",
		  GEN_TX_MBUF_IFP(m));
		return;
	}

	/*
	 * First, clear the event mbuf.
	 * In principle, the event 'm' should match the one stored
	 * on ring 'r'. However we check it explicitely to stay
	 * safe against lower layers (qdisc, driver, etc.) changing
	 * MBUF_TXQ(m) under our feet. If the match is not found
	 * on 'r', we try to see if it belongs to some other ring.
	 */
	for (;;) {
		bool match = false;

		kring = na->tx_rings[r];
		mtx_lock_spin(&kring->tx_event_lock);
		if (kring->tx_event == m) {
			kring->tx_event = NULL;
			match = true;
		}
		mtx_unlock_spin(&kring->tx_event_lock);

		if (match) {
			if (r != r_orig) {
				nm_prlim(1, "event %p migrated: ring %u --> %u",
				      m, r_orig, r);
			}
			break;
		}

		if (++r == na->num_tx_rings) r = 0;

		if (r == r_orig) {
			nm_prlim(1, "Cannot match event %p", m);
			return;
		}
	}

	/* Second, wake up clients. They will reclaim the event through
	 * txsync. */
	netmap_generic_irq(na, r, NULL);
#ifdef __FreeBSD__
#if __FreeBSD_version <= 1200050
	void_mbuf_dtor(m, NULL, NULL);
#else  /* __FreeBSD_version >= 1200051 */
	void_mbuf_dtor(m);
#endif /* __FreeBSD_version >= 1200051 */
#endif
}