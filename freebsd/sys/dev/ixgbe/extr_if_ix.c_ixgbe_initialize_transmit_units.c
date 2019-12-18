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
typedef  union ixgbe_adv_tx_desc {int dummy; } ixgbe_adv_tx_desc ;
typedef  int u64 ;
typedef  int u32 ;
struct tx_ring {int tx_paddr; int me; int tx_cidx_processed; int /*<<< orphan*/ * tx_rsq; int /*<<< orphan*/  tx_rs_pidx; int /*<<< orphan*/  tx_rs_cidx; int /*<<< orphan*/  tail; } ;
struct TYPE_3__ {int type; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
struct ix_tx_queue {struct tx_ring txr; } ;
struct adapter {int num_tx_queues; int /*<<< orphan*/  iov_mode; struct ix_tx_queue* tx_queues; TYPE_2__* shared; struct ixgbe_hw hw; } ;
typedef  TYPE_2__* if_softc_ctx_t ;
typedef  int /*<<< orphan*/  if_ctx_t ;
struct TYPE_4__ {int* isc_ntxd; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_DCA_TXCTRL (int) ; 
 int /*<<< orphan*/  IXGBE_DCA_TXCTRL_82599 (int) ; 
 int IXGBE_DCA_TXCTRL_DESC_WRO_EN ; 
 int /*<<< orphan*/  IXGBE_DMATXCTL ; 
 int IXGBE_DMATXCTL_TE ; 
 int /*<<< orphan*/  IXGBE_MTQC ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_RTTDCS ; 
 int IXGBE_RTTDCS_ARBDIS ; 
 int /*<<< orphan*/  IXGBE_TDBAH (int) ; 
 int /*<<< orphan*/  IXGBE_TDBAL (int) ; 
 int /*<<< orphan*/  IXGBE_TDH (int) ; 
 int /*<<< orphan*/  IXGBE_TDLEN (int) ; 
 int /*<<< orphan*/  IXGBE_TDT (int) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  QIDX_INVALID ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int ixgbe_get_mtqc (int /*<<< orphan*/ ) ; 
#define  ixgbe_mac_82598EB 128 

__attribute__((used)) static void
ixgbe_initialize_transmit_units(if_ctx_t ctx)
{
	struct adapter     *adapter = iflib_get_softc(ctx);
	struct ixgbe_hw    *hw = &adapter->hw;
	if_softc_ctx_t     scctx = adapter->shared;
	struct ix_tx_queue *que;
	int i;

	/* Setup the Base and Length of the Tx Descriptor Ring */
	for (i = 0, que = adapter->tx_queues; i < adapter->num_tx_queues;
	    i++, que++) {
		struct tx_ring	   *txr = &que->txr;
		u64 tdba = txr->tx_paddr;
		u32 txctrl = 0;
		int j = txr->me;

		IXGBE_WRITE_REG(hw, IXGBE_TDBAL(j),
		    (tdba & 0x00000000ffffffffULL));
		IXGBE_WRITE_REG(hw, IXGBE_TDBAH(j), (tdba >> 32));
		IXGBE_WRITE_REG(hw, IXGBE_TDLEN(j),
		    scctx->isc_ntxd[0] * sizeof(union ixgbe_adv_tx_desc));

		/* Setup the HW Tx Head and Tail descriptor pointers */
		IXGBE_WRITE_REG(hw, IXGBE_TDH(j), 0);
		IXGBE_WRITE_REG(hw, IXGBE_TDT(j), 0);

		/* Cache the tail address */
		txr->tail = IXGBE_TDT(txr->me);

		txr->tx_rs_cidx = txr->tx_rs_pidx;
		txr->tx_cidx_processed = scctx->isc_ntxd[0] - 1;
		for (int k = 0; k < scctx->isc_ntxd[0]; k++)
			txr->tx_rsq[k] = QIDX_INVALID;

		/* Disable Head Writeback */
		/*
		 * Note: for X550 series devices, these registers are actually
		 * prefixed with TPH_ isntead of DCA_, but the addresses and
		 * fields remain the same.
		 */
		switch (hw->mac.type) {
		case ixgbe_mac_82598EB:
			txctrl = IXGBE_READ_REG(hw, IXGBE_DCA_TXCTRL(j));
			break;
		default:
			txctrl = IXGBE_READ_REG(hw, IXGBE_DCA_TXCTRL_82599(j));
			break;
		}
		txctrl &= ~IXGBE_DCA_TXCTRL_DESC_WRO_EN;
		switch (hw->mac.type) {
		case ixgbe_mac_82598EB:
			IXGBE_WRITE_REG(hw, IXGBE_DCA_TXCTRL(j), txctrl);
			break;
		default:
			IXGBE_WRITE_REG(hw, IXGBE_DCA_TXCTRL_82599(j), txctrl);
			break;
		}

	}

	if (hw->mac.type != ixgbe_mac_82598EB) {
		u32 dmatxctl, rttdcs;

		dmatxctl = IXGBE_READ_REG(hw, IXGBE_DMATXCTL);
		dmatxctl |= IXGBE_DMATXCTL_TE;
		IXGBE_WRITE_REG(hw, IXGBE_DMATXCTL, dmatxctl);
		/* Disable arbiter to set MTQC */
		rttdcs = IXGBE_READ_REG(hw, IXGBE_RTTDCS);
		rttdcs |= IXGBE_RTTDCS_ARBDIS;
		IXGBE_WRITE_REG(hw, IXGBE_RTTDCS, rttdcs);
		IXGBE_WRITE_REG(hw, IXGBE_MTQC,
		    ixgbe_get_mtqc(adapter->iov_mode));
		rttdcs &= ~IXGBE_RTTDCS_ARBDIS;
		IXGBE_WRITE_REG(hw, IXGBE_RTTDCS, rttdcs);
	}

}