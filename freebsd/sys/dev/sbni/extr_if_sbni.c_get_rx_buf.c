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
struct sbni_softc {struct mbuf* rx_buf_p; int /*<<< orphan*/  ifp; } ;
struct TYPE_2__ {scalar_t__ len; } ;
struct mbuf {scalar_t__ m_len; TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 scalar_t__ ETHER_MAX_LEN ; 
 int /*<<< orphan*/  MCLGET (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGETHDR (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MHLEN ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  if_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  m_adj (struct mbuf*,int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

__attribute__((used)) static int
get_rx_buf(struct sbni_softc *sc)
{
	struct mbuf *m;

	MGETHDR(m, M_NOWAIT, MT_DATA);
	if (m == NULL) {
		if_printf(sc->ifp, "cannot allocate header mbuf\n");
		return (0);
	}

	/*
	 * We always put the received packet in a single buffer -
	 * either with just an mbuf header or in a cluster attached
	 * to the header. The +2 is to compensate for the alignment
	 * fixup below.
	 */
	if (ETHER_MAX_LEN + 2 > MHLEN) {
		/* Attach an mbuf cluster */
		if (!(MCLGET(m, M_NOWAIT))) {
			m_freem(m);
			return (0);
		}
	}
	m->m_pkthdr.len = m->m_len = ETHER_MAX_LEN + 2;

	/*
	 * The +2 is to longword align the start of the real packet.
	 * (sizeof ether_header == 14)
	 * This is important for NFS.
	 */
	m_adj(m, 2);
	sc->rx_buf_p = m;
	return (1);
}