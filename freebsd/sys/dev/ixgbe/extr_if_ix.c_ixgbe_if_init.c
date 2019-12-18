#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct tx_ring {int /*<<< orphan*/  me; } ;
struct rx_ring {int /*<<< orphan*/  me; } ;
struct TYPE_7__ {int (* identify ) (struct ixgbe_hw*) ;} ;
struct TYPE_8__ {scalar_t__ type; TYPE_3__ ops; } ;
struct TYPE_6__ {scalar_t__ type; int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {int rar_used_count; } ;
struct ixgbe_hw {TYPE_4__ phy; TYPE_2__ mac; TYPE_1__ addr_ctrl; } ;
struct ix_tx_queue {struct tx_ring txr; } ;
struct ix_rx_queue {struct rx_ring rxr; } ;
struct ifnet {scalar_t__ if_mtu; } ;
struct adapter {int max_frame_size; int num_tx_queues; int num_rx_queues; int feat_en; int /*<<< orphan*/  vector; struct ix_rx_queue* rx_queues; struct ix_tx_queue* tx_queues; scalar_t__ task_requests; int /*<<< orphan*/  rx_mbuf_sz; int /*<<< orphan*/  pool; struct ixgbe_hw hw; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ ETHERMTU ; 
 int /*<<< orphan*/  IF_LLADDR (struct ifnet*) ; 
 int /*<<< orphan*/  INIT_DEBUGOUT (char*) ; 
 int /*<<< orphan*/  IXGBE_CTRL_EXT ; 
 int IXGBE_CTRL_EXT_PFRSTD ; 
 int /*<<< orphan*/  IXGBE_EIAM ; 
 int /*<<< orphan*/  IXGBE_EIAM_EX (int) ; 
 int IXGBE_EICS_RTX_QUEUE ; 
 int /*<<< orphan*/  IXGBE_EITR (int /*<<< orphan*/ ) ; 
 int IXGBE_ERR_SFP_NOT_SUPPORTED ; 
 int /*<<< orphan*/  IXGBE_ETH_LENGTH_OF_ADDRESS ; 
 int IXGBE_FEATURE_SRIOV ; 
 int IXGBE_LINK_ITR ; 
 int /*<<< orphan*/  IXGBE_MHADD ; 
 int IXGBE_MHADD_MFS_MASK ; 
 int IXGBE_MHADD_MFS_SHIFT ; 
 int IXGBE_RAH_AV ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_RXCTRL ; 
 int IXGBE_RXCTRL_DMBYPS ; 
 int IXGBE_RXCTRL_RXEN ; 
 int /*<<< orphan*/  IXGBE_RXDCTL (int /*<<< orphan*/ ) ; 
 int IXGBE_RXDCTL_ENABLE ; 
 int /*<<< orphan*/  IXGBE_TXDCTL (int /*<<< orphan*/ ) ; 
 int IXGBE_TXDCTL_ENABLE ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iflib_get_dev (int /*<<< orphan*/ ) ; 
 struct ifnet* iflib_get_ifp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_get_rx_mbuf_sz (int /*<<< orphan*/ ) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_align_all_queue_indices (struct adapter*) ; 
 int /*<<< orphan*/  ixgbe_config_delay_values (struct adapter*) ; 
 int /*<<< orphan*/  ixgbe_config_dmac (struct adapter*) ; 
 int /*<<< orphan*/  ixgbe_config_gpie (struct adapter*) ; 
 int /*<<< orphan*/  ixgbe_config_link (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_configure_ivars (struct adapter*) ; 
 scalar_t__ ixgbe_enable_msix ; 
 int /*<<< orphan*/  ixgbe_enable_rx_dma (struct ixgbe_hw*,int) ; 
 int /*<<< orphan*/  ixgbe_if_enable_intr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_if_multi_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_init_fdir (struct adapter*) ; 
 int /*<<< orphan*/  ixgbe_init_hw (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_initialize_iov (struct adapter*) ; 
 int /*<<< orphan*/  ixgbe_initialize_receive_units (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_initialize_transmit_units (int /*<<< orphan*/ ) ; 
 scalar_t__ ixgbe_mac_82598EB ; 
 scalar_t__ ixgbe_phy_none ; 
 int /*<<< orphan*/  ixgbe_set_ivar (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ixgbe_set_phy_power (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_set_rar (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ixgbe_setup_vlan_hw_support (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_start_hw (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  msec_delay (int) ; 
 int stub1 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  wmb () ; 

void
ixgbe_if_init(if_ctx_t ctx)
{
	struct adapter     *adapter = iflib_get_softc(ctx);
	struct ifnet       *ifp = iflib_get_ifp(ctx);
	device_t           dev = iflib_get_dev(ctx);
	struct ixgbe_hw *hw = &adapter->hw;
	struct ix_rx_queue *rx_que;
	struct ix_tx_queue *tx_que;
	u32             txdctl, mhadd;
	u32             rxdctl, rxctrl;
	u32             ctrl_ext;

	int             i, j, err;

	INIT_DEBUGOUT("ixgbe_if_init: begin");

	/* Queue indices may change with IOV mode */
	ixgbe_align_all_queue_indices(adapter);

	/* reprogram the RAR[0] in case user changed it. */
	ixgbe_set_rar(hw, 0, hw->mac.addr, adapter->pool, IXGBE_RAH_AV);

	/* Get the latest mac address, User can use a LAA */
	bcopy(IF_LLADDR(ifp), hw->mac.addr, IXGBE_ETH_LENGTH_OF_ADDRESS);
	ixgbe_set_rar(hw, 0, hw->mac.addr, adapter->pool, 1);
	hw->addr_ctrl.rar_used_count = 1;

	ixgbe_init_hw(hw);

	ixgbe_initialize_iov(adapter);

	ixgbe_initialize_transmit_units(ctx);

	/* Setup Multicast table */
	ixgbe_if_multi_set(ctx);

	/* Determine the correct mbuf pool, based on frame size */
	adapter->rx_mbuf_sz = iflib_get_rx_mbuf_sz(ctx);

	/* Configure RX settings */
	ixgbe_initialize_receive_units(ctx);

	/*
	 * Initialize variable holding task enqueue requests
	 * from MSI-X interrupts
	 */
	adapter->task_requests = 0;

	/* Enable SDP & MSI-X interrupts based on adapter */
	ixgbe_config_gpie(adapter);

	/* Set MTU size */
	if (ifp->if_mtu > ETHERMTU) {
		/* aka IXGBE_MAXFRS on 82599 and newer */
		mhadd = IXGBE_READ_REG(hw, IXGBE_MHADD);
		mhadd &= ~IXGBE_MHADD_MFS_MASK;
		mhadd |= adapter->max_frame_size << IXGBE_MHADD_MFS_SHIFT;
		IXGBE_WRITE_REG(hw, IXGBE_MHADD, mhadd);
	}

	/* Now enable all the queues */
	for (i = 0, tx_que = adapter->tx_queues; i < adapter->num_tx_queues; i++, tx_que++) {
		struct tx_ring *txr = &tx_que->txr;

		txdctl = IXGBE_READ_REG(hw, IXGBE_TXDCTL(txr->me));
		txdctl |= IXGBE_TXDCTL_ENABLE;
		/* Set WTHRESH to 8, burst writeback */
		txdctl |= (8 << 16);
		/*
		 * When the internal queue falls below PTHRESH (32),
		 * start prefetching as long as there are at least
		 * HTHRESH (1) buffers ready. The values are taken
		 * from the Intel linux driver 3.8.21.
		 * Prefetching enables tx line rate even with 1 queue.
		 */
		txdctl |= (32 << 0) | (1 << 8);
		IXGBE_WRITE_REG(hw, IXGBE_TXDCTL(txr->me), txdctl);
	}

	for (i = 0, rx_que = adapter->rx_queues; i < adapter->num_rx_queues; i++, rx_que++) {
		struct rx_ring *rxr = &rx_que->rxr;

		rxdctl = IXGBE_READ_REG(hw, IXGBE_RXDCTL(rxr->me));
		if (hw->mac.type == ixgbe_mac_82598EB) {
			/*
			 * PTHRESH = 21
			 * HTHRESH = 4
			 * WTHRESH = 8
			 */
			rxdctl &= ~0x3FFFFF;
			rxdctl |= 0x080420;
		}
		rxdctl |= IXGBE_RXDCTL_ENABLE;
		IXGBE_WRITE_REG(hw, IXGBE_RXDCTL(rxr->me), rxdctl);
		for (j = 0; j < 10; j++) {
			if (IXGBE_READ_REG(hw, IXGBE_RXDCTL(rxr->me)) &
			    IXGBE_RXDCTL_ENABLE)
				break;
			else
				msec_delay(1);
		}
		wmb();
	}

	/* Enable Receive engine */
	rxctrl = IXGBE_READ_REG(hw, IXGBE_RXCTRL);
	if (hw->mac.type == ixgbe_mac_82598EB)
		rxctrl |= IXGBE_RXCTRL_DMBYPS;
	rxctrl |= IXGBE_RXCTRL_RXEN;
	ixgbe_enable_rx_dma(hw, rxctrl);

	/* Set up MSI/MSI-X routing */
	if (ixgbe_enable_msix)  {
		ixgbe_configure_ivars(adapter);
		/* Set up auto-mask */
		if (hw->mac.type == ixgbe_mac_82598EB)
			IXGBE_WRITE_REG(hw, IXGBE_EIAM, IXGBE_EICS_RTX_QUEUE);
		else {
			IXGBE_WRITE_REG(hw, IXGBE_EIAM_EX(0), 0xFFFFFFFF);
			IXGBE_WRITE_REG(hw, IXGBE_EIAM_EX(1), 0xFFFFFFFF);
		}
	} else {  /* Simple settings for Legacy/MSI */
		ixgbe_set_ivar(adapter, 0, 0, 0);
		ixgbe_set_ivar(adapter, 0, 0, 1);
		IXGBE_WRITE_REG(hw, IXGBE_EIAM, IXGBE_EICS_RTX_QUEUE);
	}

	ixgbe_init_fdir(adapter);

	/*
	 * Check on any SFP devices that
	 * need to be kick-started
	 */
	if (hw->phy.type == ixgbe_phy_none) {
		err = hw->phy.ops.identify(hw);
		if (err == IXGBE_ERR_SFP_NOT_SUPPORTED) {
			device_printf(dev,
			    "Unsupported SFP+ module type was detected.\n");
			return;
		}
	}

	/* Set moderation on the Link interrupt */
	IXGBE_WRITE_REG(hw, IXGBE_EITR(adapter->vector), IXGBE_LINK_ITR);

	/* Enable power to the phy. */
	ixgbe_set_phy_power(hw, TRUE);

	/* Config/Enable Link */
	ixgbe_config_link(ctx);

	/* Hardware Packet Buffer & Flow Control setup */
	ixgbe_config_delay_values(adapter);

	/* Initialize the FC settings */
	ixgbe_start_hw(hw);

	/* Set up VLAN support and filter */
	ixgbe_setup_vlan_hw_support(ctx);

	/* Setup DMA Coalescing */
	ixgbe_config_dmac(adapter);

	/* And now turn on interrupts */
	ixgbe_if_enable_intr(ctx);

	/* Enable the use of the MBX by the VF's */
	if (adapter->feat_en & IXGBE_FEATURE_SRIOV) {
		ctrl_ext = IXGBE_READ_REG(hw, IXGBE_CTRL_EXT);
		ctrl_ext |= IXGBE_CTRL_EXT_PFRSTD;
		IXGBE_WRITE_REG(hw, IXGBE_CTRL_EXT, ctrl_ext);
	}

}