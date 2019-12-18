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
typedef  int uint32_t ;
struct cgem_softc {int net_ctl_shadow; int /*<<< orphan*/  rxnobufs; int /*<<< orphan*/  rxoverruns; int /*<<< orphan*/  dev; int /*<<< orphan*/  ifp; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int CGEM_INTR_HRESP_NOT_OK ; 
 int CGEM_INTR_RX_COMPLETE ; 
 int CGEM_INTR_RX_OVERRUN ; 
 int CGEM_INTR_RX_USED_READ ; 
 int /*<<< orphan*/  CGEM_INTR_STAT ; 
 int /*<<< orphan*/  CGEM_LOCK (struct cgem_softc*) ; 
 int /*<<< orphan*/  CGEM_NET_CTRL ; 
 int CGEM_NET_CTRL_FLUSH_DPRAM_PKT ; 
 int /*<<< orphan*/  CGEM_RX_STAT ; 
 int CGEM_RX_STAT_HRESP_NOT_OK ; 
 int CGEM_RX_STAT_OVERRUN ; 
 int /*<<< orphan*/  CGEM_UNLOCK (struct cgem_softc*) ; 
 int IFF_DRV_RUNNING ; 
 int RD4 (struct cgem_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WR4 (struct cgem_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cgem_clean_tx (struct cgem_softc*) ; 
 int /*<<< orphan*/  cgem_fill_rqueue (struct cgem_softc*) ; 
 int /*<<< orphan*/  cgem_recv (struct cgem_softc*) ; 
 int /*<<< orphan*/  cgem_start_locked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int if_getdrvflags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_sendq_empty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cgem_intr(void *arg)
{
	struct cgem_softc *sc = (struct cgem_softc *)arg;
	if_t ifp = sc->ifp;
	uint32_t istatus;

	CGEM_LOCK(sc);

	if ((if_getdrvflags(ifp) & IFF_DRV_RUNNING) == 0) {
		CGEM_UNLOCK(sc);
		return;
	}

	/* Read interrupt status and immediately clear the bits. */
	istatus = RD4(sc, CGEM_INTR_STAT);
	WR4(sc, CGEM_INTR_STAT, istatus);

	/* Packets received. */
	if ((istatus & CGEM_INTR_RX_COMPLETE) != 0)
		cgem_recv(sc);

	/* Free up any completed transmit buffers. */
	cgem_clean_tx(sc);

	/* Hresp not ok.  Something is very bad with DMA.  Try to clear. */
	if ((istatus & CGEM_INTR_HRESP_NOT_OK) != 0) {
		device_printf(sc->dev, "cgem_intr: hresp not okay! "
			      "rx_status=0x%x\n", RD4(sc, CGEM_RX_STAT));
		WR4(sc, CGEM_RX_STAT, CGEM_RX_STAT_HRESP_NOT_OK);
	}

	/* Receiver overrun. */
	if ((istatus & CGEM_INTR_RX_OVERRUN) != 0) {
		/* Clear status bit. */
		WR4(sc, CGEM_RX_STAT, CGEM_RX_STAT_OVERRUN);
		sc->rxoverruns++;
	}

	/* Receiver ran out of bufs. */
	if ((istatus & CGEM_INTR_RX_USED_READ) != 0) {
		WR4(sc, CGEM_NET_CTRL, sc->net_ctl_shadow |
		    CGEM_NET_CTRL_FLUSH_DPRAM_PKT);
		cgem_fill_rqueue(sc);
		sc->rxnobufs++;
	}

	/* Restart transmitter if needed. */
	if (!if_sendq_empty(ifp))
		cgem_start_locked(ifp);

	CGEM_UNLOCK(sc);
}