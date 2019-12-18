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
struct netmap_ring {scalar_t__ cur; scalar_t__ tail; scalar_t__ head; } ;
struct netmap_priv_d {int np_sync_flags; int np_csb_atok_base; size_t* np_qfirst; size_t* np_qlast; scalar_t__ np_txpoll; int /*<<< orphan*/ ** np_si; struct netmap_adapter* np_na; int /*<<< orphan*/ * np_nifp; } ;
struct netmap_kring {scalar_t__ rhead; scalar_t__ nr_hwcur; scalar_t__ nkr_num_slots; scalar_t__ rcur; scalar_t__ rtail; int nr_kflags; int /*<<< orphan*/  (* nm_notify ) (struct netmap_kring*,int /*<<< orphan*/ ) ;scalar_t__ (* nm_sync ) (struct netmap_kring*,int) ;struct netmap_ring* ring; } ;
struct netmap_adapter {int /*<<< orphan*/  ifp; struct netmap_kring** rx_rings; struct netmap_kring** tx_rings; int /*<<< orphan*/  name; } ;
struct mbq {int dummy; } ;
typedef  enum txrx { ____Placeholder_txrx } txrx ;
typedef  int /*<<< orphan*/  NM_SELRECORD_T ;
typedef  int /*<<< orphan*/  NM_SELINFO_T ;

/* Variables and functions */
 struct netmap_kring** NMR (struct netmap_adapter*,int const) ; 
 int NM_DEBUG_ON ; 
 int NR_FORWARD ; 
 size_t NR_RX ; 
 size_t NR_TX ; 
 int NR_TXRX ; 
 int POLLERR ; 
 int POLLIN ; 
 int POLLOUT ; 
 int POLLRDNORM ; 
 int POLLWRNORM ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  mbq_init (struct mbq*) ; 
 scalar_t__ mbq_peek (struct mbq*) ; 
 int netmap_debug ; 
 int /*<<< orphan*/  netmap_fwd ; 
 int /*<<< orphan*/  netmap_grab_packets (struct netmap_kring*,struct mbq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netmap_ring_reinit (struct netmap_kring*) ; 
 int /*<<< orphan*/  netmap_send_up (int /*<<< orphan*/ ,struct mbq*) ; 
 int /*<<< orphan*/  nm_kr_put (struct netmap_kring*) ; 
 int nm_kr_tryget (struct netmap_kring*,int,size_t*) ; 
 scalar_t__ nm_may_forward_up (struct netmap_kring*) ; 
 int /*<<< orphan*/  nm_netmap_on (struct netmap_adapter*) ; 
 int /*<<< orphan*/  nm_os_selrecord (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nm_prerr (char*) ; 
 int /*<<< orphan*/  nm_prinf (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nm_rxsync_prologue (struct netmap_kring*,struct netmap_ring*) ; 
 int /*<<< orphan*/  nm_sync_finalize (struct netmap_kring*) ; 
 scalar_t__ nm_txsync_prologue (struct netmap_kring*,struct netmap_ring*) ; 
 int /*<<< orphan*/  ring_timestamp_set (struct netmap_ring*) ; 
 scalar_t__ stub1 (struct netmap_kring*,int) ; 
 int /*<<< orphan*/  stub2 (struct netmap_kring*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 (struct netmap_kring*,int) ; 
 int /*<<< orphan*/  stub4 (struct netmap_kring*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int want_rx ; 
 int want_tx ; 

int
netmap_poll(struct netmap_priv_d *priv, int events, NM_SELRECORD_T *sr)
{
	struct netmap_adapter *na;
	struct netmap_kring *kring;
	struct netmap_ring *ring;
	u_int i, want[NR_TXRX], revents = 0;
	NM_SELINFO_T *si[NR_TXRX];
#define want_tx want[NR_TX]
#define want_rx want[NR_RX]
	struct mbq q;	/* packets from RX hw queues to host stack */

	/*
	 * In order to avoid nested locks, we need to "double check"
	 * txsync and rxsync if we decide to do a selrecord().
	 * retry_tx (and retry_rx, later) prevent looping forever.
	 */
	int retry_tx = 1, retry_rx = 1;

	/* Transparent mode: send_down is 1 if we have found some
	 * packets to forward (host RX ring --> NIC) during the rx
	 * scan and we have not sent them down to the NIC yet.
	 * Transparent mode requires to bind all rings to a single
	 * file descriptor.
	 */
	int send_down = 0;
	int sync_flags = priv->np_sync_flags;

	mbq_init(&q);

	if (unlikely(priv->np_nifp == NULL)) {
		return POLLERR;
	}
	mb(); /* make sure following reads are not from cache */

	na = priv->np_na;

	if (unlikely(!nm_netmap_on(na)))
		return POLLERR;

	if (unlikely(priv->np_csb_atok_base)) {
		nm_prerr("Invalid poll in CSB mode");
		return POLLERR;
	}

	if (netmap_debug & NM_DEBUG_ON)
		nm_prinf("device %s events 0x%x", na->name, events);
	want_tx = events & (POLLOUT | POLLWRNORM);
	want_rx = events & (POLLIN | POLLRDNORM);

	/*
	 * If the card has more than one queue AND the file descriptor is
	 * bound to all of them, we sleep on the "global" selinfo, otherwise
	 * we sleep on individual selinfo (FreeBSD only allows two selinfo's
	 * per file descriptor).
	 * The interrupt routine in the driver wake one or the other
	 * (or both) depending on which clients are active.
	 *
	 * rxsync() is only called if we run out of buffers on a POLLIN.
	 * txsync() is called if we run out of buffers on POLLOUT, or
	 * there are pending packets to send. The latter can be disabled
	 * passing NETMAP_NO_TX_POLL in the NIOCREG call.
	 */
	si[NR_RX] = priv->np_si[NR_RX];
	si[NR_TX] = priv->np_si[NR_TX];

#ifdef __FreeBSD__
	/*
	 * We start with a lock free round which is cheap if we have
	 * slots available. If this fails, then lock and call the sync
	 * routines. We can't do this on Linux, as the contract says
	 * that we must call nm_os_selrecord() unconditionally.
	 */
	if (want_tx) {
		const enum txrx t = NR_TX;
		for (i = priv->np_qfirst[t]; i < priv->np_qlast[t]; i++) {
			kring = NMR(na, t)[i];
			if (kring->ring->cur != kring->ring->tail) {
				/* Some unseen TX space is available, so what
				 * we don't need to run txsync. */
				revents |= want[t];
				want[t] = 0;
				break;
			}
		}
	}
	if (want_rx) {
		const enum txrx t = NR_RX;
		int rxsync_needed = 0;

		for (i = priv->np_qfirst[t]; i < priv->np_qlast[t]; i++) {
			kring = NMR(na, t)[i];
			if (kring->ring->cur == kring->ring->tail
				|| kring->rhead != kring->ring->head) {
				/* There are no unseen packets on this ring,
				 * or there are some buffers to be returned
				 * to the netmap port. We therefore go ahead
				 * and run rxsync. */
				rxsync_needed = 1;
				break;
			}
		}
		if (!rxsync_needed) {
			revents |= want_rx;
			want_rx = 0;
		}
	}
#endif

#ifdef linux
	/* The selrecord must be unconditional on linux. */
	nm_os_selrecord(sr, si[NR_RX]);
	nm_os_selrecord(sr, si[NR_TX]);
#endif /* linux */

	/*
	 * If we want to push packets out (priv->np_txpoll) or
	 * want_tx is still set, we must issue txsync calls
	 * (on all rings, to avoid that the tx rings stall).
	 * Fortunately, normal tx mode has np_txpoll set.
	 */
	if (priv->np_txpoll || want_tx) {
		/*
		 * The first round checks if anyone is ready, if not
		 * do a selrecord and another round to handle races.
		 * want_tx goes to 0 if any space is found, and is
		 * used to skip rings with no pending transmissions.
		 */
flush_tx:
		for (i = priv->np_qfirst[NR_TX]; i < priv->np_qlast[NR_TX]; i++) {
			int found = 0;

			kring = na->tx_rings[i];
			ring = kring->ring;

			/*
			 * Don't try to txsync this TX ring if we already found some
			 * space in some of the TX rings (want_tx == 0) and there are no
			 * TX slots in this ring that need to be flushed to the NIC
			 * (head == hwcur).
			 */
			if (!send_down && !want_tx && ring->head == kring->nr_hwcur)
				continue;

			if (nm_kr_tryget(kring, 1, &revents))
				continue;

			if (nm_txsync_prologue(kring, ring) >= kring->nkr_num_slots) {
				netmap_ring_reinit(kring);
				revents |= POLLERR;
			} else {
				if (kring->nm_sync(kring, sync_flags))
					revents |= POLLERR;
				else
					nm_sync_finalize(kring);
			}

			/*
			 * If we found new slots, notify potential
			 * listeners on the same ring.
			 * Since we just did a txsync, look at the copies
			 * of cur,tail in the kring.
			 */
			found = kring->rcur != kring->rtail;
			nm_kr_put(kring);
			if (found) { /* notify other listeners */
				revents |= want_tx;
				want_tx = 0;
#ifndef linux
				kring->nm_notify(kring, 0);
#endif /* linux */
			}
		}
		/* if there were any packet to forward we must have handled them by now */
		send_down = 0;
		if (want_tx && retry_tx && sr) {
#ifndef linux
			nm_os_selrecord(sr, si[NR_TX]);
#endif /* !linux */
			retry_tx = 0;
			goto flush_tx;
		}
	}

	/*
	 * If want_rx is still set scan receive rings.
	 * Do it on all rings because otherwise we starve.
	 */
	if (want_rx) {
		/* two rounds here for race avoidance */
do_retry_rx:
		for (i = priv->np_qfirst[NR_RX]; i < priv->np_qlast[NR_RX]; i++) {
			int found = 0;

			kring = na->rx_rings[i];
			ring = kring->ring;

			if (unlikely(nm_kr_tryget(kring, 1, &revents)))
				continue;

			if (nm_rxsync_prologue(kring, ring) >= kring->nkr_num_slots) {
				netmap_ring_reinit(kring);
				revents |= POLLERR;
			}
			/* now we can use kring->rcur, rtail */

			/*
			 * transparent mode support: collect packets from
			 * hw rxring(s) that have been released by the user
			 */
			if (nm_may_forward_up(kring)) {
				netmap_grab_packets(kring, &q, netmap_fwd);
			}

			/* Clear the NR_FORWARD flag anyway, it may be set by
			 * the nm_sync() below only on for the host RX ring (see
			 * netmap_rxsync_from_host()). */
			kring->nr_kflags &= ~NR_FORWARD;
			if (kring->nm_sync(kring, sync_flags))
				revents |= POLLERR;
			else
				nm_sync_finalize(kring);
			send_down |= (kring->nr_kflags & NR_FORWARD);
			ring_timestamp_set(ring);
			found = kring->rcur != kring->rtail;
			nm_kr_put(kring);
			if (found) {
				revents |= want_rx;
				retry_rx = 0;
#ifndef linux
				kring->nm_notify(kring, 0);
#endif /* linux */
			}
		}

#ifndef linux
		if (retry_rx && sr) {
			nm_os_selrecord(sr, si[NR_RX]);
		}
#endif /* !linux */
		if (send_down || retry_rx) {
			retry_rx = 0;
			if (send_down)
				goto flush_tx; /* and retry_rx */
			else
				goto do_retry_rx;
		}
	}

	/*
	 * Transparent mode: released bufs (i.e. between kring->nr_hwcur and
	 * ring->head) marked with NS_FORWARD on hw rx rings are passed up
	 * to the host stack.
	 */

	if (mbq_peek(&q)) {
		netmap_send_up(na->ifp, &q);
	}

	return (revents);
#undef want_tx
#undef want_rx
}