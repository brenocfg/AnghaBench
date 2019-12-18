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
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  (* check_overtemp ) (struct ixgbe_hw*) ;} ;
struct TYPE_6__ {scalar_t__ type; TYPE_1__ ops; } ;
struct TYPE_5__ {int type; } ;
struct ixgbe_hw {TYPE_3__ phy; TYPE_2__ mac; } ;
struct adapter {int feat_en; int /*<<< orphan*/  task_requests; int /*<<< orphan*/  ctx; struct ixgbe_hw hw; int /*<<< orphan*/  fdir_reinit; int /*<<< orphan*/  link_irq; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 int FILTER_SCHEDULE_THREAD ; 
 int /*<<< orphan*/  IXGBE_EICR ; 
 int IXGBE_EICR_ECC ; 
 int IXGBE_EICR_FLOW_DIR ; 
 int IXGBE_EICR_GPI_SDP0_X540 ; 
 int IXGBE_EICR_GPI_SDP0_X550EM_a ; 
 int IXGBE_EICR_GPI_SDP1_BY_MAC (struct ixgbe_hw*) ; 
 int IXGBE_EICR_GPI_SDP2_BY_MAC (struct ixgbe_hw*) ; 
 int IXGBE_EICR_LSC ; 
 int IXGBE_EICR_MAILBOX ; 
 int IXGBE_EICR_RTX_QUEUE ; 
 int IXGBE_EICR_TS ; 
 int /*<<< orphan*/  IXGBE_EICS ; 
 int /*<<< orphan*/  IXGBE_EIMC ; 
 int IXGBE_EIMC_LSC ; 
 int IXGBE_EIMC_OTHER ; 
 int /*<<< orphan*/  IXGBE_ERR_OVERTEMP ; 
 int IXGBE_FEATURE_FAN_FAIL ; 
 int IXGBE_FEATURE_FDIR ; 
 int IXGBE_FEATURE_SRIOV ; 
 int IXGBE_FEATURE_TEMP_SENSOR ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_REQUEST_TASK_FDIR ; 
 int /*<<< orphan*/  IXGBE_REQUEST_TASK_LSC ; 
 int /*<<< orphan*/  IXGBE_REQUEST_TASK_MBX ; 
 int /*<<< orphan*/  IXGBE_REQUEST_TASK_MOD ; 
 int /*<<< orphan*/  IXGBE_REQUEST_TASK_MSF ; 
 int /*<<< orphan*/  IXGBE_REQUEST_TASK_PHY ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  atomic_cmpset_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iflib_get_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_check_fan_failure (struct adapter*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ixgbe_is_sfp (struct ixgbe_hw*) ; 
 int ixgbe_mac_82598EB ; 
 scalar_t__ ixgbe_mac_82599EB ; 
 scalar_t__ ixgbe_mac_X540 ; 
#define  ixgbe_mac_X550EM_a 128 
 scalar_t__ ixgbe_phy_x550em_ext_t ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*) ; 

__attribute__((used)) static int
ixgbe_msix_link(void *arg)
{
	struct adapter  *adapter = arg;
	struct ixgbe_hw *hw = &adapter->hw;
	u32             eicr, eicr_mask;
	s32             retval;

	++adapter->link_irq;

	/* Pause other interrupts */
	IXGBE_WRITE_REG(hw, IXGBE_EIMC, IXGBE_EIMC_OTHER);

	/* First get the cause */
	eicr = IXGBE_READ_REG(hw, IXGBE_EICS);
	/* Be sure the queue bits are not cleared */
	eicr &= ~IXGBE_EICR_RTX_QUEUE;
	/* Clear interrupt with write */
	IXGBE_WRITE_REG(hw, IXGBE_EICR, eicr);

	/* Link status change */
	if (eicr & IXGBE_EICR_LSC) {
		IXGBE_WRITE_REG(hw, IXGBE_EIMC, IXGBE_EIMC_LSC);
		adapter->task_requests |= IXGBE_REQUEST_TASK_LSC;
	}

	if (adapter->hw.mac.type != ixgbe_mac_82598EB) {
		if ((adapter->feat_en & IXGBE_FEATURE_FDIR) &&
		    (eicr & IXGBE_EICR_FLOW_DIR)) {
			/* This is probably overkill :) */
			if (!atomic_cmpset_int(&adapter->fdir_reinit, 0, 1))
				return (FILTER_HANDLED);
			/* Disable the interrupt */
			IXGBE_WRITE_REG(hw, IXGBE_EIMC, IXGBE_EICR_FLOW_DIR);
			adapter->task_requests |= IXGBE_REQUEST_TASK_FDIR;
		} else
			if (eicr & IXGBE_EICR_ECC) {
				device_printf(iflib_get_dev(adapter->ctx),
				   "\nCRITICAL: ECC ERROR!! Please Reboot!!\n");
				IXGBE_WRITE_REG(hw, IXGBE_EICR, IXGBE_EICR_ECC);
			}

		/* Check for over temp condition */
		if (adapter->feat_en & IXGBE_FEATURE_TEMP_SENSOR) {
			switch (adapter->hw.mac.type) {
			case ixgbe_mac_X550EM_a:
				if (!(eicr & IXGBE_EICR_GPI_SDP0_X550EM_a))
					break;
				IXGBE_WRITE_REG(hw, IXGBE_EIMC,
				    IXGBE_EICR_GPI_SDP0_X550EM_a);
				IXGBE_WRITE_REG(hw, IXGBE_EICR,
				    IXGBE_EICR_GPI_SDP0_X550EM_a);
				retval = hw->phy.ops.check_overtemp(hw);
				if (retval != IXGBE_ERR_OVERTEMP)
					break;
				device_printf(iflib_get_dev(adapter->ctx),
				    "\nCRITICAL: OVER TEMP!! PHY IS SHUT DOWN!!\n");
				device_printf(iflib_get_dev(adapter->ctx),
				    "System shutdown required!\n");
				break;
			default:
				if (!(eicr & IXGBE_EICR_TS))
					break;
				retval = hw->phy.ops.check_overtemp(hw);
				if (retval != IXGBE_ERR_OVERTEMP)
					break;
				device_printf(iflib_get_dev(adapter->ctx),
				    "\nCRITICAL: OVER TEMP!! PHY IS SHUT DOWN!!\n");
				device_printf(iflib_get_dev(adapter->ctx),
				    "System shutdown required!\n");
				IXGBE_WRITE_REG(hw, IXGBE_EICR, IXGBE_EICR_TS);
				break;
			}
		}

		/* Check for VF message */
		if ((adapter->feat_en & IXGBE_FEATURE_SRIOV) &&
		    (eicr & IXGBE_EICR_MAILBOX))
			adapter->task_requests |= IXGBE_REQUEST_TASK_MBX;
	}

	if (ixgbe_is_sfp(hw)) {
		/* Pluggable optics-related interrupt */
		if (hw->mac.type >= ixgbe_mac_X540)
			eicr_mask = IXGBE_EICR_GPI_SDP0_X540;
		else
			eicr_mask = IXGBE_EICR_GPI_SDP2_BY_MAC(hw);

		if (eicr & eicr_mask) {
			IXGBE_WRITE_REG(hw, IXGBE_EICR, eicr_mask);
			adapter->task_requests |= IXGBE_REQUEST_TASK_MOD;
		}

		if ((hw->mac.type == ixgbe_mac_82599EB) &&
		    (eicr & IXGBE_EICR_GPI_SDP1_BY_MAC(hw))) {
			IXGBE_WRITE_REG(hw, IXGBE_EICR,
			    IXGBE_EICR_GPI_SDP1_BY_MAC(hw));
			adapter->task_requests |= IXGBE_REQUEST_TASK_MSF;
		}
	}

	/* Check for fan failure */
	if (adapter->feat_en & IXGBE_FEATURE_FAN_FAIL) {
		ixgbe_check_fan_failure(adapter, eicr, TRUE);
		IXGBE_WRITE_REG(hw, IXGBE_EICR, IXGBE_EICR_GPI_SDP1_BY_MAC(hw));
	}

	/* External PHY interrupt */
	if ((hw->phy.type == ixgbe_phy_x550em_ext_t) &&
	    (eicr & IXGBE_EICR_GPI_SDP0_X540)) {
		IXGBE_WRITE_REG(hw, IXGBE_EICR, IXGBE_EICR_GPI_SDP0_X540);
		adapter->task_requests |= IXGBE_REQUEST_TASK_PHY;
	}

	return (adapter->task_requests != 0) ? FILTER_SCHEDULE_THREAD : FILTER_HANDLED;
}