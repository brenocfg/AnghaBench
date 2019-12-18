#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_9__ {int /*<<< orphan*/  (* write ) (struct ixgbe_hw*,int,int) ;} ;
struct TYPE_10__ {TYPE_4__ ops; } ;
struct TYPE_8__ {scalar_t__ func; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* set_lan_id ) (struct ixgbe_hw*) ;} ;
struct TYPE_7__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_5__ eeprom; TYPE_3__ bus; TYPE_2__ mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 scalar_t__ IXGBE_ERR_NO_SAN_ADDR_PTR ; 
 scalar_t__ IXGBE_SAN_MAC_ADDR_PORT0_OFFSET ; 
 scalar_t__ IXGBE_SAN_MAC_ADDR_PORT1_OFFSET ; 
 scalar_t__ IXGBE_SUCCESS ; 
 scalar_t__ ixgbe_get_san_mac_addr_offset (struct ixgbe_hw*,int*) ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,int,int) ; 

s32 ixgbe_set_san_mac_addr_generic(struct ixgbe_hw *hw, u8 *san_mac_addr)
{
	s32 ret_val;
	u16 san_mac_data, san_mac_offset;
	u8 i;

	DEBUGFUNC("ixgbe_set_san_mac_addr_generic");

	/* Look for SAN mac address pointer.  If not defined, return */
	ret_val = ixgbe_get_san_mac_addr_offset(hw, &san_mac_offset);
	if (ret_val || san_mac_offset == 0 || san_mac_offset == 0xFFFF)
		return IXGBE_ERR_NO_SAN_ADDR_PTR;

	/* Make sure we know which port we need to write */
	hw->mac.ops.set_lan_id(hw);
	/* Apply the port offset to the address offset */
	(hw->bus.func) ? (san_mac_offset += IXGBE_SAN_MAC_ADDR_PORT1_OFFSET) :
			 (san_mac_offset += IXGBE_SAN_MAC_ADDR_PORT0_OFFSET);

	for (i = 0; i < 3; i++) {
		san_mac_data = (u16)((u16)(san_mac_addr[i * 2 + 1]) << 8);
		san_mac_data |= (u16)(san_mac_addr[i * 2]);
		hw->eeprom.ops.write(hw, san_mac_offset, san_mac_data);
		san_mac_offset++;
	}

	return IXGBE_SUCCESS;
}