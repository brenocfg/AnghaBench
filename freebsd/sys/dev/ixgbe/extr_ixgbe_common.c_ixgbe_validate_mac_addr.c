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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  IXGBE_ERR_INVALID_MAC_ADDR ; 
 scalar_t__ IXGBE_IS_BROADCAST (scalar_t__*) ; 
 scalar_t__ IXGBE_IS_MULTICAST (scalar_t__*) ; 
 int /*<<< orphan*/  IXGBE_SUCCESS ; 

s32 ixgbe_validate_mac_addr(u8 *mac_addr)
{
	s32 status = IXGBE_SUCCESS;

	DEBUGFUNC("ixgbe_validate_mac_addr");

	/* Make sure it is not a multicast address */
	if (IXGBE_IS_MULTICAST(mac_addr)) {
		status = IXGBE_ERR_INVALID_MAC_ADDR;
	/* Not a broadcast address */
	} else if (IXGBE_IS_BROADCAST(mac_addr)) {
		status = IXGBE_ERR_INVALID_MAC_ADDR;
	/* Reject the zero address */
	} else if (mac_addr[0] == 0 && mac_addr[1] == 0 && mac_addr[2] == 0 &&
		   mac_addr[3] == 0 && mac_addr[4] == 0 && mac_addr[5] == 0) {
		status = IXGBE_ERR_INVALID_MAC_ADDR;
	}
	return status;
}