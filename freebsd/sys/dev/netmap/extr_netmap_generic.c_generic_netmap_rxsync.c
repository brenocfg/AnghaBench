#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct netmap_slot {int flags; int len; } ;
struct netmap_ring {struct netmap_slot* slot; } ;
struct mbq {int dummy; } ;
struct netmap_kring {scalar_t__ nkr_num_slots; scalar_t__ rhead; int nr_kflags; scalar_t__ nr_hwcur; scalar_t__ nr_hwtail; struct mbq rx_queue; struct netmap_adapter* na; struct netmap_ring* ring; } ;
struct netmap_adapter {int dummy; } ;
struct mbuf {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  rxpkt; int /*<<< orphan*/  rxsync; } ;
struct TYPE_4__ {TYPE_1__ new; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFRATE (scalar_t__) ; 
 int MBUF_LEN (struct mbuf*) ; 
 int NAF_FORCE_READ ; 
 void* NETMAP_BUF_BASE (struct netmap_adapter*) ; 
 scalar_t__ NETMAP_BUF_SIZE (struct netmap_adapter*) ; 
 int NKR_PENDINTR ; 
 void* NMB (struct netmap_adapter*,struct netmap_slot*) ; 
 int NS_BUF_CHANGED ; 
 int NS_MOREFRAG ; 
 int /*<<< orphan*/  m_copydata (struct mbuf*,int,int,void*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct mbuf* mbq_dequeue (struct mbq*) ; 
 int /*<<< orphan*/  mbq_enqueue (struct mbq*,struct mbuf*) ; 
 int /*<<< orphan*/  mbq_fini (struct mbq*) ; 
 int /*<<< orphan*/  mbq_init (struct mbq*) ; 
 int /*<<< orphan*/  mbq_lock (struct mbq*) ; 
 struct mbuf* mbq_peek (struct mbq*) ; 
 int /*<<< orphan*/  mbq_purge (struct mbq*) ; 
 int /*<<< orphan*/  mbq_unlock (struct mbq*) ; 
 int /*<<< orphan*/  netmap_no_pendintr ; 
 int netmap_ring_reinit (struct netmap_kring*) ; 
 scalar_t__ nm_next (scalar_t__,scalar_t__ const) ; 
 scalar_t__ nm_prev (scalar_t__,scalar_t__ const) ; 
 TYPE_2__ rate_ctx ; 

__attribute__((used)) static int
generic_netmap_rxsync(struct netmap_kring *kring, int flags)
{
	struct netmap_ring *ring = kring->ring;
	struct netmap_adapter *na = kring->na;
	u_int nm_i;	/* index into the netmap ring */ //j,
	u_int n;
	u_int const lim = kring->nkr_num_slots - 1;
	u_int const head = kring->rhead;
	int force_update = (flags & NAF_FORCE_READ) || kring->nr_kflags & NKR_PENDINTR;

	/* Adapter-specific variables. */
	u_int nm_buf_len = NETMAP_BUF_SIZE(na);
	struct mbq tmpq;
	struct mbuf *m;
	int avail; /* in bytes */
	int mlen;
	int copy;

	if (head > lim)
		return netmap_ring_reinit(kring);

	IFRATE(rate_ctx.new.rxsync++);

	/*
	 * First part: skip past packets that userspace has released.
	 * This can possibly make room for the second part.
	 */
	nm_i = kring->nr_hwcur;
	if (nm_i != head) {
		/* Userspace has released some packets. */
		for (n = 0; nm_i != head; n++) {
			struct netmap_slot *slot = &ring->slot[nm_i];

			slot->flags &= ~NS_BUF_CHANGED;
			nm_i = nm_next(nm_i, lim);
		}
		kring->nr_hwcur = head;
	}

	/*
	 * Second part: import newly received packets.
	 */
	if (!netmap_no_pendintr && !force_update) {
		return 0;
	}

	nm_i = kring->nr_hwtail; /* First empty slot in the receive ring. */

	/* Compute the available space (in bytes) in this netmap ring.
	 * The first slot that is not considered in is the one before
	 * nr_hwcur. */

	avail = nm_prev(kring->nr_hwcur, lim) - nm_i;
	if (avail < 0)
		avail += lim + 1;
	avail *= nm_buf_len;

	/* First pass: While holding the lock on the RX mbuf queue,
	 * extract as many mbufs as they fit the available space,
	 * and put them in a temporary queue.
	 * To avoid performing a per-mbuf division (mlen / nm_buf_len) to
	 * to update avail, we do the update in a while loop that we
	 * also use to set the RX slots, but without performing the copy. */
	mbq_init(&tmpq);
	mbq_lock(&kring->rx_queue);
	for (n = 0;; n++) {
		m = mbq_peek(&kring->rx_queue);
		if (!m) {
			/* No more packets from the driver. */
			break;
		}

		mlen = MBUF_LEN(m);
		if (mlen > avail) {
			/* No more space in the ring. */
			break;
		}

		mbq_dequeue(&kring->rx_queue);

		while (mlen) {
			copy = nm_buf_len;
			if (mlen < copy) {
				copy = mlen;
			}
			mlen -= copy;
			avail -= nm_buf_len;

			ring->slot[nm_i].len = copy;
			ring->slot[nm_i].flags = (mlen ? NS_MOREFRAG : 0);
			nm_i = nm_next(nm_i, lim);
		}

		mbq_enqueue(&tmpq, m);
	}
	mbq_unlock(&kring->rx_queue);

	/* Second pass: Drain the temporary queue, going over the used RX slots,
	 * and perform the copy out of the RX queue lock. */
	nm_i = kring->nr_hwtail;

	for (;;) {
		void *nmaddr;
		int ofs = 0;
		int morefrag;

		m = mbq_dequeue(&tmpq);
		if (!m)	{
			break;
		}

		do {
			nmaddr = NMB(na, &ring->slot[nm_i]);
			/* We only check the address here on generic rx rings. */
			if (nmaddr == NETMAP_BUF_BASE(na)) { /* Bad buffer */
				m_freem(m);
				mbq_purge(&tmpq);
				mbq_fini(&tmpq);
				return netmap_ring_reinit(kring);
			}

			copy = ring->slot[nm_i].len;
			m_copydata(m, ofs, copy, nmaddr);
			ofs += copy;
			morefrag = ring->slot[nm_i].flags & NS_MOREFRAG;
			nm_i = nm_next(nm_i, lim);
		} while (morefrag);

		m_freem(m);
	}

	mbq_fini(&tmpq);

	if (n) {
		kring->nr_hwtail = nm_i;
		IFRATE(rate_ctx.new.rxpkt += n);
	}
	kring->nr_kflags &= ~NKR_PENDINTR;

	return 0;
}