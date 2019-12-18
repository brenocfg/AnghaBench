#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct tx_ring {scalar_t__ tx_cidx_processed; int /*<<< orphan*/  tx_rs_pidx; int /*<<< orphan*/  tx_rs_cidx; } ;
struct ifnet {int dummy; } ;
struct em_tx_queue {struct tx_ring txr; } ;
struct TYPE_13__ {scalar_t__ type; int /*<<< orphan*/  addr; } ;
struct TYPE_12__ {scalar_t__ media_type; } ;
struct TYPE_15__ {TYPE_2__ mac; TYPE_1__ phy; } ;
struct adapter {int tx_num_queues; int ivars; scalar_t__ intr_type; TYPE_4__ hw; scalar_t__ has_amt; scalar_t__ has_manage; int /*<<< orphan*/  rx_mbuf_sz; struct em_tx_queue* tx_queues; TYPE_3__* shared; } ;
typedef  TYPE_3__* if_softc_ctx_t ;
typedef  int /*<<< orphan*/  if_ctx_t ;
struct TYPE_14__ {scalar_t__* isc_ntxd; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_CTRL ; 
 int /*<<< orphan*/  E1000_CTRL_EXT ; 
 int E1000_CTRL_EXT_PBA_CLR ; 
 int E1000_CTRL_VME ; 
 int /*<<< orphan*/  E1000_ICR ; 
 int /*<<< orphan*/  E1000_ICS ; 
 int E1000_ICS_LSC ; 
 int /*<<< orphan*/  E1000_IVAR ; 
 scalar_t__ E1000_RAR_ENTRIES ; 
 int E1000_READ_REG (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_VET ; 
 int /*<<< orphan*/  E1000_WRITE_REG (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int ETHERTYPE_VLAN ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int IFCAP_VLAN_HWFILTER ; 
 int IFCAP_VLAN_HWTAGGING ; 
 int /*<<< orphan*/  IFF_PROMISC ; 
 scalar_t__ IFLIB_INTR_MSIX ; 
 int /*<<< orphan*/  INIT_DEBUGOUT (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ e1000_82571 ; 
 scalar_t__ e1000_82574 ; 
 int /*<<< orphan*/  e1000_clear_hw_cntrs_base_generic (TYPE_4__*) ; 
 scalar_t__ e1000_i354 ; 
 scalar_t__ e1000_media_type_copper ; 
 int /*<<< orphan*/  e1000_rar_set (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  e1000_rx_fifo_flush_82575 (TYPE_4__*) ; 
 int /*<<< orphan*/  e1000_set_eee_i350 (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e1000_set_eee_i354 (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e1000_set_laa_state_82571 (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  em_get_hw_control (struct adapter*) ; 
 int /*<<< orphan*/  em_if_multi_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  em_if_set_promisc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  em_if_update_admin_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  em_init_manageability (struct adapter*) ; 
 int /*<<< orphan*/  em_initialize_receive_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  em_initialize_transmit_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  em_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  em_setup_vlan_hw_support (struct adapter*) ; 
 int if_getcapenable (struct ifnet*) ; 
 int /*<<< orphan*/  if_getlladdr (struct ifnet*) ; 
 struct ifnet* iflib_get_ifp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_get_rx_mbuf_sz (int /*<<< orphan*/ ) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igb_configure_queues (struct adapter*) ; 
 scalar_t__ igb_mac_min ; 

__attribute__((used)) static void
em_if_init(if_ctx_t ctx)
{
	struct adapter *adapter = iflib_get_softc(ctx);
	if_softc_ctx_t scctx = adapter->shared;
	struct ifnet *ifp = iflib_get_ifp(ctx);
	struct em_tx_queue *tx_que;
	int i;

	INIT_DEBUGOUT("em_if_init: begin");

	/* Get the latest mac address, User can use a LAA */
	bcopy(if_getlladdr(ifp), adapter->hw.mac.addr,
	    ETHER_ADDR_LEN);

	/* Put the address into the Receive Address Array */
	e1000_rar_set(&adapter->hw, adapter->hw.mac.addr, 0);

	/*
	 * With the 82571 adapter, RAR[0] may be overwritten
	 * when the other port is reset, we make a duplicate
	 * in RAR[14] for that eventuality, this assures
	 * the interface continues to function.
	 */
	if (adapter->hw.mac.type == e1000_82571) {
		e1000_set_laa_state_82571(&adapter->hw, TRUE);
		e1000_rar_set(&adapter->hw, adapter->hw.mac.addr,
		    E1000_RAR_ENTRIES - 1);
	}


	/* Initialize the hardware */
	em_reset(ctx);
	em_if_update_admin_status(ctx);

	for (i = 0, tx_que = adapter->tx_queues; i < adapter->tx_num_queues; i++, tx_que++) {
		struct tx_ring *txr = &tx_que->txr;

		txr->tx_rs_cidx = txr->tx_rs_pidx;

		/* Initialize the last processed descriptor to be the end of
		 * the ring, rather than the start, so that we avoid an
		 * off-by-one error when calculating how many descriptors are
		 * done in the credits_update function.
		 */
		txr->tx_cidx_processed = scctx->isc_ntxd[0] - 1;
	}

	/* Setup VLAN support, basic and offload if available */
	E1000_WRITE_REG(&adapter->hw, E1000_VET, ETHERTYPE_VLAN);

	/* Clear bad data from Rx FIFOs */
	if (adapter->hw.mac.type >= igb_mac_min)
		e1000_rx_fifo_flush_82575(&adapter->hw);

	/* Configure for OS presence */
	em_init_manageability(adapter);

	/* Prepare transmit descriptors and buffers */
	em_initialize_transmit_unit(ctx);

	/* Setup Multicast table */
	em_if_multi_set(ctx);

	adapter->rx_mbuf_sz = iflib_get_rx_mbuf_sz(ctx);
	em_initialize_receive_unit(ctx);

	/* Use real VLAN Filter support? */
	if (if_getcapenable(ifp) & IFCAP_VLAN_HWTAGGING) {
		if (if_getcapenable(ifp) & IFCAP_VLAN_HWFILTER)
			/* Use real VLAN Filter support */
			em_setup_vlan_hw_support(adapter);
		else {
			u32 ctrl;
			ctrl = E1000_READ_REG(&adapter->hw, E1000_CTRL);
			ctrl |= E1000_CTRL_VME;
			E1000_WRITE_REG(&adapter->hw, E1000_CTRL, ctrl);
		}
	}

	/* Don't lose promiscuous settings */
	em_if_set_promisc(ctx, IFF_PROMISC);
	e1000_clear_hw_cntrs_base_generic(&adapter->hw);

	/* MSI-X configuration for 82574 */
	if (adapter->hw.mac.type == e1000_82574) {
		int tmp = E1000_READ_REG(&adapter->hw, E1000_CTRL_EXT);

		tmp |= E1000_CTRL_EXT_PBA_CLR;
		E1000_WRITE_REG(&adapter->hw, E1000_CTRL_EXT, tmp);
		/* Set the IVAR - interrupt vector routing. */
		E1000_WRITE_REG(&adapter->hw, E1000_IVAR, adapter->ivars);
	} else if (adapter->intr_type == IFLIB_INTR_MSIX) /* Set up queue routing */
		igb_configure_queues(adapter);

	/* this clears any pending interrupts */
	E1000_READ_REG(&adapter->hw, E1000_ICR);
	E1000_WRITE_REG(&adapter->hw, E1000_ICS, E1000_ICS_LSC);

	/* AMT based hardware can now take control from firmware */
	if (adapter->has_manage && adapter->has_amt)
		em_get_hw_control(adapter);

	/* Set Energy Efficient Ethernet */
	if (adapter->hw.mac.type >= igb_mac_min &&
	    adapter->hw.phy.media_type == e1000_media_type_copper) {
		if (adapter->hw.mac.type == e1000_i354)
			e1000_set_eee_i354(&adapter->hw, TRUE, TRUE);
		else
			e1000_set_eee_i350(&adapter->hw, TRUE, TRUE);
	}
}