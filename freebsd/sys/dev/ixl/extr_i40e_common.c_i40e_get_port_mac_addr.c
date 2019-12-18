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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct i40e_hw {int dummy; } ;
struct i40e_aqc_mac_address_read_data {int /*<<< orphan*/  port_mac; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 int I40E_AQC_PORT_ADDR_VALID ; 
 int I40E_ERR_INVALID_MAC_ADDR ; 
 int /*<<< orphan*/  I40E_NONDMA_TO_NONDMA ; 
 int i40e_aq_mac_address_read (struct i40e_hw*,int*,struct i40e_aqc_mac_address_read_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

enum i40e_status_code i40e_get_port_mac_addr(struct i40e_hw *hw, u8 *mac_addr)
{
	struct i40e_aqc_mac_address_read_data addrs;
	enum i40e_status_code status;
	u16 flags = 0;

	status = i40e_aq_mac_address_read(hw, &flags, &addrs, NULL);
	if (status)
		return status;

	if (flags & I40E_AQC_PORT_ADDR_VALID)
		i40e_memcpy(mac_addr, &addrs.port_mac, sizeof(addrs.port_mac),
			I40E_NONDMA_TO_NONDMA);
	else
		status = I40E_ERR_INVALID_MAC_ADDR;

	return status;
}