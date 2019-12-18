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
struct TYPE_3__ {int (* get_media_type ) (struct ixgbe_hw*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ mac; int /*<<< orphan*/  need_crosstalk_fix; } ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
#define  ixgbe_media_type_fiber 129 
#define  ixgbe_media_type_fiber_qsfp 128 
 int stub1 (struct ixgbe_hw*) ; 

__attribute__((used)) static bool ixgbe_need_crosstalk_fix(struct ixgbe_hw *hw)
{

	/* Does FW say we need the fix */
	if (!hw->need_crosstalk_fix)
		return FALSE;

	/* Only consider SFP+ PHYs i.e. media type fiber */
	switch (hw->mac.ops.get_media_type(hw)) {
	case ixgbe_media_type_fiber:
	case ixgbe_media_type_fiber_qsfp:
		break;
	default:
		return FALSE;
	}

	return TRUE;
}