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
typedef  scalar_t__ u32 ;
struct TYPE_7__ {scalar_t__ (* setup_sfp ) (struct ixgbe_hw*) ;} ;
struct TYPE_8__ {int type; TYPE_3__ ops; } ;
struct TYPE_5__ {scalar_t__ (* identify_sfp ) (struct ixgbe_hw*) ;scalar_t__ (* reset ) (struct ixgbe_hw*) ;} ;
struct TYPE_6__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_4__ mac; TYPE_2__ phy; scalar_t__ need_crosstalk_fix; } ;
struct adapter {int /*<<< orphan*/  task_requests; struct ixgbe_hw hw; } ;
typedef  void* if_ctx_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ IXGBE_ERR_SFP_NOT_SUPPORTED ; 
 int /*<<< orphan*/  IXGBE_ESDP ; 
 scalar_t__ IXGBE_ESDP_SDP0 ; 
 scalar_t__ IXGBE_ESDP_SDP2 ; 
 scalar_t__ IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_REQUEST_TASK_MSF ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iflib_get_dev (void*) ; 
 struct adapter* iflib_get_softc (void*) ; 
 int ixgbe_mac_82598EB ; 
#define  ixgbe_mac_82599EB 130 
#define  ixgbe_mac_X550EM_a 129 
#define  ixgbe_mac_X550EM_x 128 
 scalar_t__ stub1 (struct ixgbe_hw*) ; 
 scalar_t__ stub2 (struct ixgbe_hw*) ; 
 scalar_t__ stub3 (struct ixgbe_hw*) ; 

__attribute__((used)) static void
ixgbe_handle_mod(void *context)
{
	if_ctx_t        ctx = context;
	struct adapter  *adapter = iflib_get_softc(ctx);
	struct ixgbe_hw *hw = &adapter->hw;
	device_t        dev = iflib_get_dev(ctx);
	u32             err, cage_full = 0;

	if (adapter->hw.need_crosstalk_fix) {
		switch (hw->mac.type) {
		case ixgbe_mac_82599EB:
			cage_full = IXGBE_READ_REG(hw, IXGBE_ESDP) &
			    IXGBE_ESDP_SDP2;
			break;
		case ixgbe_mac_X550EM_x:
		case ixgbe_mac_X550EM_a:
			cage_full = IXGBE_READ_REG(hw, IXGBE_ESDP) &
			    IXGBE_ESDP_SDP0;
			break;
		default:
			break;
		}

		if (!cage_full)
			goto handle_mod_out;
	}

	err = hw->phy.ops.identify_sfp(hw);
	if (err == IXGBE_ERR_SFP_NOT_SUPPORTED) {
		device_printf(dev,
		    "Unsupported SFP+ module type was detected.\n");
		goto handle_mod_out;
	}

	if (hw->mac.type == ixgbe_mac_82598EB)
		err = hw->phy.ops.reset(hw);
	else
		err = hw->mac.ops.setup_sfp(hw);

	if (err == IXGBE_ERR_SFP_NOT_SUPPORTED) {
		device_printf(dev,
		    "Setup failure - unsupported SFP+ module type.\n");
		goto handle_mod_out;
	}
	adapter->task_requests |= IXGBE_REQUEST_TASK_MSF;
	return;

handle_mod_out:
	adapter->task_requests &= ~(IXGBE_REQUEST_TASK_MSF);
}