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
typedef  int /*<<< orphan*/  uint16_t ;
struct ntb_transport_qp {int dummy; } ;
struct ntb_net_queue {int /*<<< orphan*/  ifp; struct ntb_net_ctx* sc; } ;
struct ntb_net_ctx {int num_queues; int queues; } ;
struct TYPE_2__ {int csum_data; void* csum_flags; struct ntb_net_queue* flowid; int /*<<< orphan*/  rcvif; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTR1 (int /*<<< orphan*/ ,char*,int) ; 
#define  ETHERTYPE_IP 129 
#define  ETHERTYPE_IPV6 128 
 int IFCAP_RXCSUM ; 
 int IFCAP_RXCSUM_IPV6 ; 
 int /*<<< orphan*/  IFCOUNTER_IERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_IPACKETS ; 
 int /*<<< orphan*/  KTR_NTB ; 
 int /*<<< orphan*/  M_HASHTYPE_OPAQUE ; 
 int /*<<< orphan*/  M_HASHTYPE_SET (struct mbuf*,int /*<<< orphan*/ ) ; 
 void* NTB_CSUM_SET ; 
 int if_getcapenable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_inc_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_input (int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  m_copydata (struct mbuf*,int,int,void*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ntb_net_rx_handler(struct ntb_transport_qp *qp, void *qp_data, void *data,
    int len)
{
	struct ntb_net_queue *q = qp_data;
	struct ntb_net_ctx *sc = q->sc;
	struct mbuf *m = data;
	if_t ifp = q->ifp;
	uint16_t proto;

	CTR1(KTR_NTB, "RX: rx handler (%d)", len);
	if (len < 0) {
		if_inc_counter(ifp, IFCOUNTER_IERRORS, 1);
		return;
	}

	m->m_pkthdr.rcvif = ifp;
	if (sc->num_queues > 1) {
		m->m_pkthdr.flowid = q - sc->queues;
		M_HASHTYPE_SET(m, M_HASHTYPE_OPAQUE);
	}
	if (if_getcapenable(ifp) & (IFCAP_RXCSUM | IFCAP_RXCSUM_IPV6)) {
		m_copydata(m, 12, 2, (void *)&proto);
		switch (ntohs(proto)) {
		case ETHERTYPE_IP:
			if (if_getcapenable(ifp) & IFCAP_RXCSUM) {
				m->m_pkthdr.csum_data = 0xffff;
				m->m_pkthdr.csum_flags = NTB_CSUM_SET;
			}
			break;
		case ETHERTYPE_IPV6:
			if (if_getcapenable(ifp) & IFCAP_RXCSUM_IPV6) {
				m->m_pkthdr.csum_data = 0xffff;
				m->m_pkthdr.csum_flags = NTB_CSUM_SET;
			}
			break;
		}
	}
	if_inc_counter(ifp, IFCOUNTER_IPACKETS, 1);
	if_input(ifp, m);
}