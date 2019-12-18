#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ error; } ;
typedef  TYPE_1__ xdma_transfer_status_t ;
struct xae_softc {int /*<<< orphan*/  xchan_tx; struct ifnet* ifp; } ;
struct mbuf {int dummy; } ;
struct ifnet {int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  XAE_LOCK (struct xae_softc*) ; 
 int /*<<< orphan*/  XAE_UNLOCK (struct xae_softc*) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int xdma_dequeue_mbuf (int /*<<< orphan*/ ,struct mbuf**,TYPE_1__*) ; 

__attribute__((used)) static int
xae_xdma_tx_intr(void *arg, xdma_transfer_status_t *status)
{
	xdma_transfer_status_t st;
	struct xae_softc *sc;
	struct ifnet *ifp;
	struct mbuf *m;
	int err;

	sc = arg;

	XAE_LOCK(sc);

	ifp = sc->ifp;

	for (;;) {
		err = xdma_dequeue_mbuf(sc->xchan_tx, &m, &st);
		if (err != 0) {
			break;
		}

		if (st.error != 0) {
			if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
		}

		m_freem(m);
	}

	ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;

	XAE_UNLOCK(sc);

	return (0);
}