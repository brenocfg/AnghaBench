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
struct e1000_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int E1000_COLLISION_DISTANCE ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_TCTL_EXT ; 
 int E1000_TCTL_EXT_COLD ; 
 int E1000_TCTL_EXT_COLD_SHIFT ; 
 int /*<<< orphan*/  E1000_WRITE_FLUSH (struct e1000_hw*) ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void e1000_config_collision_dist_82575(struct e1000_hw *hw)
{
	u32 tctl_ext;

	DEBUGFUNC("e1000_config_collision_dist_82575");

	tctl_ext = E1000_READ_REG(hw, E1000_TCTL_EXT);

	tctl_ext &= ~E1000_TCTL_EXT_COLD;
	tctl_ext |= E1000_COLLISION_DISTANCE << E1000_TCTL_EXT_COLD_SHIFT;

	E1000_WRITE_REG(hw, E1000_TCTL_EXT, tctl_ext);
	E1000_WRITE_FLUSH(hw);
}