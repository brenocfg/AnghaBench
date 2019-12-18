#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  init_params; } ;
struct TYPE_12__ {TYPE_5__ ops; } ;
struct TYPE_7__ {int /*<<< orphan*/  init_params; } ;
struct TYPE_10__ {int type; TYPE_1__ ops; } ;
struct TYPE_8__ {int /*<<< orphan*/  init_params; } ;
struct TYPE_9__ {TYPE_2__ ops; } ;
struct e1000_hw {TYPE_6__ phy; TYPE_4__ mac; TYPE_3__ nvm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
#define  e1000_ich10lan 135 
#define  e1000_ich8lan 134 
#define  e1000_ich9lan 133 
 int /*<<< orphan*/  e1000_init_mac_params_ich8lan ; 
 int /*<<< orphan*/  e1000_init_nvm_params_ich8lan ; 
 int /*<<< orphan*/  e1000_init_phy_params_ich8lan ; 
 int /*<<< orphan*/  e1000_init_phy_params_pchlan ; 
#define  e1000_pch2lan 132 
#define  e1000_pch_cnp 131 
#define  e1000_pch_lpt 130 
#define  e1000_pch_spt 129 
#define  e1000_pchlan 128 

void e1000_init_function_pointers_ich8lan(struct e1000_hw *hw)
{
	DEBUGFUNC("e1000_init_function_pointers_ich8lan");

	hw->mac.ops.init_params = e1000_init_mac_params_ich8lan;
	hw->nvm.ops.init_params = e1000_init_nvm_params_ich8lan;
	switch (hw->mac.type) {
	case e1000_ich8lan:
	case e1000_ich9lan:
	case e1000_ich10lan:
		hw->phy.ops.init_params = e1000_init_phy_params_ich8lan;
		break;
	case e1000_pchlan:
	case e1000_pch2lan:
	case e1000_pch_lpt:
	case e1000_pch_spt:
	case e1000_pch_cnp:
		hw->phy.ops.init_params = e1000_init_phy_params_pchlan;
		break;
	default:
		break;
	}
}