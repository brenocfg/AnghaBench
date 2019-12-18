#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct sfxge_txq {int dummy; } ;
struct sfxge_softc {int if_flags; int txq_dynamic_cksum_toggle_supported; int txq_count; int* rx_indir_table; struct sfxge_txq** txq; } ;
struct TYPE_2__ {int csum_flags; int flowid; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct ifnet {int if_flags; scalar_t__ if_softc; } ;

/* Variables and functions */
 int B_FALSE ; 
 int CSUM_DELAY_DATA ; 
 int CSUM_DELAY_IP ; 
 int CSUM_TCP_IPV6 ; 
 int CSUM_TSO ; 
 int CSUM_UDP_IPV6 ; 
 int IFF_UP ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ M_HASHTYPE_GET (struct mbuf*) ; 
 scalar_t__ M_HASHTYPE_NONE ; 
 size_t SFXGE_TXQ_IP_CKSUM ; 
 int SFXGE_TXQ_IP_TCP_UDP_CKSUM ; 
 size_t SFXGE_TXQ_NON_CKSUM ; 
 int SFXGE_TXQ_NTYPES ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int nitems (int*) ; 
 scalar_t__ rss_m2bucket (struct mbuf*,int*) ; 
 int /*<<< orphan*/  sfxge_parse_tx_packet (struct mbuf*) ; 
 int sfxge_tx_packet_add (struct sfxge_txq*,struct mbuf*) ; 

int
sfxge_if_transmit(struct ifnet *ifp, struct mbuf *m)
{
	struct sfxge_softc *sc;
	struct sfxge_txq *txq;
	int rc;

	sc = (struct sfxge_softc *)ifp->if_softc;

	/*
	 * Transmit may be called when interface is up from the kernel
	 * point of view, but not yet up (in progress) from the driver
	 * point of view. I.e. link aggregation bring up.
	 * Transmit may be called when interface is up from the driver
	 * point of view, but already down from the kernel point of
	 * view. I.e. Rx when interface shutdown is in progress.
	 */
	KASSERT((ifp->if_flags & IFF_UP) || (sc->if_flags & IFF_UP),
		("interface not up"));

	/* Pick the desired transmit queue. */
	if (sc->txq_dynamic_cksum_toggle_supported |
	    (m->m_pkthdr.csum_flags &
	     (CSUM_DELAY_DATA | CSUM_TCP_IPV6 | CSUM_UDP_IPV6 | CSUM_TSO))) {
		int index = 0;

#ifdef RSS
		uint32_t bucket_id;

		/*
		 * Select a TX queue which matches the corresponding
		 * RX queue for the hash in order to assign both
		 * TX and RX parts of the flow to the same CPU
		 */
		if (rss_m2bucket(m, &bucket_id) == 0)
			index = bucket_id % (sc->txq_count - (SFXGE_TXQ_NTYPES - 1));
#else
		/* check if flowid is set */
		if (M_HASHTYPE_GET(m) != M_HASHTYPE_NONE) {
			uint32_t hash = m->m_pkthdr.flowid;
			uint32_t idx = hash % nitems(sc->rx_indir_table);

			index = sc->rx_indir_table[idx];
		}
#endif
#if SFXGE_TX_PARSE_EARLY
		if (m->m_pkthdr.csum_flags & CSUM_TSO)
			sfxge_parse_tx_packet(m);
#endif
		index += (sc->txq_dynamic_cksum_toggle_supported == B_FALSE) ?
			 SFXGE_TXQ_IP_TCP_UDP_CKSUM : 0;
		txq = sc->txq[index];
	} else if (m->m_pkthdr.csum_flags & CSUM_DELAY_IP) {
		txq = sc->txq[SFXGE_TXQ_IP_CKSUM];
	} else {
		txq = sc->txq[SFXGE_TXQ_NON_CKSUM];
	}

	rc = sfxge_tx_packet_add(txq, m);
	if (rc != 0)
		m_freem(m);

	return (rc);
}