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
struct TYPE_4__ {int /*<<< orphan*/  vtxs_tso; } ;
struct vtnet_txq {TYPE_2__ vtntx_stats; struct vtnet_softc* vtntx_sc; } ;
struct vtnet_softc {int vtnet_flags; int /*<<< orphan*/  vtnet_ifp; } ;
struct virtio_net_hdr {int hdr_len; int /*<<< orphan*/  gso_type; int /*<<< orphan*/  gso_size; } ;
struct timeval {int dummy; } ;
struct tcphdr {int th_off; int th_flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  tso_segsz; } ;
struct mbuf {int m_len; TYPE_1__ m_pkthdr; scalar_t__ m_data; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int ENOTSUP ; 
 int ETHERTYPE_IP ; 
 int TH_CWR ; 
 int /*<<< orphan*/  VIRTIO_NET_HDR_GSO_ECN ; 
 int /*<<< orphan*/  VIRTIO_NET_HDR_GSO_TCPV4 ; 
 int /*<<< orphan*/  VIRTIO_NET_HDR_GSO_TCPV6 ; 
 int VTNET_FLAG_TSO_ECN ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  if_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  m_copydata (struct mbuf*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ppsratecheck (struct timeval*,int*,int) ; 

__attribute__((used)) static int
vtnet_txq_offload_tso(struct vtnet_txq *txq, struct mbuf *m, int eth_type,
    int offset, struct virtio_net_hdr *hdr)
{
	static struct timeval lastecn;
	static int curecn;
	struct vtnet_softc *sc;
	struct tcphdr *tcp, tcphdr;

	sc = txq->vtntx_sc;

	if (__predict_false(m->m_len < offset + sizeof(struct tcphdr))) {
		m_copydata(m, offset, sizeof(struct tcphdr), (caddr_t) &tcphdr);
		tcp = &tcphdr;
	} else
		tcp = (struct tcphdr *)(m->m_data + offset);

	hdr->hdr_len = offset + (tcp->th_off << 2);
	hdr->gso_size = m->m_pkthdr.tso_segsz;
	hdr->gso_type = eth_type == ETHERTYPE_IP ? VIRTIO_NET_HDR_GSO_TCPV4 :
	    VIRTIO_NET_HDR_GSO_TCPV6;

	if (tcp->th_flags & TH_CWR) {
		/*
		 * Drop if VIRTIO_NET_F_HOST_ECN was not negotiated. In FreeBSD,
		 * ECN support is not on a per-interface basis, but globally via
		 * the net.inet.tcp.ecn.enable sysctl knob. The default is off.
		 */
		if ((sc->vtnet_flags & VTNET_FLAG_TSO_ECN) == 0) {
			if (ppsratecheck(&lastecn, &curecn, 1))
				if_printf(sc->vtnet_ifp,
				    "TSO with ECN not negotiated with host\n");
			return (ENOTSUP);
		}
		hdr->gso_type |= VIRTIO_NET_HDR_GSO_ECN;
	}

	txq->vtntx_stats.vtxs_tso++;

	return (0);
}