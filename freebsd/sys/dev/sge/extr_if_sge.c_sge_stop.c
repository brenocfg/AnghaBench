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
struct sge_softc {int /*<<< orphan*/  sge_flags; int /*<<< orphan*/  sge_stat_ch; scalar_t__ sge_timer; struct ifnet* sge_ifp; } ;
struct ifnet {int if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_READ_4 (struct sge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct sge_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IntrMask ; 
 int /*<<< orphan*/  IntrStatus ; 
 int /*<<< orphan*/  RX_CTL ; 
 int /*<<< orphan*/  SGE_FLAG_LINK ; 
 int /*<<< orphan*/  SGE_LOCK_ASSERT (struct sge_softc*) ; 
 int /*<<< orphan*/  TX_CTL ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sge_list_rx_free (struct sge_softc*) ; 
 int /*<<< orphan*/  sge_list_tx_free (struct sge_softc*) ; 

__attribute__((used)) static void
sge_stop(struct sge_softc *sc)
{
	struct ifnet *ifp;

	ifp = sc->sge_ifp;

	SGE_LOCK_ASSERT(sc);

	sc->sge_timer = 0;
	callout_stop(&sc->sge_stat_ch);
	ifp->if_drv_flags &= ~(IFF_DRV_RUNNING | IFF_DRV_OACTIVE);

	CSR_WRITE_4(sc, IntrMask, 0);
	CSR_READ_4(sc, IntrMask);
	CSR_WRITE_4(sc, IntrStatus, 0xffffffff);
	/* Stop TX/RX MAC. */
	CSR_WRITE_4(sc, TX_CTL, 0x1a00);
	CSR_WRITE_4(sc, RX_CTL, 0x1a00);
	/* XXX Can we assume active DMA cycles gone? */
	DELAY(2000);
	CSR_WRITE_4(sc, IntrMask, 0);
	CSR_WRITE_4(sc, IntrStatus, 0xffffffff);

	sc->sge_flags &= ~SGE_FLAG_LINK;
	sge_list_rx_free(sc);
	sge_list_tx_free(sc);
}