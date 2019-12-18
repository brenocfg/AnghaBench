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
typedef  void* u8 ;
typedef  int u32 ;
struct TYPE_4__ {int type; } ;
struct TYPE_3__ {int /*<<< orphan*/  get_link_info; } ;
struct i40e_hw {int flags; TYPE_2__ mac; void* pf_id; void* port; TYPE_1__ phy; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int I40E_ERR_DEVICE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  I40E_GLPCI_CAPSUP ; 
 int I40E_GLPCI_CAPSUP_ARI_EN_MASK ; 
 int I40E_GLPCI_CAPSUP_ARI_EN_SHIFT ; 
 int I40E_HW_FLAG_AQ_SRCTL_ACCESS_ENABLE ; 
 int I40E_HW_FLAG_NVM_READ_REQUIRES_LOCK ; 
#define  I40E_MAC_X722 129 
#define  I40E_MAC_XL710 128 
 int /*<<< orphan*/  I40E_PFGEN_PORTNUM ; 
 int I40E_PFGEN_PORTNUM_PORT_NUM_MASK ; 
 int I40E_PFGEN_PORTNUM_PORT_NUM_SHIFT ; 
 int /*<<< orphan*/  I40E_PF_FUNC_RID ; 
 int I40E_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int i40e_init_nvm (struct i40e_hw*) ; 
 int /*<<< orphan*/  i40e_set_mac_type (struct i40e_hw*) ; 
 int rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 

enum i40e_status_code i40e_init_shared_code(struct i40e_hw *hw)
{
	enum i40e_status_code status = I40E_SUCCESS;
	u32 port, ari, func_rid;

	DEBUGFUNC("i40e_init_shared_code");

	i40e_set_mac_type(hw);

	switch (hw->mac.type) {
	case I40E_MAC_XL710:
	case I40E_MAC_X722:
		break;
	default:
		return I40E_ERR_DEVICE_NOT_SUPPORTED;
	}

	hw->phy.get_link_info = TRUE;

	/* Determine port number and PF number*/
	port = (rd32(hw, I40E_PFGEN_PORTNUM) & I40E_PFGEN_PORTNUM_PORT_NUM_MASK)
					   >> I40E_PFGEN_PORTNUM_PORT_NUM_SHIFT;
	hw->port = (u8)port;
	ari = (rd32(hw, I40E_GLPCI_CAPSUP) & I40E_GLPCI_CAPSUP_ARI_EN_MASK) >>
						 I40E_GLPCI_CAPSUP_ARI_EN_SHIFT;
	func_rid = rd32(hw, I40E_PF_FUNC_RID);
	if (ari)
		hw->pf_id = (u8)(func_rid & 0xff);
	else
		hw->pf_id = (u8)(func_rid & 0x7);

	if (hw->mac.type == I40E_MAC_X722)
		hw->flags |= I40E_HW_FLAG_AQ_SRCTL_ACCESS_ENABLE |
			     I40E_HW_FLAG_NVM_READ_REQUIRES_LOCK;

	status = i40e_init_nvm(hw);
	return status;
}