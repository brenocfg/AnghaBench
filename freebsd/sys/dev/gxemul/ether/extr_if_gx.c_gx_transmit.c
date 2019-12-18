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
struct TYPE_2__ {int len; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct ifnet {int if_drv_flags; struct gx_softc* if_softc; } ;
struct gx_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_BPF_MTAP (struct ifnet*,struct mbuf*) ; 
 int /*<<< orphan*/  GXEMUL_ETHER_DEV_BUFFER ; 
 int /*<<< orphan*/  GXEMUL_ETHER_DEV_COMMAND ; 
 int GXEMUL_ETHER_DEV_COMMAND_TX ; 
 scalar_t__ GXEMUL_ETHER_DEV_FUNCTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GXEMUL_ETHER_DEV_LENGTH ; 
 int /*<<< orphan*/  GXEMUL_ETHER_DEV_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GXEMUL_ETHER_LOCK (struct gx_softc*) ; 
 int /*<<< orphan*/  GXEMUL_ETHER_UNLOCK (struct gx_softc*) ; 
 int /*<<< orphan*/  IFCOUNTER_OBYTES ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_copydata (struct mbuf*,int /*<<< orphan*/ ,int,void*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

__attribute__((used)) static int
gx_transmit(struct ifnet *ifp, struct mbuf *m)
{
	struct gx_softc *sc;

	sc = ifp->if_softc;

	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != IFF_DRV_RUNNING) {
		m_freem(m);
		return (0);
	}

	GXEMUL_ETHER_LOCK(sc);
	GXEMUL_ETHER_DEV_WRITE(GXEMUL_ETHER_DEV_LENGTH, m->m_pkthdr.len);
	m_copydata(m, 0, m->m_pkthdr.len, (void *)(uintptr_t)GXEMUL_ETHER_DEV_FUNCTION(GXEMUL_ETHER_DEV_BUFFER));
	GXEMUL_ETHER_DEV_WRITE(GXEMUL_ETHER_DEV_COMMAND, GXEMUL_ETHER_DEV_COMMAND_TX);
	GXEMUL_ETHER_UNLOCK(sc);

	ETHER_BPF_MTAP(ifp, m);

	if_inc_counter(ifp, IFCOUNTER_OPACKETS, 1);
	if_inc_counter(ifp, IFCOUNTER_OBYTES, m->m_pkthdr.len);

	m_freem(m);

	return (0);
}