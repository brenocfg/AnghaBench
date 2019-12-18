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
typedef  void* u8 ;
typedef  int u16 ;
struct TYPE_6__ {void** perm_addr; void** addr; } ;
struct TYPE_4__ {scalar_t__ (* read ) (struct e1000_hw*,int,int,int*) ;} ;
struct TYPE_5__ {TYPE_1__ ops; } ;
struct e1000_hw {TYPE_3__ mac; TYPE_2__ nvm; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 scalar_t__ E1000_SUCCESS ; 
 int ETHER_ADDR_LEN ; 
 scalar_t__ stub1 (struct e1000_hw*,int,int,int*) ; 

s32 e1000_read_mac_addr_82542(struct e1000_hw *hw)
{
	s32  ret_val = E1000_SUCCESS;
	u16 offset, nvm_data, i;

	DEBUGFUNC("e1000_read_mac_addr");

	for (i = 0; i < ETHER_ADDR_LEN; i += 2) {
		offset = i >> 1;
		ret_val = hw->nvm.ops.read(hw, offset, 1, &nvm_data);
		if (ret_val) {
			DEBUGOUT("NVM Read Error\n");
			goto out;
		}
		hw->mac.perm_addr[i] = (u8)(nvm_data & 0xFF);
		hw->mac.perm_addr[i+1] = (u8)(nvm_data >> 8);
	}

	for (i = 0; i < ETHER_ADDR_LEN; i++)
		hw->mac.addr[i] = hw->mac.perm_addr[i];

out:
	return ret_val;
}