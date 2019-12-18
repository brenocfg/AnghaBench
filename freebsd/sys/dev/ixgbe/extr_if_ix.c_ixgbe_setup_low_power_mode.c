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
struct TYPE_3__ {int (* enter_lplu ) (struct ixgbe_hw*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  reset_disable; TYPE_1__ ops; } ;
struct ixgbe_hw {scalar_t__ device_id; TYPE_2__ phy; int /*<<< orphan*/  wol_enabled; } ;
struct adapter {int wufc; struct ixgbe_hw hw; } ;
typedef  int s32 ;
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IXGBE_DEV_ID_X550EM_X_10G_T ; 
 int /*<<< orphan*/  IXGBE_GRC ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IXGBE_WUC ; 
 int IXGBE_WUC_PME_EN ; 
 int IXGBE_WUC_WKEN ; 
 int /*<<< orphan*/  IXGBE_WUFC ; 
 int /*<<< orphan*/  IXGBE_WUS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  iflib_get_dev (int /*<<< orphan*/ ) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_if_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_set_phy_power (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int stub1 (struct ixgbe_hw*) ; 

__attribute__((used)) static int
ixgbe_setup_low_power_mode(if_ctx_t ctx)
{
	struct adapter  *adapter = iflib_get_softc(ctx);
	struct ixgbe_hw *hw = &adapter->hw;
	device_t        dev = iflib_get_dev(ctx);
	s32             error = 0;

	if (!hw->wol_enabled)
		ixgbe_set_phy_power(hw, FALSE);

	/* Limit power management flow to X550EM baseT */
	if (hw->device_id == IXGBE_DEV_ID_X550EM_X_10G_T &&
	    hw->phy.ops.enter_lplu) {
		/* Turn off support for APM wakeup. (Using ACPI instead) */
		IXGBE_WRITE_REG(hw, IXGBE_GRC,
		    IXGBE_READ_REG(hw, IXGBE_GRC) & ~(u32)2);

		/*
		 * Clear Wake Up Status register to prevent any previous wakeup
		 * events from waking us up immediately after we suspend.
		 */
		IXGBE_WRITE_REG(hw, IXGBE_WUS, 0xffffffff);

		/*
		 * Program the Wakeup Filter Control register with user filter
		 * settings
		 */
		IXGBE_WRITE_REG(hw, IXGBE_WUFC, adapter->wufc);

		/* Enable wakeups and power management in Wakeup Control */
		IXGBE_WRITE_REG(hw, IXGBE_WUC,
		    IXGBE_WUC_WKEN | IXGBE_WUC_PME_EN);

		/* X550EM baseT adapters need a special LPLU flow */
		hw->phy.reset_disable = TRUE;
		ixgbe_if_stop(ctx);
		error = hw->phy.ops.enter_lplu(hw);
		if (error)
			device_printf(dev, "Error entering LPLU: %d\n", error);
		hw->phy.reset_disable = FALSE;
	} else {
		/* Just stop for other adapters */
		ixgbe_if_stop(ctx);
	}

	return error;
}