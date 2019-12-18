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
struct TYPE_5__ {int /*<<< orphan*/ * write_reg; int /*<<< orphan*/ * read_reg; } ;
struct TYPE_6__ {TYPE_2__ ops; int /*<<< orphan*/  type; int /*<<< orphan*/  phy_semaphore_mask; } ;
struct TYPE_4__ {scalar_t__ lan_id; } ;
struct ixgbe_hw {TYPE_3__ phy; TYPE_1__ bus; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_GSSR_PHY0_SM ; 
 int /*<<< orphan*/  IXGBE_GSSR_PHY1_SM ; 
 int /*<<< orphan*/  ixgbe_get_phy_id_fw (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_phy_fw ; 

__attribute__((used)) static s32 ixgbe_identify_phy_fw(struct ixgbe_hw *hw)
{
	if (hw->bus.lan_id)
		hw->phy.phy_semaphore_mask = IXGBE_GSSR_PHY1_SM;
	else
		hw->phy.phy_semaphore_mask = IXGBE_GSSR_PHY0_SM;

	hw->phy.type = ixgbe_phy_fw;
	hw->phy.ops.read_reg = NULL;
	hw->phy.ops.write_reg = NULL;
	return ixgbe_get_phy_id_fw(hw);
}