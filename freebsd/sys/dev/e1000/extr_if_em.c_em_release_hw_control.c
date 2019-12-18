#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {scalar_t__ type; } ;
struct TYPE_5__ {TYPE_1__ mac; } ;
struct adapter {TYPE_2__ hw; int /*<<< orphan*/  has_manage; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_CTRL_EXT ; 
 int E1000_CTRL_EXT_DRV_LOAD ; 
 int E1000_READ_REG (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_SWSM ; 
 int E1000_SWSM_DRV_LOAD ; 
 int /*<<< orphan*/  E1000_WRITE_REG (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ e1000_82573 ; 

__attribute__((used)) static void
em_release_hw_control(struct adapter *adapter)
{
	u32 ctrl_ext, swsm;

	if (!adapter->has_manage)
		return;

	if (adapter->hw.mac.type == e1000_82573) {
		swsm = E1000_READ_REG(&adapter->hw, E1000_SWSM);
		E1000_WRITE_REG(&adapter->hw, E1000_SWSM,
		    swsm & ~E1000_SWSM_DRV_LOAD);
		return;
	}
	/* else */
	ctrl_ext = E1000_READ_REG(&adapter->hw, E1000_CTRL_EXT);
	E1000_WRITE_REG(&adapter->hw, E1000_CTRL_EXT,
	    ctrl_ext & ~E1000_CTRL_EXT_DRV_LOAD);
	return;
}