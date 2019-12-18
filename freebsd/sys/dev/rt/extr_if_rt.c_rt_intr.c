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
 int CNT_GDM_AF ; 
 int CNT_PPE_AF ; 
 int GDM_CRC_DROP ; 
 int GDM_OTHER_DROP ; 
 int IFF_DRV_RUNNING ; 
 int INT_RX_COHERENT ; 
 int INT_RX_DONE ; 
 int INT_TXQ0_DONE ; 
 int INT_TXQ1_DONE ; 
 int INT_TXQ2_DONE ; 
 int INT_TXQ3_DONE ; 
 int INT_TX_COHERENT ; 
 int PSE_BUF_DROP ; 
 int PSE_FQ_EMPTY ; 
 int PSE_P0_FC ; 
 int PSE_P1_FC ; 
 int PSE_P2_FC ; 
 int /*<<< orphan*/  RT_DEBUG_INTR ; 
 int /*<<< orphan*/  RT_DPRINTF (struct rt_softc*,int /*<<< orphan*/ ,char*,int) ; 
 int RT_READ (struct rt_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_WRITE (struct rt_softc*,int /*<<< orphan*/ ,int) ; 
 int RX_DLY_INT ; 
 int TX_DLY_INT ; 
 int /*<<< orphan*/  rt_cnt_gdm_af (struct rt_softc*) ; 
 int /*<<< orphan*/  rt_cnt_ppe_af (struct rt_softc*) ; 
 int /*<<< orphan*/  rt_gdm_crc_drop (struct rt_softc*) ; 
 int /*<<< orphan*/  rt_gdm_other_drop (struct rt_softc*) ; 
 int /*<<< orphan*/  rt_pse_buf_drop (struct rt_softc*) ; 
 int /*<<< orphan*/  rt_pse_fq_empty (struct rt_softc*) ; 
 int /*<<< orphan*/  rt_pse_p0_fc (struct rt_softc*) ; 
 int /*<<< orphan*/  rt_pse_p1_fc (struct rt_softc*) ; 
 int /*<<< orphan*/  rt_pse_p2_fc (struct rt_softc*) ; 
 int /*<<< orphan*/  rt_rx_coherent_intr (struct rt_softc*) ; 
 int /*<<< orphan*/  rt_rx_delay_intr (struct rt_softc*) ; 
 int /*<<< orphan*/  rt_rx_intr (struct rt_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt_tx_coherent_intr (struct rt_softc*) ; 
 int /*<<< orphan*/  rt_tx_delay_intr (struct rt_softc*) ; 
 int /*<<< orphan*/  rt_tx_intr (struct rt_softc*,int) ; 

__attribute__((used)) static void
rt_intr(void *arg)
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

	if (status == 0xffffffff ||	/* device likely went away */
		status == 0)		/* not for us */
		return;

	sc->interrupts++;

	if (!(ifp->if_drv_flags & IFF_DRV_RUNNING))
		return;

	if (status & CNT_PPE_AF)
		rt_cnt_ppe_af(sc);

	if (status & CNT_GDM_AF)
		rt_cnt_gdm_af(sc);

	if (status & PSE_P2_FC)
		rt_pse_p2_fc(sc);

	if (status & GDM_CRC_DROP)
		rt_gdm_crc_drop(sc);

	if (status & PSE_BUF_DROP)
		rt_pse_buf_drop(sc);

	if (status & GDM_OTHER_DROP)
		rt_gdm_other_drop(sc);

	if (status & PSE_P1_FC)
		rt_pse_p1_fc(sc);

	if (status & PSE_P0_FC)
		rt_pse_p0_fc(sc);

	if (status & PSE_FQ_EMPTY)
		rt_pse_fq_empty(sc);

	if (status & INT_TX_COHERENT)
		rt_tx_coherent_intr(sc);

	if (status & INT_RX_COHERENT)
		rt_rx_coherent_intr(sc);

	if (status & RX_DLY_INT)
		rt_rx_delay_intr(sc);

	if (status & TX_DLY_INT)
		rt_tx_delay_intr(sc);

	if (status & INT_RX_DONE)
		rt_rx_intr(sc, 0);

	if (status & INT_TXQ3_DONE)
		rt_tx_intr(sc, 3);

	if (status & INT_TXQ2_DONE)
		rt_tx_intr(sc, 2);

	if (status & INT_TXQ1_DONE)
		rt_tx_intr(sc, 1);

	if (status & INT_TXQ0_DONE)
		rt_tx_intr(sc, 0);
}