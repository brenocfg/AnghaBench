#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  callout; scalar_t__ timer; } ;
struct TYPE_4__ {int active_queue_len; int running; int /*<<< orphan*/  active; } ;
struct cpsw_softc {TYPE_1__ watchdog; TYPE_2__ tx; TYPE_2__ rx; scalar_t__ dualemac; } ;
struct cpsw_slot {int dummy; } ;

/* Variables and functions */
 int ALE_PORTCTL_FORWARD ; 
 int ALE_PORTCTL_INGRESS ; 
 int /*<<< orphan*/  CPSW_ALE_CONTROL ; 
 int CPSW_ALE_CTL_CLEAR_TBL ; 
 int CPSW_ALE_CTL_ENABLE ; 
 int CPSW_ALE_CTL_VLAN_AWARE ; 
 int /*<<< orphan*/  CPSW_ALE_PORTCTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPSW_CPDMA_DMA_INTMASK_SET ; 
 int /*<<< orphan*/  CPSW_CPDMA_RX_BUFFER_OFFSET ; 
 int /*<<< orphan*/  CPSW_CPDMA_RX_CONTROL ; 
 int /*<<< orphan*/  CPSW_CPDMA_RX_FREEBUFFER (int /*<<< orphan*/ ) ; 
 int CPSW_CPDMA_RX_INT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPSW_CPDMA_RX_INTMASK_SET ; 
 int CPSW_CPDMA_RX_INT_THRESH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPSW_CPDMA_RX_PENDTHRESH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPSW_CPDMA_TX_CONTROL ; 
 int /*<<< orphan*/  CPSW_CPDMA_TX_INTMASK_SET ; 
 int /*<<< orphan*/  CPSW_PORT_P0_CPDMA_RX_CH_MAP ; 
 int /*<<< orphan*/  CPSW_PORT_P0_CPDMA_TX_PRI_MAP ; 
 int /*<<< orphan*/  CPSW_SS_FLOW_CONTROL ; 
 int /*<<< orphan*/  CPSW_SS_PTYPE ; 
 int /*<<< orphan*/  CPSW_SS_STAT_PORT_EN ; 
 int CPSW_TXFRAGS ; 
 int /*<<< orphan*/  CPSW_WR_C_MISC_EN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPSW_WR_C_RX_EN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPSW_WR_C_RX_THRESH_EN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPSW_WR_C_TX_EN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPSW_WR_INT_CONTROL ; 
 int CPSW_WR_INT_PACE_EN ; 
 int CPSW_WR_INT_PRESCALE_MASK ; 
 int /*<<< orphan*/  MDIOCONTROL ; 
 int MDIOCTL_ENABLE ; 
 int MDIOCTL_FAULTENB ; 
 struct cpsw_slot* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cpsw_softc*) ; 
 int cpsw_read_4 (struct cpsw_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_rx_enqueue (struct cpsw_softc*) ; 
 int /*<<< orphan*/  cpsw_tx_watchdog ; 
 int /*<<< orphan*/  cpsw_write_4 (struct cpsw_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpsw_write_hdp_slot (struct cpsw_softc*,TYPE_2__*,struct cpsw_slot*) ; 
 int /*<<< orphan*/  hz ; 

__attribute__((used)) static void
cpsw_init(struct cpsw_softc *sc)
{
	struct cpsw_slot *slot;
	uint32_t reg;

	/* Disable the interrupt pacing. */
	reg = cpsw_read_4(sc, CPSW_WR_INT_CONTROL);
	reg &= ~(CPSW_WR_INT_PACE_EN | CPSW_WR_INT_PRESCALE_MASK);
	cpsw_write_4(sc, CPSW_WR_INT_CONTROL, reg);

	/* Clear ALE */
	cpsw_write_4(sc, CPSW_ALE_CONTROL, CPSW_ALE_CTL_CLEAR_TBL);

	/* Enable ALE */
	reg = CPSW_ALE_CTL_ENABLE;
	if (sc->dualemac)
		reg |= CPSW_ALE_CTL_VLAN_AWARE;
	cpsw_write_4(sc, CPSW_ALE_CONTROL, reg);

	/* Set Host Port Mapping. */
	cpsw_write_4(sc, CPSW_PORT_P0_CPDMA_TX_PRI_MAP, 0x76543210);
	cpsw_write_4(sc, CPSW_PORT_P0_CPDMA_RX_CH_MAP, 0);

	/* Initialize ALE: set host port to forwarding(3). */
	cpsw_write_4(sc, CPSW_ALE_PORTCTL(0),
	    ALE_PORTCTL_INGRESS | ALE_PORTCTL_FORWARD);

	cpsw_write_4(sc, CPSW_SS_PTYPE, 0);

	/* Enable statistics for ports 0, 1 and 2 */
	cpsw_write_4(sc, CPSW_SS_STAT_PORT_EN, 7);

	/* Turn off flow control. */
	cpsw_write_4(sc, CPSW_SS_FLOW_CONTROL, 0);

	/* Make IP hdr aligned with 4 */
	cpsw_write_4(sc, CPSW_CPDMA_RX_BUFFER_OFFSET, 2);

	/* Initialize RX Buffer Descriptors */
	cpsw_write_4(sc, CPSW_CPDMA_RX_PENDTHRESH(0), 0);
	cpsw_write_4(sc, CPSW_CPDMA_RX_FREEBUFFER(0), 0);

	/* Enable TX & RX DMA */
	cpsw_write_4(sc, CPSW_CPDMA_TX_CONTROL, 1);
	cpsw_write_4(sc, CPSW_CPDMA_RX_CONTROL, 1);

	/* Enable Interrupts for core 0 */
	cpsw_write_4(sc, CPSW_WR_C_RX_THRESH_EN(0), 0xFF);
	cpsw_write_4(sc, CPSW_WR_C_RX_EN(0), 0xFF);
	cpsw_write_4(sc, CPSW_WR_C_TX_EN(0), 0xFF);
	cpsw_write_4(sc, CPSW_WR_C_MISC_EN(0), 0x1F);

	/* Enable host Error Interrupt */
	cpsw_write_4(sc, CPSW_CPDMA_DMA_INTMASK_SET, 3);

	/* Enable interrupts for RX and TX on Channel 0 */
	cpsw_write_4(sc, CPSW_CPDMA_RX_INTMASK_SET,
	    CPSW_CPDMA_RX_INT(0) | CPSW_CPDMA_RX_INT_THRESH(0));
	cpsw_write_4(sc, CPSW_CPDMA_TX_INTMASK_SET, 1);

	/* Initialze MDIO - ENABLE, PREAMBLE=0, FAULTENB, CLKDIV=0xFF */
	/* TODO Calculate MDCLK=CLK/(CLKDIV+1) */
	cpsw_write_4(sc, MDIOCONTROL, MDIOCTL_ENABLE | MDIOCTL_FAULTENB | 0xff);

	/* Select MII in GMII_SEL, Internal Delay mode */
	//ti_scm_reg_write_4(0x650, 0);

	/* Initialize active queues. */
	slot = STAILQ_FIRST(&sc->tx.active);
	if (slot != NULL)
		cpsw_write_hdp_slot(sc, &sc->tx, slot);
	slot = STAILQ_FIRST(&sc->rx.active);
	if (slot != NULL)
		cpsw_write_hdp_slot(sc, &sc->rx, slot);
	cpsw_rx_enqueue(sc);
	cpsw_write_4(sc, CPSW_CPDMA_RX_FREEBUFFER(0), sc->rx.active_queue_len);
	cpsw_write_4(sc, CPSW_CPDMA_RX_PENDTHRESH(0), CPSW_TXFRAGS);

	/* Activate network interface. */
	sc->rx.running = 1;
	sc->tx.running = 1;
	sc->watchdog.timer = 0;
	callout_init(&sc->watchdog.callout, 0);
	callout_reset(&sc->watchdog.callout, hz, cpsw_tx_watchdog, sc);
}