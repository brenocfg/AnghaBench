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
struct sbni_softc {struct mbuf* rx_buf_p; int /*<<< orphan*/  inppos; struct ifnet* ifp; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; struct ifnet* rcvif; } ;
struct mbuf {int /*<<< orphan*/  m_len; TYPE_1__ m_pkthdr; } ;
struct ifnet {int /*<<< orphan*/  (* if_input ) (struct ifnet*,struct mbuf*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SBNI_LOCK (struct sbni_softc*) ; 
 int /*<<< orphan*/  SBNI_UNLOCK (struct sbni_softc*) ; 
 int /*<<< orphan*/  stub1 (struct ifnet*,struct mbuf*) ; 

__attribute__((used)) static void
indicate_pkt(struct sbni_softc *sc)
{
	struct ifnet *ifp = sc->ifp;
	struct mbuf *m;

	m = sc->rx_buf_p;
	m->m_pkthdr.rcvif = ifp;
	m->m_pkthdr.len   = m->m_len = sc->inppos;
	sc->rx_buf_p = NULL;

	SBNI_UNLOCK(sc);
	(*ifp->if_input)(ifp, m);
	SBNI_LOCK(sc);
}