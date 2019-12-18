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
typedef  union ixgbe_adv_rx_desc {int dummy; } ixgbe_adv_rx_desc ;
typedef  int u64 ;
typedef  int u32 ;
struct rx_ring {int rx_paddr; int me; int /*<<< orphan*/  tail; } ;
struct netmap_kring {int dummy; } ;
struct netmap_adapter {int num_rx_desc; struct netmap_kring** rx_rings; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
struct ix_rx_queue {struct rx_ring rxr; } ;
struct ifnet {scalar_t__ if_mtu; int if_capenable; } ;
struct adapter {int num_rx_queues; struct ixgbe_hw hw; TYPE_2__* shared; int /*<<< orphan*/  dev; int /*<<< orphan*/  max_frame_size; struct ix_rx_queue* rx_queues; } ;
typedef  TYPE_2__* if_softc_ctx_t ;
typedef  int /*<<< orphan*/  if_ctx_t ;
struct TYPE_4__ {int* isc_nrxd; } ;

/* Variables and functions */
 scalar_t__ ETHERMTU ; 
 int IFCAP_NETMAP ; 
 int IXGBE_PSRTYPE_IPV4HDR ; 
 int IXGBE_PSRTYPE_IPV6HDR ; 
 int IXGBE_PSRTYPE_L2HDR ; 
 int IXGBE_PSRTYPE_TCPHDR ; 
 int IXGBE_PSRTYPE_UDPHDR ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int IXGBE_RXDCTL_ENABLE ; 
 int IXGBE_RXDCTL_VME ; 
 int IXGBE_SRRCTL_BSIZEHDR_MASK ; 
 int IXGBE_SRRCTL_BSIZEPKT_MASK ; 
 int IXGBE_SRRCTL_BSIZEPKT_SHIFT ; 
 int IXGBE_SRRCTL_DESCTYPE_ADV_ONEBUF ; 
 int /*<<< orphan*/  IXGBE_VFPSRTYPE ; 
 int /*<<< orphan*/  IXGBE_VFRDBAH (int) ; 
 int /*<<< orphan*/  IXGBE_VFRDBAL (int) ; 
 int /*<<< orphan*/  IXGBE_VFRDH (int) ; 
 int /*<<< orphan*/  IXGBE_VFRDLEN (int) ; 
 int /*<<< orphan*/  IXGBE_VFRDT (int) ; 
 int /*<<< orphan*/  IXGBE_VFRXDCTL (int) ; 
 int /*<<< orphan*/  IXGBE_VFSRRCTL (int) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 struct netmap_adapter* NA (struct ifnet*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 struct ifnet* iflib_get_ifp (int /*<<< orphan*/ ) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ ixgbe_mac_X550_vf ; 
 scalar_t__ ixgbevf_rlpml_set_vf (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixv_initialize_rss_mapping (struct adapter*) ; 
 int /*<<< orphan*/  msec_delay (int) ; 
 int nm_kr_rxspace (struct netmap_kring*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void
ixv_initialize_receive_units(if_ctx_t ctx)
{
	struct adapter     *adapter = iflib_get_softc(ctx);
	if_softc_ctx_t     scctx;
	struct ixgbe_hw    *hw = &adapter->hw;
	struct ifnet       *ifp = iflib_get_ifp(ctx);
	struct ix_rx_queue *que = adapter->rx_queues;
	u32                bufsz, psrtype;

	if (ifp->if_mtu > ETHERMTU)
		bufsz = 4096 >> IXGBE_SRRCTL_BSIZEPKT_SHIFT;
	else
		bufsz = 2048 >> IXGBE_SRRCTL_BSIZEPKT_SHIFT;

	psrtype = IXGBE_PSRTYPE_TCPHDR
	        | IXGBE_PSRTYPE_UDPHDR
	        | IXGBE_PSRTYPE_IPV4HDR
	        | IXGBE_PSRTYPE_IPV6HDR
	        | IXGBE_PSRTYPE_L2HDR;

	if (adapter->num_rx_queues > 1)
		psrtype |= 1 << 29;

	IXGBE_WRITE_REG(hw, IXGBE_VFPSRTYPE, psrtype);

	/* Tell PF our max_frame size */
	if (ixgbevf_rlpml_set_vf(hw, adapter->max_frame_size) != 0) {
		device_printf(adapter->dev, "There is a problem with the PF setup.  It is likely the receive unit for this VF will not function correctly.\n");
	}
	scctx = adapter->shared;

	for (int i = 0; i < adapter->num_rx_queues; i++, que++) {
		struct rx_ring *rxr = &que->rxr;
		u64            rdba = rxr->rx_paddr;
		u32            reg, rxdctl;
		int            j = rxr->me;

		/* Disable the queue */
		rxdctl = IXGBE_READ_REG(hw, IXGBE_VFRXDCTL(j));
		rxdctl &= ~IXGBE_RXDCTL_ENABLE;
		IXGBE_WRITE_REG(hw, IXGBE_VFRXDCTL(j), rxdctl);
		for (int k = 0; k < 10; k++) {
			if (IXGBE_READ_REG(hw, IXGBE_VFRXDCTL(j)) &
			    IXGBE_RXDCTL_ENABLE)
				msec_delay(1);
			else
				break;
		}
		wmb();
		/* Setup the Base and Length of the Rx Descriptor Ring */
		IXGBE_WRITE_REG(hw, IXGBE_VFRDBAL(j),
		    (rdba & 0x00000000ffffffffULL));
		IXGBE_WRITE_REG(hw, IXGBE_VFRDBAH(j), (rdba >> 32));
		IXGBE_WRITE_REG(hw, IXGBE_VFRDLEN(j),
		    scctx->isc_nrxd[0] * sizeof(union ixgbe_adv_rx_desc));

		/* Reset the ring indices */
		IXGBE_WRITE_REG(hw, IXGBE_VFRDH(rxr->me), 0);
		IXGBE_WRITE_REG(hw, IXGBE_VFRDT(rxr->me), 0);

		/* Set up the SRRCTL register */
		reg = IXGBE_READ_REG(hw, IXGBE_VFSRRCTL(j));
		reg &= ~IXGBE_SRRCTL_BSIZEHDR_MASK;
		reg &= ~IXGBE_SRRCTL_BSIZEPKT_MASK;
		reg |= bufsz;
		reg |= IXGBE_SRRCTL_DESCTYPE_ADV_ONEBUF;
		IXGBE_WRITE_REG(hw, IXGBE_VFSRRCTL(j), reg);

		/* Capture Rx Tail index */
		rxr->tail = IXGBE_VFRDT(rxr->me);

		/* Do the queue enabling last */
		rxdctl |= IXGBE_RXDCTL_ENABLE | IXGBE_RXDCTL_VME;
		IXGBE_WRITE_REG(hw, IXGBE_VFRXDCTL(j), rxdctl);
		for (int l = 0; l < 10; l++) {
			if (IXGBE_READ_REG(hw, IXGBE_VFRXDCTL(j)) &
			    IXGBE_RXDCTL_ENABLE)
				break;
			msec_delay(1);
		}
		wmb();

		/* Set the Tail Pointer */
#ifdef DEV_NETMAP
		/*
		 * In netmap mode, we must preserve the buffers made
		 * available to userspace before the if_init()
		 * (this is true by default on the TX side, because
		 * init makes all buffers available to userspace).
		 *
		 * netmap_reset() and the device specific routines
		 * (e.g. ixgbe_setup_receive_rings()) map these
		 * buffers at the end of the NIC ring, so here we
		 * must set the RDT (tail) register to make sure
		 * they are not overwritten.
		 *
		 * In this driver the NIC ring starts at RDH = 0,
		 * RDT points to the last slot available for reception (?),
		 * so RDT = num_rx_desc - 1 means the whole ring is available.
		 */
		if (ifp->if_capenable & IFCAP_NETMAP) {
			struct netmap_adapter *na = NA(ifp);
			struct netmap_kring *kring = na->rx_rings[j];
			int t = na->num_rx_desc - 1 - nm_kr_rxspace(kring);

			IXGBE_WRITE_REG(hw, IXGBE_VFRDT(rxr->me), t);
		} else
#endif /* DEV_NETMAP */
			IXGBE_WRITE_REG(hw, IXGBE_VFRDT(rxr->me),
			    scctx->isc_nrxd[0] - 1);
	}

	/*
	 * Do not touch RSS and RETA settings for older hardware
	 * as those are shared among PF and all VF.
	 */
	if (adapter->hw.mac.type >= ixgbe_mac_X550_vf)
		ixv_initialize_rss_mapping(adapter);
}