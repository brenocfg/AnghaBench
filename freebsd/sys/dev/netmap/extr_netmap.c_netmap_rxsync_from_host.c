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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ u_int ;
struct netmap_slot {int len; scalar_t__ flags; } ;
struct netmap_ring {struct netmap_slot* slot; } ;
struct mbq {int dummy; } ;
struct netmap_kring {scalar_t__ nkr_num_slots; scalar_t__ rhead; scalar_t__ nr_hwtail; scalar_t__ nr_hwcur; int /*<<< orphan*/  nr_kflags; struct mbq rx_queue; struct netmap_ring* ring; struct netmap_adapter* na; } ;
struct netmap_adapter {int dummy; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int MBUF_LEN (struct mbuf*) ; 
 int /*<<< orphan*/  NMB (struct netmap_adapter*,struct netmap_slot*) ; 
 int NM_DEBUG_HOST ; 
 int /*<<< orphan*/  NR_FORWARD ; 
 int /*<<< orphan*/  m_copydata (struct mbuf*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct mbuf* mbq_dequeue (struct mbq*) ; 
 int /*<<< orphan*/  mbq_enqueue (struct mbq*,struct mbuf*) ; 
 int /*<<< orphan*/  mbq_fini (struct mbq*) ; 
 int /*<<< orphan*/  mbq_init (struct mbq*) ; 
 scalar_t__ mbq_len (struct mbq*) ; 
 int /*<<< orphan*/  mbq_lock (struct mbq*) ; 
 int /*<<< orphan*/  mbq_purge (struct mbq*) ; 
 int /*<<< orphan*/  mbq_unlock (struct mbq*) ; 
 int netmap_debug ; 
 int netmap_sw_to_nic (struct netmap_adapter*) ; 
 int /*<<< orphan*/  nm_dump_buf (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ nm_may_forward_down (struct netmap_kring*,int) ; 
 scalar_t__ nm_next (scalar_t__,scalar_t__ const) ; 
 int /*<<< orphan*/  nm_prdis (char*,scalar_t__,int) ; 
 scalar_t__ nm_prev (scalar_t__,scalar_t__ const) ; 
 int /*<<< orphan*/  nm_prinf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
netmap_rxsync_from_host(struct netmap_kring *kring, int flags)
{
	struct netmap_adapter *na = kring->na;
	struct netmap_ring *ring = kring->ring;
	u_int nm_i, n;
	u_int const lim = kring->nkr_num_slots - 1;
	u_int const head = kring->rhead;
	int ret = 0;
	struct mbq *q = &kring->rx_queue, fq;

	mbq_init(&fq); /* fq holds packets to be freed */

	mbq_lock(q);

	/* First part: import newly received packets */
	n = mbq_len(q);
	if (n) { /* grab packets from the queue */
		struct mbuf *m;
		uint32_t stop_i;

		nm_i = kring->nr_hwtail;
		stop_i = nm_prev(kring->nr_hwcur, lim);
		while ( nm_i != stop_i && (m = mbq_dequeue(q)) != NULL ) {
			int len = MBUF_LEN(m);
			struct netmap_slot *slot = &ring->slot[nm_i];

			m_copydata(m, 0, len, NMB(na, slot));
			nm_prdis("nm %d len %d", nm_i, len);
			if (netmap_debug & NM_DEBUG_HOST)
				nm_prinf("%s", nm_dump_buf(NMB(na, slot),len, 128, NULL));

			slot->len = len;
			slot->flags = 0;
			nm_i = nm_next(nm_i, lim);
			mbq_enqueue(&fq, m);
		}
		kring->nr_hwtail = nm_i;
	}

	/*
	 * Second part: skip past packets that userspace has released.
	 */
	nm_i = kring->nr_hwcur;
	if (nm_i != head) { /* something was released */
		if (nm_may_forward_down(kring, flags)) {
			ret = netmap_sw_to_nic(na);
			if (ret > 0) {
				kring->nr_kflags |= NR_FORWARD;
				ret = 0;
			}
		}
		kring->nr_hwcur = head;
	}

	mbq_unlock(q);

	mbq_purge(&fq);
	mbq_fini(&fq);

	return ret;
}