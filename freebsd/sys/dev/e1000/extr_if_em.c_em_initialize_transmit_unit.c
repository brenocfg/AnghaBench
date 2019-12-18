#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct tx_ring {int tx_paddr; int /*<<< orphan*/  csum_flags; } ;
struct em_tx_queue {struct tx_ring txr; } ;
struct e1000_tx_desc {int dummy; } ;
struct TYPE_9__ {int type; } ;
struct TYPE_6__ {int /*<<< orphan*/  media_type; } ;
struct e1000_hw {TYPE_4__ mac; TYPE_1__ phy; } ;
struct TYPE_7__ {int value; } ;
struct TYPE_8__ {int value; } ;
struct adapter {int tx_num_queues; struct e1000_hw hw; int /*<<< orphan*/  txd_cmd; TYPE_2__ tx_int_delay; TYPE_3__ tx_abs_int_delay; struct em_tx_queue* tx_queues; TYPE_5__* shared; } ;
typedef  TYPE_5__* if_softc_ctx_t ;
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  scalar_t__ caddr_t ;
struct TYPE_10__ {int* isc_ntxd; } ;

/* Variables and functions */
 int DEFAULT_80003ES2LAN_TIPG_IPGR2 ; 
 int DEFAULT_82542_TIPG_IPGR1 ; 
 int DEFAULT_82542_TIPG_IPGR2 ; 
 int DEFAULT_82542_TIPG_IPGT ; 
 int DEFAULT_82543_TIPG_IPGR1 ; 
 int DEFAULT_82543_TIPG_IPGR2 ; 
 int DEFAULT_82543_TIPG_IPGT_COPPER ; 
 int DEFAULT_82543_TIPG_IPGT_FIBER ; 
 int E1000_COLLISION_THRESHOLD ; 
 int E1000_CT_SHIFT ; 
 int /*<<< orphan*/  E1000_IOSFPC ; 
 int E1000_RCTL_RDMTS_HEX ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_TADV ; 
 int /*<<< orphan*/  E1000_TARC (int) ; 
 int E1000_TARC0_CB_MULTIQ_2_REQ ; 
 int E1000_TARC0_CB_MULTIQ_3_REQ ; 
 int /*<<< orphan*/  E1000_TCTL ; 
 int E1000_TCTL_CT ; 
 int E1000_TCTL_EN ; 
 int E1000_TCTL_MULR ; 
 int E1000_TCTL_PSP ; 
 int E1000_TCTL_RTLC ; 
 int /*<<< orphan*/  E1000_TDBAH (int) ; 
 int /*<<< orphan*/  E1000_TDBAL (int) ; 
 int /*<<< orphan*/  E1000_TDH (int) ; 
 int /*<<< orphan*/  E1000_TDLEN (int) ; 
 int /*<<< orphan*/  E1000_TDT (int) ; 
 int /*<<< orphan*/  E1000_TIDV ; 
 int /*<<< orphan*/  E1000_TIPG ; 
 int E1000_TIPG_IPGR1_SHIFT ; 
 int E1000_TIPG_IPGR2_SHIFT ; 
 int /*<<< orphan*/  E1000_TXDCTL (int) ; 
 int E1000_TXDCTL_GRAN ; 
 int /*<<< orphan*/  E1000_TXD_CMD_IDE ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HW_DEBUGOUT2 (char*,int,int) ; 
 int /*<<< orphan*/  INIT_DEBUGOUT (char*) ; 
 int TARC_COMPENSATION_MODE ; 
 int TARC_ERRATA_BIT ; 
 int TARC_MQ_FIX ; 
 int TARC_SPEED_MODE_BIT ; 
 int /*<<< orphan*/  bzero (scalar_t__,scalar_t__) ; 
#define  e1000_80003es2lan 129 
 int e1000_82540 ; 
#define  e1000_82542 128 
 scalar_t__ e1000_82571 ; 
 scalar_t__ e1000_82572 ; 
 int const e1000_82574 ; 
 int /*<<< orphan*/  e1000_media_type_fiber ; 
 int /*<<< orphan*/  e1000_media_type_internal_serdes ; 
 scalar_t__ e1000_pch_spt ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
em_initialize_transmit_unit(if_ctx_t ctx)
{
	struct adapter *adapter = iflib_get_softc(ctx);
	if_softc_ctx_t scctx = adapter->shared;
	struct em_tx_queue *que;
	struct tx_ring	*txr;
	struct e1000_hw	*hw = &adapter->hw;
	u32 tctl, txdctl = 0, tarc, tipg = 0;

	INIT_DEBUGOUT("em_initialize_transmit_unit: begin");

	for (int i = 0; i < adapter->tx_num_queues; i++, txr++) {
		u64 bus_addr;
		caddr_t offp, endp;

		que = &adapter->tx_queues[i];
		txr = &que->txr;
		bus_addr = txr->tx_paddr;

		/* Clear checksum offload context. */
		offp = (caddr_t)&txr->csum_flags;
		endp = (caddr_t)(txr + 1);
		bzero(offp, endp - offp);

		/* Base and Len of TX Ring */
		E1000_WRITE_REG(hw, E1000_TDLEN(i),
		    scctx->isc_ntxd[0] * sizeof(struct e1000_tx_desc));
		E1000_WRITE_REG(hw, E1000_TDBAH(i),
		    (u32)(bus_addr >> 32));
		E1000_WRITE_REG(hw, E1000_TDBAL(i),
		    (u32)bus_addr);
		/* Init the HEAD/TAIL indices */
		E1000_WRITE_REG(hw, E1000_TDT(i), 0);
		E1000_WRITE_REG(hw, E1000_TDH(i), 0);

		HW_DEBUGOUT2("Base = %x, Length = %x\n",
		    E1000_READ_REG(&adapter->hw, E1000_TDBAL(i)),
		    E1000_READ_REG(&adapter->hw, E1000_TDLEN(i)));

		txdctl = 0; /* clear txdctl */
		txdctl |= 0x1f; /* PTHRESH */
		txdctl |= 1 << 8; /* HTHRESH */
		txdctl |= 1 << 16;/* WTHRESH */
		txdctl |= 1 << 22; /* Reserved bit 22 must always be 1 */
		txdctl |= E1000_TXDCTL_GRAN;
		txdctl |= 1 << 25; /* LWTHRESH */

		E1000_WRITE_REG(hw, E1000_TXDCTL(i), txdctl);
	}

	/* Set the default values for the Tx Inter Packet Gap timer */
	switch (adapter->hw.mac.type) {
	case e1000_80003es2lan:
		tipg = DEFAULT_82543_TIPG_IPGR1;
		tipg |= DEFAULT_80003ES2LAN_TIPG_IPGR2 <<
		    E1000_TIPG_IPGR2_SHIFT;
		break;
	case e1000_82542:
		tipg = DEFAULT_82542_TIPG_IPGT;
		tipg |= DEFAULT_82542_TIPG_IPGR1 << E1000_TIPG_IPGR1_SHIFT;
		tipg |= DEFAULT_82542_TIPG_IPGR2 << E1000_TIPG_IPGR2_SHIFT;
		break;
	default:
		if ((adapter->hw.phy.media_type == e1000_media_type_fiber) ||
		    (adapter->hw.phy.media_type ==
		    e1000_media_type_internal_serdes))
			tipg = DEFAULT_82543_TIPG_IPGT_FIBER;
		else
			tipg = DEFAULT_82543_TIPG_IPGT_COPPER;
		tipg |= DEFAULT_82543_TIPG_IPGR1 << E1000_TIPG_IPGR1_SHIFT;
		tipg |= DEFAULT_82543_TIPG_IPGR2 << E1000_TIPG_IPGR2_SHIFT;
	}

	E1000_WRITE_REG(&adapter->hw, E1000_TIPG, tipg);
	E1000_WRITE_REG(&adapter->hw, E1000_TIDV, adapter->tx_int_delay.value);

	if(adapter->hw.mac.type >= e1000_82540)
		E1000_WRITE_REG(&adapter->hw, E1000_TADV,
		    adapter->tx_abs_int_delay.value);

	if ((adapter->hw.mac.type == e1000_82571) ||
	    (adapter->hw.mac.type == e1000_82572)) {
		tarc = E1000_READ_REG(&adapter->hw, E1000_TARC(0));
		tarc |= TARC_SPEED_MODE_BIT;
		E1000_WRITE_REG(&adapter->hw, E1000_TARC(0), tarc);
	} else if (adapter->hw.mac.type == e1000_80003es2lan) {
		/* errata: program both queues to unweighted RR */
		tarc = E1000_READ_REG(&adapter->hw, E1000_TARC(0));
		tarc |= 1;
		E1000_WRITE_REG(&adapter->hw, E1000_TARC(0), tarc);
		tarc = E1000_READ_REG(&adapter->hw, E1000_TARC(1));
		tarc |= 1;
		E1000_WRITE_REG(&adapter->hw, E1000_TARC(1), tarc);
	} else if (adapter->hw.mac.type == e1000_82574) {
		tarc = E1000_READ_REG(&adapter->hw, E1000_TARC(0));
		tarc |= TARC_ERRATA_BIT;
		if ( adapter->tx_num_queues > 1) {
			tarc |= (TARC_COMPENSATION_MODE | TARC_MQ_FIX);
			E1000_WRITE_REG(&adapter->hw, E1000_TARC(0), tarc);
			E1000_WRITE_REG(&adapter->hw, E1000_TARC(1), tarc);
		} else
			E1000_WRITE_REG(&adapter->hw, E1000_TARC(0), tarc);
	}

	if (adapter->tx_int_delay.value > 0)
		adapter->txd_cmd |= E1000_TXD_CMD_IDE;

	/* Program the Transmit Control Register */
	tctl = E1000_READ_REG(&adapter->hw, E1000_TCTL);
	tctl &= ~E1000_TCTL_CT;
	tctl |= (E1000_TCTL_PSP | E1000_TCTL_RTLC | E1000_TCTL_EN |
		   (E1000_COLLISION_THRESHOLD << E1000_CT_SHIFT));

	if (adapter->hw.mac.type >= e1000_82571)
		tctl |= E1000_TCTL_MULR;

	/* This write will effectively turn on the transmit unit. */
	E1000_WRITE_REG(&adapter->hw, E1000_TCTL, tctl);

	/* SPT and KBL errata workarounds */
	if (hw->mac.type == e1000_pch_spt) {
		u32 reg;
		reg = E1000_READ_REG(hw, E1000_IOSFPC);
		reg |= E1000_RCTL_RDMTS_HEX;
		E1000_WRITE_REG(hw, E1000_IOSFPC, reg);
		/* i218-i219 Specification Update 1.5.4.5 */
		reg = E1000_READ_REG(hw, E1000_TARC(0));
		reg &= ~E1000_TARC0_CB_MULTIQ_3_REQ;
		reg |= E1000_TARC0_CB_MULTIQ_2_REQ;
		E1000_WRITE_REG(hw, E1000_TARC(0), reg);
	}
}