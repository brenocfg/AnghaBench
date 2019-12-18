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
struct vge_softc {int /*<<< orphan*/  vge_watchdog; scalar_t__ vge_timer; struct ifnet* vge_ifp; } ;
struct ifnet {int if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_1 (struct vge_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct vge_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct vge_softc*,int /*<<< orphan*/ ,int) ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  VGE_CHAIN_RESET (struct vge_softc*) ; 
 int VGE_CR0_STOP ; 
 int VGE_CR3_INT_GMSK ; 
 int /*<<< orphan*/  VGE_CRC3 ; 
 int /*<<< orphan*/  VGE_CRS0 ; 
 int /*<<< orphan*/  VGE_ISR ; 
 int /*<<< orphan*/  VGE_LOCK_ASSERT (struct vge_softc*) ; 
 int /*<<< orphan*/  VGE_RXDESC_ADDR_LO ; 
 int /*<<< orphan*/  VGE_RXQCSRC ; 
 int /*<<< orphan*/  VGE_TXQCSRC ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vge_freebufs (struct vge_softc*) ; 
 int /*<<< orphan*/  vge_stats_update (struct vge_softc*) ; 
 int /*<<< orphan*/  vge_txeof (struct vge_softc*) ; 

__attribute__((used)) static void
vge_stop(struct vge_softc *sc)
{
	struct ifnet *ifp;

	VGE_LOCK_ASSERT(sc);
	ifp = sc->vge_ifp;
	sc->vge_timer = 0;
	callout_stop(&sc->vge_watchdog);

	ifp->if_drv_flags &= ~(IFF_DRV_RUNNING | IFF_DRV_OACTIVE);

	CSR_WRITE_1(sc, VGE_CRC3, VGE_CR3_INT_GMSK);
	CSR_WRITE_1(sc, VGE_CRS0, VGE_CR0_STOP);
	CSR_WRITE_4(sc, VGE_ISR, 0xFFFFFFFF);
	CSR_WRITE_2(sc, VGE_TXQCSRC, 0xFFFF);
	CSR_WRITE_1(sc, VGE_RXQCSRC, 0xFF);
	CSR_WRITE_4(sc, VGE_RXDESC_ADDR_LO, 0);

	vge_stats_update(sc);
	VGE_CHAIN_RESET(sc);
	vge_txeof(sc);
	vge_freebufs(sc);
}