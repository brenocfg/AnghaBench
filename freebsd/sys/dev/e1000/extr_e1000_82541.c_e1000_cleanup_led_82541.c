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
struct TYPE_8__ {int /*<<< orphan*/  ledctl_default; } ;
struct TYPE_6__ {scalar_t__ (* write_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {TYPE_2__ ops; } ;
struct e1000_dev_spec_82541 {int /*<<< orphan*/  spd_default; } ;
struct TYPE_5__ {struct e1000_dev_spec_82541 _82541; } ;
struct e1000_hw {TYPE_4__ mac; TYPE_3__ phy; TYPE_1__ dev_spec; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_LEDCTL ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IGP01E1000_GMII_FIFO ; 
 scalar_t__ stub1 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 e1000_cleanup_led_82541(struct e1000_hw *hw)
{
	struct e1000_dev_spec_82541 *dev_spec = &hw->dev_spec._82541;
	s32 ret_val;

	DEBUGFUNC("e1000_cleanup_led_82541");

	ret_val = hw->phy.ops.write_reg(hw, IGP01E1000_GMII_FIFO,
					dev_spec->spd_default);
	if (ret_val)
		goto out;

	E1000_WRITE_REG(hw, E1000_LEDCTL, hw->mac.ledctl_default);

out:
	return ret_val;
}