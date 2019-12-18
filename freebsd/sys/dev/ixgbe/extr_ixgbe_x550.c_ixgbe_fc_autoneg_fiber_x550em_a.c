#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  requested_mode; int /*<<< orphan*/  current_mode; int /*<<< orphan*/  fc_was_autonegged; } ;
struct ixgbe_hw {TYPE_1__ fc; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 

void ixgbe_fc_autoneg_fiber_x550em_a(struct ixgbe_hw *hw)
{
	hw->fc.fc_was_autonegged = FALSE;
	hw->fc.current_mode = hw->fc.requested_mode;
}