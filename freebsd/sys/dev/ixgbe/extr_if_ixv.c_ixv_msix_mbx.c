#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct ixgbe_hw {int dummy; } ;
struct adapter {int /*<<< orphan*/  ctx; int /*<<< orphan*/  link_irq; struct ixgbe_hw hw; } ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 int IXGBE_EICR_LSC ; 
 int IXGBE_EIMS_OTHER ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_VTEICR ; 
 int /*<<< orphan*/  IXGBE_VTEICS ; 
 int /*<<< orphan*/  IXGBE_VTEIMS ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iflib_admin_intr_deferred (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ixv_msix_mbx(void *arg)
{
	struct adapter  *adapter = arg;
	struct ixgbe_hw *hw = &adapter->hw;
	u32             reg;

	++adapter->link_irq;

	/* First get the cause */
	reg = IXGBE_READ_REG(hw, IXGBE_VTEICS);
	/* Clear interrupt with write */
	IXGBE_WRITE_REG(hw, IXGBE_VTEICR, reg);

	/* Link status change */
	if (reg & IXGBE_EICR_LSC)
		iflib_admin_intr_deferred(adapter->ctx);

	IXGBE_WRITE_REG(hw, IXGBE_VTEIMS, IXGBE_EIMS_OTHER);

	return (FILTER_HANDLED);
}