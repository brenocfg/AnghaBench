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
struct rt_softc {int /*<<< orphan*/  interrupts; int /*<<< orphan*/  fe_int_status; struct ifnet* ifp; } ;
struct ifnet {int if_drv_flags; } ;

/* Variables and functions */
 int IFF_DRV_RUNNING ; 
 int RT5350_INT_RXQ0_DONE ; 
 int RT5350_INT_RXQ1_DONE ; 
 int RT5350_INT_RX_COHERENT ; 
 int RT5350_INT_TXQ0_DONE ; 
 int RT5350_INT_TXQ1_DONE ; 
 int RT5350_INT_TXQ2_DONE ; 
 int RT5350_INT_TXQ3_DONE ; 
 int RT5350_INT_TX_COHERENT ; 
 int RT5350_RX_DLY_INT ; 
 int RT5350_TX_DLY_INT ; 
 int /*<<< orphan*/  RT_DEBUG_INTR ; 
 int /*<<< orphan*/  RT_DPRINTF (struct rt_softc*,int /*<<< orphan*/ ,char*,int) ; 
 int RT_READ (struct rt_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_WRITE (struct rt_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt_rx_coherent_intr (struct rt_softc*) ; 
 int /*<<< orphan*/  rt_rx_delay_intr (struct rt_softc*) ; 
 int /*<<< orphan*/  rt_rx_intr (struct rt_softc*,int) ; 
 int /*<<< orphan*/  rt_tx_coherent_intr (struct rt_softc*) ; 
 int /*<<< orphan*/  rt_tx_delay_intr (struct rt_softc*) ; 
 int /*<<< orphan*/  rt_tx_intr (struct rt_softc*,int) ; 

__attribute__((used)) static void
rt_rt5350_intr(void *arg)
{
	struct rt_softc *sc;
	struct ifnet *ifp;
	uint32_t status;
	
	sc = arg;
	ifp = sc->ifp;
	
	/* acknowledge interrupts */
	status = RT_READ(sc, sc->fe_int_status);
	RT_WRITE(sc, sc->fe_int_status, status);
	
	RT_DPRINTF(sc, RT_DEBUG_INTR, "interrupt: status=0x%08x\n", status);
	
	if (status == 0xffffffff ||     /* device likely went away */
		status == 0)            /* not for us */
		return;
	
	sc->interrupts++;
	
	if (!(ifp->if_drv_flags & IFF_DRV_RUNNING))
	        return;
	
	if (status & RT5350_INT_TX_COHERENT)
		rt_tx_coherent_intr(sc);
	if (status & RT5350_INT_RX_COHERENT)
		rt_rx_coherent_intr(sc);
	if (status & RT5350_RX_DLY_INT)
	        rt_rx_delay_intr(sc);
	if (status & RT5350_TX_DLY_INT)
	        rt_tx_delay_intr(sc);
	if (status & RT5350_INT_RXQ1_DONE)
		rt_rx_intr(sc, 1);	
	if (status & RT5350_INT_RXQ0_DONE)
		rt_rx_intr(sc, 0);	
	if (status & RT5350_INT_TXQ3_DONE)
		rt_tx_intr(sc, 3);
	if (status & RT5350_INT_TXQ2_DONE)
		rt_tx_intr(sc, 2);
	if (status & RT5350_INT_TXQ1_DONE)
		rt_tx_intr(sc, 1);
	if (status & RT5350_INT_TXQ0_DONE)
		rt_tx_intr(sc, 0);
}