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
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int type; } ;
struct ixgbe_hw {TYPE_2__ phy; int /*<<< orphan*/  device_id; TYPE_1__ mac; } ;
struct ix_rx_queue {int /*<<< orphan*/  msix; } ;
struct adapter {int feat_en; scalar_t__ intr_type; int feat_cap; int num_rx_queues; struct ixgbe_hw hw; struct ix_rx_queue* rx_queues; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 scalar_t__ IFLIB_INTR_MSIX ; 
 int /*<<< orphan*/  IXGBE_DEV_ID_X550EM_A_SFP ; 
 int /*<<< orphan*/  IXGBE_DEV_ID_X550EM_A_SFP_N ; 
 int /*<<< orphan*/  IXGBE_DEV_ID_X550EM_X_10G_T ; 
 int /*<<< orphan*/  IXGBE_DEV_ID_X550EM_X_SFP ; 
 int /*<<< orphan*/  IXGBE_EIAC ; 
 int IXGBE_EICR_GPI_SDP0_X540 ; 
 int /*<<< orphan*/  IXGBE_EIMS ; 
 int IXGBE_EIMS_ECC ; 
 int IXGBE_EIMS_ENABLE_MASK ; 
 int IXGBE_EIMS_FLOW_DIR ; 
 int IXGBE_EIMS_GPI_SDP0 ; 
 int IXGBE_EIMS_GPI_SDP0_BY_MAC (struct ixgbe_hw*) ; 
 int IXGBE_EIMS_GPI_SDP1 ; 
 int IXGBE_EIMS_GPI_SDP2 ; 
 int IXGBE_EIMS_LSC ; 
 int IXGBE_EIMS_MAILBOX ; 
 int IXGBE_EIMS_OTHER ; 
 int IXGBE_EIMS_RTX_QUEUE ; 
 int IXGBE_EIMS_TS ; 
 int IXGBE_FEATURE_FAN_FAIL ; 
 int IXGBE_FEATURE_FDIR ; 
 int IXGBE_FEATURE_SRIOV ; 
 int /*<<< orphan*/  IXGBE_FWSM ; 
 int IXGBE_FWSM_TS_ENABLED ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_enable_queue (struct adapter*,int /*<<< orphan*/ ) ; 
#define  ixgbe_mac_82599EB 132 
#define  ixgbe_mac_X540 131 
#define  ixgbe_mac_X550 130 
#define  ixgbe_mac_X550EM_a 129 
#define  ixgbe_mac_X550EM_x 128 
 int /*<<< orphan*/  ixgbe_phy_x550em_ext_t ; 

void
ixgbe_if_enable_intr(if_ctx_t ctx)
{
	struct adapter     *adapter = iflib_get_softc(ctx);
	struct ixgbe_hw    *hw = &adapter->hw;
	struct ix_rx_queue *que = adapter->rx_queues;
	u32                mask, fwsm;

	mask = (IXGBE_EIMS_ENABLE_MASK & ~IXGBE_EIMS_RTX_QUEUE);

	switch (adapter->hw.mac.type) {
	case ixgbe_mac_82599EB:
		mask |= IXGBE_EIMS_ECC;
		/* Temperature sensor on some adapters */
		mask |= IXGBE_EIMS_GPI_SDP0;
		/* SFP+ (RX_LOS_N & MOD_ABS_N) */
		mask |= IXGBE_EIMS_GPI_SDP1;
		mask |= IXGBE_EIMS_GPI_SDP2;
		break;
	case ixgbe_mac_X540:
		/* Detect if Thermal Sensor is enabled */
		fwsm = IXGBE_READ_REG(hw, IXGBE_FWSM);
		if (fwsm & IXGBE_FWSM_TS_ENABLED)
			mask |= IXGBE_EIMS_TS;
		mask |= IXGBE_EIMS_ECC;
		break;
	case ixgbe_mac_X550:
		/* MAC thermal sensor is automatically enabled */
		mask |= IXGBE_EIMS_TS;
		mask |= IXGBE_EIMS_ECC;
		break;
	case ixgbe_mac_X550EM_x:
	case ixgbe_mac_X550EM_a:
		/* Some devices use SDP0 for important information */
		if (hw->device_id == IXGBE_DEV_ID_X550EM_X_SFP ||
		    hw->device_id == IXGBE_DEV_ID_X550EM_A_SFP ||
		    hw->device_id == IXGBE_DEV_ID_X550EM_A_SFP_N ||
		    hw->device_id == IXGBE_DEV_ID_X550EM_X_10G_T)
			mask |= IXGBE_EIMS_GPI_SDP0_BY_MAC(hw);
		if (hw->phy.type == ixgbe_phy_x550em_ext_t)
			mask |= IXGBE_EICR_GPI_SDP0_X540;
		mask |= IXGBE_EIMS_ECC;
		break;
	default:
		break;
	}

	/* Enable Fan Failure detection */
	if (adapter->feat_en & IXGBE_FEATURE_FAN_FAIL)
		mask |= IXGBE_EIMS_GPI_SDP1;
	/* Enable SR-IOV */
	if (adapter->feat_en & IXGBE_FEATURE_SRIOV)
		mask |= IXGBE_EIMS_MAILBOX;
	/* Enable Flow Director */
	if (adapter->feat_en & IXGBE_FEATURE_FDIR)
		mask |= IXGBE_EIMS_FLOW_DIR;

	IXGBE_WRITE_REG(hw, IXGBE_EIMS, mask);

	/* With MSI-X we use auto clear */
	if (adapter->intr_type == IFLIB_INTR_MSIX) {
		mask = IXGBE_EIMS_ENABLE_MASK;
		/* Don't autoclear Link */
		mask &= ~IXGBE_EIMS_OTHER;
		mask &= ~IXGBE_EIMS_LSC;
		if (adapter->feat_cap & IXGBE_FEATURE_SRIOV)
			mask &= ~IXGBE_EIMS_MAILBOX;
		IXGBE_WRITE_REG(hw, IXGBE_EIAC, mask);
	}

	/*
	 * Now enable all queues, this is done separately to
	 * allow for handling the extended (beyond 32) MSI-X
	 * vectors that can be used by 82599
	 */
	for (int i = 0; i < adapter->num_rx_queues; i++, que++)
		ixgbe_enable_queue(adapter, que->msix);

	IXGBE_WRITE_FLUSH(hw);

}