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
struct TYPE_2__ {int csum_flags; scalar_t__ len; int /*<<< orphan*/  csum_data; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct bge_softc {int dummy; } ;
struct bge_rx_bd {int bge_flags; int bge_error_flag; int bge_ip_csum; int /*<<< orphan*/  bge_tcp_udp_csum; } ;

/* Variables and functions */
 scalar_t__ BGE_IS_5717_PLUS (struct bge_softc*) ; 
 int BGE_RXBDFLAG_IPV6 ; 
 int BGE_RXBDFLAG_IP_CSUM ; 
 int BGE_RXBDFLAG_TCP_UDP_CSUM ; 
 int BGE_RXERRFLAG_IP_CSUM_NOK ; 
 int CSUM_DATA_VALID ; 
 int CSUM_IP_CHECKED ; 
 int CSUM_IP_VALID ; 
 int CSUM_PSEUDO_HDR ; 
 scalar_t__ ETHER_MIN_NOPAD ; 

__attribute__((used)) static void
bge_rxcsum(struct bge_softc *sc, struct bge_rx_bd *cur_rx, struct mbuf *m)
{

	if (BGE_IS_5717_PLUS(sc)) {
		if ((cur_rx->bge_flags & BGE_RXBDFLAG_IPV6) == 0) {
			if (cur_rx->bge_flags & BGE_RXBDFLAG_IP_CSUM) {
				m->m_pkthdr.csum_flags |= CSUM_IP_CHECKED;
				if ((cur_rx->bge_error_flag &
				    BGE_RXERRFLAG_IP_CSUM_NOK) == 0)
					m->m_pkthdr.csum_flags |= CSUM_IP_VALID;
			}
			if (cur_rx->bge_flags & BGE_RXBDFLAG_TCP_UDP_CSUM) {
				m->m_pkthdr.csum_data =
				    cur_rx->bge_tcp_udp_csum;
				m->m_pkthdr.csum_flags |= CSUM_DATA_VALID |
				    CSUM_PSEUDO_HDR;
			}
		}
	} else {
		if (cur_rx->bge_flags & BGE_RXBDFLAG_IP_CSUM) {
			m->m_pkthdr.csum_flags |= CSUM_IP_CHECKED;
			if ((cur_rx->bge_ip_csum ^ 0xFFFF) == 0)
				m->m_pkthdr.csum_flags |= CSUM_IP_VALID;
		}
		if (cur_rx->bge_flags & BGE_RXBDFLAG_TCP_UDP_CSUM &&
		    m->m_pkthdr.len >= ETHER_MIN_NOPAD) {
			m->m_pkthdr.csum_data =
			    cur_rx->bge_tcp_udp_csum;
			m->m_pkthdr.csum_flags |= CSUM_DATA_VALID |
			    CSUM_PSEUDO_HDR;
		}
	}
}