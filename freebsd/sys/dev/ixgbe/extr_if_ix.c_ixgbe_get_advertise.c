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
struct TYPE_5__ {scalar_t__ (* get_link_capabilities ) (struct ixgbe_hw*,int*,int*) ;} ;
struct TYPE_6__ {TYPE_2__ ops; } ;
struct TYPE_4__ {scalar_t__ media_type; int /*<<< orphan*/  multispeed_fiber; } ;
struct ixgbe_hw {TYPE_3__ mac; TYPE_1__ phy; } ;
struct adapter {struct ixgbe_hw hw; } ;
typedef  scalar_t__ s32 ;
typedef  int ixgbe_link_speed ;

/* Variables and functions */
 int FALSE ; 
 int IXGBE_LINK_SPEED_100_FULL ; 
 int IXGBE_LINK_SPEED_10GB_FULL ; 
 int IXGBE_LINK_SPEED_10_FULL ; 
 int IXGBE_LINK_SPEED_1GB_FULL ; 
 scalar_t__ IXGBE_SUCCESS ; 
 scalar_t__ ixgbe_media_type_copper ; 
 scalar_t__ stub1 (struct ixgbe_hw*,int*,int*) ; 

__attribute__((used)) static int
ixgbe_get_advertise(struct adapter *adapter)
{
	struct ixgbe_hw  *hw = &adapter->hw;
	int              speed;
	ixgbe_link_speed link_caps = 0;
	s32              err;
	bool             negotiate = FALSE;

	/*
	 * Advertised speed means nothing unless it's copper or
	 * multi-speed fiber
	 */
	if (!(hw->phy.media_type == ixgbe_media_type_copper) &&
	    !(hw->phy.multispeed_fiber))
		return (0);

	err = hw->mac.ops.get_link_capabilities(hw, &link_caps, &negotiate);
	if (err != IXGBE_SUCCESS)
		return (0);

	speed =
	    ((link_caps & IXGBE_LINK_SPEED_10GB_FULL) ? 4 : 0) |
	    ((link_caps & IXGBE_LINK_SPEED_1GB_FULL)  ? 2 : 0) |
	    ((link_caps & IXGBE_LINK_SPEED_100_FULL)  ? 1 : 0) |
	    ((link_caps & IXGBE_LINK_SPEED_10_FULL)   ? 8 : 0);

	return speed;
}