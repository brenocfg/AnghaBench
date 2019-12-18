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
struct rt_softc {scalar_t__ fe_int_enable; scalar_t__ rt_chipid; scalar_t__ gdma1_base; int /*<<< orphan*/  periodic_task; int /*<<< orphan*/  taskqueue; int /*<<< orphan*/  tx_done_task; int /*<<< orphan*/  rx_done_task; int /*<<< orphan*/  tx_watchdog_ch; int /*<<< orphan*/  periodic_ch; scalar_t__ tx_timer; struct ifnet* ifp; } ;
struct ifnet {int if_drv_flags; } ;

/* Variables and functions */
 scalar_t__ FE_RST_GLO ; 
 scalar_t__ GDMA_FWD_CFG ; 
 int GDM_BFRC_P_SHIFT ; 
 int GDM_DST_PORT_CPU ; 
 int GDM_ICS_EN ; 
 int GDM_MFRC_P_SHIFT ; 
 int GDM_OFRC_P_SHIFT ; 
 int GDM_STRPCRC ; 
 int GDM_TCS_EN ; 
 int GDM_UCS_EN ; 
 int GDM_UFRC_P_SHIFT ; 
 scalar_t__ GE_PORT_BASE ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int PSE_RESET ; 
 scalar_t__ RT_CHIPID_MT7620 ; 
 scalar_t__ RT_CHIPID_MT7621 ; 
 scalar_t__ RT_CHIPID_RT5350 ; 
 int /*<<< orphan*/  RT_DEBUG_ANY ; 
 int /*<<< orphan*/  RT_DPRINTF (struct rt_softc*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RT_SOFTC_ASSERT_LOCKED (struct rt_softc*) ; 
 int /*<<< orphan*/  RT_SOFTC_LOCK (struct rt_softc*) ; 
 int /*<<< orphan*/  RT_SOFTC_UNLOCK (struct rt_softc*) ; 
 int /*<<< orphan*/  RT_WRITE (struct rt_softc*,scalar_t__,int) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rt_stop_locked(void *priv)
{
	struct rt_softc *sc;
	struct ifnet *ifp;

	sc = priv;
	ifp = sc->ifp;

	RT_DPRINTF(sc, RT_DEBUG_ANY, "stopping\n");

	RT_SOFTC_ASSERT_LOCKED(sc);
	sc->tx_timer = 0;
	ifp->if_drv_flags &= ~(IFF_DRV_RUNNING | IFF_DRV_OACTIVE);
	callout_stop(&sc->periodic_ch);
	callout_stop(&sc->tx_watchdog_ch);
	RT_SOFTC_UNLOCK(sc);
	taskqueue_block(sc->taskqueue);

	/*
	 * Sometime rt_stop_locked called from isr and we get panic
	 * When found, I fix it
	 */
#ifdef notyet
	taskqueue_drain(sc->taskqueue, &sc->rx_done_task);
	taskqueue_drain(sc->taskqueue, &sc->tx_done_task);
	taskqueue_drain(sc->taskqueue, &sc->periodic_task);
#endif
	RT_SOFTC_LOCK(sc);

	/* disable interrupts */
	RT_WRITE(sc, sc->fe_int_enable, 0);
	
	if(sc->rt_chipid != RT_CHIPID_RT5350 &&
	   sc->rt_chipid != RT_CHIPID_MT7620 &&
	   sc->rt_chipid != RT_CHIPID_MT7621) {
		/* reset adapter */
		RT_WRITE(sc, GE_PORT_BASE + FE_RST_GLO, PSE_RESET);
	}

	if (sc->gdma1_base != 0)
		RT_WRITE(sc, sc->gdma1_base + GDMA_FWD_CFG,
		(
		GDM_ICS_EN | /* Enable IP Csum */
		GDM_TCS_EN | /* Enable TCP Csum */
		GDM_UCS_EN | /* Enable UDP Csum */
		GDM_STRPCRC | /* Strip CRC from packet */
		GDM_DST_PORT_CPU << GDM_UFRC_P_SHIFT | /* fwd UCast to CPU */
		GDM_DST_PORT_CPU << GDM_BFRC_P_SHIFT | /* fwd BCast to CPU */
		GDM_DST_PORT_CPU << GDM_MFRC_P_SHIFT | /* fwd MCast to CPU */
		GDM_DST_PORT_CPU << GDM_OFRC_P_SHIFT   /* fwd Other to CPU */
		));
}