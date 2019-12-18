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
struct mbq {int dummy; } ;
struct netmap_kring {scalar_t__ nr_mode; int nr_hwtail; int nr_hwcur; int nkr_num_slots; int /*<<< orphan*/  (* nm_notify ) (struct netmap_kring*,int /*<<< orphan*/ ) ;struct mbq rx_queue; } ;
struct netmap_adapter {size_t num_host_rx_rings; unsigned int num_tx_rings; int /*<<< orphan*/  name; } ;
struct mbuf {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 size_t ENOBUFS ; 
 size_t ENXIO ; 
 int /*<<< orphan*/  ETHER_BPF_MTAP (struct ifnet*,struct mbuf*) ; 
 size_t MBUF_LEN (struct mbuf*) ; 
 int MBUF_TRANSMIT (struct netmap_adapter*,struct ifnet*,struct mbuf*) ; 
 void* MBUF_TXQ (struct mbuf*) ; 
 struct netmap_adapter* NA (struct ifnet*) ; 
 size_t NETMAP_BUF_SIZE (struct netmap_adapter*) ; 
 scalar_t__ NKR_NETMAP_OFF ; 
 struct netmap_kring** NMR (struct netmap_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NR_RX ; 
 int /*<<< orphan*/  NR_TX ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  mbq_enqueue (struct mbq*,struct mbuf*) ; 
 int mbq_len (struct mbq*) ; 
 int /*<<< orphan*/  mbq_lock (struct mbq*) ; 
 int /*<<< orphan*/  mbq_unlock (struct mbq*) ; 
 int /*<<< orphan*/  netmap_generic_hwcsum ; 
 int /*<<< orphan*/  nm_netmap_on (struct netmap_adapter*) ; 
 scalar_t__ nm_os_mbuf_has_csum_offld (struct mbuf*) ; 
 scalar_t__ nm_os_mbuf_has_seg_offld (struct mbuf*) ; 
 int /*<<< orphan*/  nm_prdis (int,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nm_prerr (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  nm_prlim (int,char*,int /*<<< orphan*/ ,...) ; 
 size_t nma_get_nrings (struct netmap_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct netmap_kring*,int /*<<< orphan*/ ) ; 

int
netmap_transmit(struct ifnet *ifp, struct mbuf *m)
{
	struct netmap_adapter *na = NA(ifp);
	struct netmap_kring *kring, *tx_kring;
	u_int len = MBUF_LEN(m);
	u_int error = ENOBUFS;
	unsigned int txr;
	struct mbq *q;
	int busy;
	u_int i;

	i = MBUF_TXQ(m);
	if (i >= na->num_host_rx_rings) {
		i = i % na->num_host_rx_rings;
	}
	kring = NMR(na, NR_RX)[nma_get_nrings(na, NR_RX) + i];

	// XXX [Linux] we do not need this lock
	// if we follow the down/configure/up protocol -gl
	// mtx_lock(&na->core_lock);

	if (!nm_netmap_on(na)) {
		nm_prerr("%s not in netmap mode anymore", na->name);
		error = ENXIO;
		goto done;
	}

	txr = MBUF_TXQ(m);
	if (txr >= na->num_tx_rings) {
		txr %= na->num_tx_rings;
	}
	tx_kring = NMR(na, NR_TX)[txr];

	if (tx_kring->nr_mode == NKR_NETMAP_OFF) {
		return MBUF_TRANSMIT(na, ifp, m);
	}

	q = &kring->rx_queue;

	// XXX reconsider long packets if we handle fragments
	if (len > NETMAP_BUF_SIZE(na)) { /* too long for us */
		nm_prerr("%s from_host, drop packet size %d > %d", na->name,
			len, NETMAP_BUF_SIZE(na));
		goto done;
	}

	if (!netmap_generic_hwcsum) {
		if (nm_os_mbuf_has_csum_offld(m)) {
			nm_prlim(1, "%s drop mbuf that needs checksum offload", na->name);
			goto done;
		}
	}

	if (nm_os_mbuf_has_seg_offld(m)) {
		nm_prlim(1, "%s drop mbuf that needs generic segmentation offload", na->name);
		goto done;
	}

#ifdef __FreeBSD__
	ETHER_BPF_MTAP(ifp, m);
#endif /* __FreeBSD__ */

	/* protect against netmap_rxsync_from_host(), netmap_sw_to_nic()
	 * and maybe other instances of netmap_transmit (the latter
	 * not possible on Linux).
	 * We enqueue the mbuf only if we are sure there is going to be
	 * enough room in the host RX ring, otherwise we drop it.
	 */
	mbq_lock(q);

	busy = kring->nr_hwtail - kring->nr_hwcur;
	if (busy < 0)
		busy += kring->nkr_num_slots;
	if (busy + mbq_len(q) >= kring->nkr_num_slots - 1) {
		nm_prlim(2, "%s full hwcur %d hwtail %d qlen %d", na->name,
			kring->nr_hwcur, kring->nr_hwtail, mbq_len(q));
	} else {
		mbq_enqueue(q, m);
		nm_prdis(2, "%s %d bufs in queue", na->name, mbq_len(q));
		/* notify outside the lock */
		m = NULL;
		error = 0;
	}
	mbq_unlock(q);

done:
	if (m)
		m_freem(m);
	/* unconditionally wake up listeners */
	kring->nm_notify(kring, 0);
	/* this is normally netmap_notify(), but for nics
	 * connected to a bridge it is netmap_bwrap_intr_notify(),
	 * that possibly forwards the frames through the switch
	 */

	return (error);
}