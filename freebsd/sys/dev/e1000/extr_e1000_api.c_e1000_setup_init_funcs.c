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
struct TYPE_2__ {int type; } ;
struct e1000_hw {TYPE_1__ mac; int /*<<< orphan*/  hw_addr; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int E1000_ERR_CONFIG ; 
#define  e1000_80003es2lan 162 
#define  e1000_82540 161 
#define  e1000_82541 160 
#define  e1000_82541_rev_2 159 
#define  e1000_82542 158 
#define  e1000_82543 157 
#define  e1000_82544 156 
#define  e1000_82545 155 
#define  e1000_82545_rev_3 154 
#define  e1000_82546 153 
#define  e1000_82546_rev_3 152 
#define  e1000_82547 151 
#define  e1000_82547_rev_2 150 
#define  e1000_82571 149 
#define  e1000_82572 148 
#define  e1000_82573 147 
#define  e1000_82574 146 
#define  e1000_82575 145 
#define  e1000_82576 144 
#define  e1000_82580 143 
#define  e1000_82583 142 
#define  e1000_i210 141 
#define  e1000_i211 140 
#define  e1000_i350 139 
#define  e1000_i354 138 
#define  e1000_ich10lan 137 
#define  e1000_ich8lan 136 
#define  e1000_ich9lan 135 
 int /*<<< orphan*/  e1000_init_function_pointers_80003es2lan (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_init_function_pointers_82540 (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_init_function_pointers_82541 (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_init_function_pointers_82542 (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_init_function_pointers_82543 (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_init_function_pointers_82571 (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_init_function_pointers_82575 (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_init_function_pointers_i210 (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_init_function_pointers_ich8lan (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_init_function_pointers_vf (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_init_mac_ops_generic (struct e1000_hw*) ; 
 int e1000_init_mac_params (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_init_mbx_ops_generic (struct e1000_hw*) ; 
 int e1000_init_mbx_params (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_init_nvm_ops_generic (struct e1000_hw*) ; 
 int e1000_init_nvm_params (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_init_phy_ops_generic (struct e1000_hw*) ; 
 int e1000_init_phy_params (struct e1000_hw*) ; 
#define  e1000_pch2lan 134 
#define  e1000_pch_cnp 133 
#define  e1000_pch_lpt 132 
#define  e1000_pch_spt 131 
#define  e1000_pchlan 130 
 int e1000_set_mac_type (struct e1000_hw*) ; 
#define  e1000_vfadapt 129 
#define  e1000_vfadapt_i350 128 

s32 e1000_setup_init_funcs(struct e1000_hw *hw, bool init_device)
{
	s32 ret_val;

	/* Can't do much good without knowing the MAC type. */
	ret_val = e1000_set_mac_type(hw);
	if (ret_val) {
		DEBUGOUT("ERROR: MAC type could not be set properly.\n");
		goto out;
	}

	if (!hw->hw_addr) {
		DEBUGOUT("ERROR: Registers not mapped\n");
		ret_val = -E1000_ERR_CONFIG;
		goto out;
	}

	/*
	 * Init function pointers to generic implementations. We do this first
	 * allowing a driver module to override it afterward.
	 */
	e1000_init_mac_ops_generic(hw);
	e1000_init_phy_ops_generic(hw);
	e1000_init_nvm_ops_generic(hw);
	e1000_init_mbx_ops_generic(hw);

	/*
	 * Set up the init function pointers. These are functions within the
	 * adapter family file that sets up function pointers for the rest of
	 * the functions in that family.
	 */
	switch (hw->mac.type) {
	case e1000_82542:
		e1000_init_function_pointers_82542(hw);
		break;
	case e1000_82543:
	case e1000_82544:
		e1000_init_function_pointers_82543(hw);
		break;
	case e1000_82540:
	case e1000_82545:
	case e1000_82545_rev_3:
	case e1000_82546:
	case e1000_82546_rev_3:
		e1000_init_function_pointers_82540(hw);
		break;
	case e1000_82541:
	case e1000_82541_rev_2:
	case e1000_82547:
	case e1000_82547_rev_2:
		e1000_init_function_pointers_82541(hw);
		break;
	case e1000_82571:
	case e1000_82572:
	case e1000_82573:
	case e1000_82574:
	case e1000_82583:
		e1000_init_function_pointers_82571(hw);
		break;
	case e1000_80003es2lan:
		e1000_init_function_pointers_80003es2lan(hw);
		break;
	case e1000_ich8lan:
	case e1000_ich9lan:
	case e1000_ich10lan:
	case e1000_pchlan:
	case e1000_pch2lan:
	case e1000_pch_lpt:
	case e1000_pch_spt:
	case e1000_pch_cnp:
		e1000_init_function_pointers_ich8lan(hw);
		break;
	case e1000_82575:
	case e1000_82576:
	case e1000_82580:
	case e1000_i350:
	case e1000_i354:
		e1000_init_function_pointers_82575(hw);
		break;
	case e1000_i210:
	case e1000_i211:
		e1000_init_function_pointers_i210(hw);
		break;
	case e1000_vfadapt:
		e1000_init_function_pointers_vf(hw);
		break;
	case e1000_vfadapt_i350:
		e1000_init_function_pointers_vf(hw);
		break;
	default:
		DEBUGOUT("Hardware not supported\n");
		ret_val = -E1000_ERR_CONFIG;
		break;
	}

	/*
	 * Initialize the rest of the function pointers. These require some
	 * register reads/writes in some cases.
	 */
	if (!(ret_val) && init_device) {
		ret_val = e1000_init_mac_params(hw);
		if (ret_val)
			goto out;

		ret_val = e1000_init_nvm_params(hw);
		if (ret_val)
			goto out;

		ret_val = e1000_init_phy_params(hw);
		if (ret_val)
			goto out;

		ret_val = e1000_init_mbx_params(hw);
		if (ret_val)
			goto out;
	}

out:
	return ret_val;
}