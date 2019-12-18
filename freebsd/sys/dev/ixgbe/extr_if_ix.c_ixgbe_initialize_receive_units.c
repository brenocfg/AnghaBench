#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  union ixgbe_adv_rx_desc {int dummy; } ixgbe_adv_rx_desc ;
typedef  int u64 ;
typedef  int u32 ;
struct rx_ring {int rx_paddr; int me; int /*<<< orphan*/  tail; } ;
struct TYPE_5__ {scalar_t__ type; } ;
struct TYPE_4__ {scalar_t__ requested_mode; } ;
struct ixgbe_hw {TYPE_2__ mac; TYPE_1__ fc; } ;
struct ix_rx_queue {struct rx_ring rxr; } ;
struct ifnet {scalar_t__ if_mtu; int if_capenable; } ;
struct adapter {int rx_mbuf_sz; int num_rx_queues; struct ixgbe_hw hw; struct ix_rx_queue* rx_queues; TYPE_3__* shared; } ;
typedef  TYPE_3__* if_softc_ctx_t ;
typedef  int /*<<< orphan*/  if_ctx_t ;
struct TYPE_6__ {int* isc_nrxd; } ;

/* Variables and functions */
 int BSIZEPKT_ROUNDUP ; 
 scalar_t__ ETHERMTU ; 
 int IFCAP_RXCSUM ; 
 int /*<<< orphan*/  IXGBE_FCTRL ; 
 int IXGBE_FCTRL_BAM ; 
 int IXGBE_FCTRL_DPF ; 
 int IXGBE_FCTRL_PMCF ; 
 int /*<<< orphan*/  IXGBE_HLREG0 ; 
 int IXGBE_HLREG0_JUMBOEN ; 
 int /*<<< orphan*/  IXGBE_PSRTYPE (int /*<<< orphan*/ ) ; 
 int IXGBE_PSRTYPE_IPV4HDR ; 
 int IXGBE_PSRTYPE_IPV6HDR ; 
 int IXGBE_PSRTYPE_TCPHDR ; 
 int IXGBE_PSRTYPE_UDPHDR ; 
 int /*<<< orphan*/  IXGBE_RDBAH (int) ; 
 int /*<<< orphan*/  IXGBE_RDBAL (int) ; 
 int /*<<< orphan*/  IXGBE_RDH (int) ; 
 int /*<<< orphan*/  IXGBE_RDLEN (int) ; 
 int /*<<< orphan*/  IXGBE_RDT (int) ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_RXCSUM ; 
 int IXGBE_RXCSUM_IPPCSE ; 
 int IXGBE_RXCSUM_PCSD ; 
 int /*<<< orphan*/  IXGBE_SRRCTL (int) ; 
 int IXGBE_SRRCTL_BSIZEHDR_MASK ; 
 int IXGBE_SRRCTL_BSIZEPKT_MASK ; 
 int IXGBE_SRRCTL_BSIZEPKT_SHIFT ; 
 int IXGBE_SRRCTL_DESCTYPE_ADV_ONEBUF ; 
 int IXGBE_SRRCTL_DROP_EN ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 struct ifnet* iflib_get_ifp (int /*<<< orphan*/ ) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_disable_rx (struct ixgbe_hw*) ; 
 scalar_t__ ixgbe_fc_none ; 
 int /*<<< orphan*/  ixgbe_initialize_rss_mapping (struct adapter*) ; 
 scalar_t__ ixgbe_mac_82598EB ; 

__attribute__((used)) static void
ixgbe_initialize_receive_units(if_ctx_t ctx)
{
	struct adapter     *adapter = iflib_get_softc(ctx);
	if_softc_ctx_t     scctx = adapter->shared;
	struct ixgbe_hw    *hw = &adapter->hw;
	struct ifnet       *ifp = iflib_get_ifp(ctx);
	struct ix_rx_queue *que;
	int                i, j;
	u32                bufsz, fctrl, srrctl, rxcsum;
	u32                hlreg;

	/*
	 * Make sure receives are disabled while
	 * setting up the descriptor ring
	 */
	ixgbe_disable_rx(hw);

	/* Enable broadcasts */
	fctrl = IXGBE_READ_REG(hw, IXGBE_FCTRL);
	fctrl |= IXGBE_FCTRL_BAM;
	if (adapter->hw.mac.type == ixgbe_mac_82598EB) {
		fctrl |= IXGBE_FCTRL_DPF;
		fctrl |= IXGBE_FCTRL_PMCF;
	}
	IXGBE_WRITE_REG(hw, IXGBE_FCTRL, fctrl);

	/* Set for Jumbo Frames? */
	hlreg = IXGBE_READ_REG(hw, IXGBE_HLREG0);
	if (ifp->if_mtu > ETHERMTU)
		hlreg |= IXGBE_HLREG0_JUMBOEN;
	else
		hlreg &= ~IXGBE_HLREG0_JUMBOEN;
	IXGBE_WRITE_REG(hw, IXGBE_HLREG0, hlreg);

	bufsz = (adapter->rx_mbuf_sz + BSIZEPKT_ROUNDUP) >>
	    IXGBE_SRRCTL_BSIZEPKT_SHIFT;

	/* Setup the Base and Length of the Rx Descriptor Ring */
	for (i = 0, que = adapter->rx_queues; i < adapter->num_rx_queues; i++, que++) {
		struct rx_ring *rxr = &que->rxr;
		u64            rdba = rxr->rx_paddr;

		j = rxr->me;

		/* Setup the Base and Length of the Rx Descriptor Ring */
		IXGBE_WRITE_REG(hw, IXGBE_RDBAL(j),
		    (rdba & 0x00000000ffffffffULL));
		IXGBE_WRITE_REG(hw, IXGBE_RDBAH(j), (rdba >> 32));
		IXGBE_WRITE_REG(hw, IXGBE_RDLEN(j),
		     scctx->isc_nrxd[0] * sizeof(union ixgbe_adv_rx_desc));

		/* Set up the SRRCTL register */
		srrctl = IXGBE_READ_REG(hw, IXGBE_SRRCTL(j));
		srrctl &= ~IXGBE_SRRCTL_BSIZEHDR_MASK;
		srrctl &= ~IXGBE_SRRCTL_BSIZEPKT_MASK;
		srrctl |= bufsz;
		srrctl |= IXGBE_SRRCTL_DESCTYPE_ADV_ONEBUF;

		/*
		 * Set DROP_EN iff we have no flow control and >1 queue.
		 * Note that srrctl was cleared shortly before during reset,
		 * so we do not need to clear the bit, but do it just in case
		 * this code is moved elsewhere.
		 */
		if (adapter->num_rx_queues > 1 &&
		    adapter->hw.fc.requested_mode == ixgbe_fc_none) {
			srrctl |= IXGBE_SRRCTL_DROP_EN;
		} else {
			srrctl &= ~IXGBE_SRRCTL_DROP_EN;
		}

		IXGBE_WRITE_REG(hw, IXGBE_SRRCTL(j), srrctl);

		/* Setup the HW Rx Head and Tail Descriptor Pointers */
		IXGBE_WRITE_REG(hw, IXGBE_RDH(j), 0);
		IXGBE_WRITE_REG(hw, IXGBE_RDT(j), 0);

		/* Set the driver rx tail address */
		rxr->tail =  IXGBE_RDT(rxr->me);
	}

	if (adapter->hw.mac.type != ixgbe_mac_82598EB) {
		u32 psrtype = IXGBE_PSRTYPE_TCPHDR
		            | IXGBE_PSRTYPE_UDPHDR
		            | IXGBE_PSRTYPE_IPV4HDR
		            | IXGBE_PSRTYPE_IPV6HDR;
		IXGBE_WRITE_REG(hw, IXGBE_PSRTYPE(0), psrtype);
	}

	rxcsum = IXGBE_READ_REG(hw, IXGBE_RXCSUM);

	ixgbe_initialize_rss_mapping(adapter);

	if (adapter->num_rx_queues > 1) {
		/* RSS and RX IPP Checksum are mutually exclusive */
		rxcsum |= IXGBE_RXCSUM_PCSD;
	}

	if (ifp->if_capenable & IFCAP_RXCSUM)
		rxcsum |= IXGBE_RXCSUM_PCSD;

	/* This is useful for calculating UDP/IP fragment checksums */
	if (!(rxcsum & IXGBE_RXCSUM_PCSD))
		rxcsum |= IXGBE_RXCSUM_IPPCSE;

	IXGBE_WRITE_REG(hw, IXGBE_RXCSUM, rxcsum);

}