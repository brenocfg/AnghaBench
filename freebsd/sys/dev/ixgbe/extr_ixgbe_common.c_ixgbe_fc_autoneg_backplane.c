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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ type; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  IXGBE_ANLP1 ; 
 int /*<<< orphan*/  IXGBE_ANLP1_ASM_PAUSE ; 
 int /*<<< orphan*/  IXGBE_ANLP1_SYM_PAUSE ; 
 int /*<<< orphan*/  IXGBE_AUTOC ; 
 int /*<<< orphan*/  IXGBE_AUTOC_ASM_PAUSE ; 
 int /*<<< orphan*/  IXGBE_AUTOC_SYM_PAUSE ; 
 int /*<<< orphan*/  IXGBE_ERR_FC_NOT_NEGOTIATED ; 
 int /*<<< orphan*/  IXGBE_LINKS ; 
 int /*<<< orphan*/  IXGBE_LINKS2 ; 
 int IXGBE_LINKS2_AN_SUPPORTED ; 
 int IXGBE_LINKS_KX_AN_COMP ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ ixgbe_mac_82599EB ; 
 int /*<<< orphan*/  ixgbe_negotiate_fc (struct ixgbe_hw*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 ixgbe_fc_autoneg_backplane(struct ixgbe_hw *hw)
{
	u32 links2, anlp1_reg, autoc_reg, links;
	s32 ret_val = IXGBE_ERR_FC_NOT_NEGOTIATED;

	/*
	 * On backplane, bail out if
	 * - backplane autoneg was not completed, or if
	 * - we are 82599 and link partner is not AN enabled
	 */
	links = IXGBE_READ_REG(hw, IXGBE_LINKS);
	if ((links & IXGBE_LINKS_KX_AN_COMP) == 0) {
		DEBUGOUT("Auto-Negotiation did not complete\n");
		goto out;
	}

	if (hw->mac.type == ixgbe_mac_82599EB) {
		links2 = IXGBE_READ_REG(hw, IXGBE_LINKS2);
		if ((links2 & IXGBE_LINKS2_AN_SUPPORTED) == 0) {
			DEBUGOUT("Link partner is not AN enabled\n");
			goto out;
		}
	}
	/*
	 * Read the 10g AN autoc and LP ability registers and resolve
	 * local flow control settings accordingly
	 */
	autoc_reg = IXGBE_READ_REG(hw, IXGBE_AUTOC);
	anlp1_reg = IXGBE_READ_REG(hw, IXGBE_ANLP1);

	ret_val = ixgbe_negotiate_fc(hw, autoc_reg,
		anlp1_reg, IXGBE_AUTOC_SYM_PAUSE, IXGBE_AUTOC_ASM_PAUSE,
		IXGBE_ANLP1_SYM_PAUSE, IXGBE_ANLP1_ASM_PAUSE);

out:
	return ret_val;
}