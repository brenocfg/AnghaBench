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
typedef  int u32 ;
typedef  int u16 ;
struct e1000_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT1 (char*,int) ; 
 int E1000_VFMAILBOX_SIZE ; 
 int E1000_VF_SET_MULTICAST ; 
 int E1000_VF_SET_MULTICAST_OVERFLOW ; 
 int E1000_VT_MSGINFO_SHIFT ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int e1000_hash_mc_addr_vf (struct e1000_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e1000_write_msg_read_ack (struct e1000_hw*,int*,int) ; 

void e1000_update_mc_addr_list_vf(struct e1000_hw *hw,
				  u8 *mc_addr_list, u32 mc_addr_count)
{
	u32 msgbuf[E1000_VFMAILBOX_SIZE];
	u16 *hash_list = (u16 *)&msgbuf[1];
	u32 hash_value;
	u32 i;

	DEBUGFUNC("e1000_update_mc_addr_list_vf");

	/* Each entry in the list uses 1 16 bit word.  We have 30
	 * 16 bit words available in our HW msg buffer (minus 1 for the
	 * msg type).  That's 30 hash values if we pack 'em right.  If
	 * there are more than 30 MC addresses to add then punt the
	 * extras for now and then add code to handle more than 30 later.
	 * It would be unusual for a server to request that many multi-cast
	 * addresses except for in large enterprise network environments.
	 */

	DEBUGOUT1("MC Addr Count = %d\n", mc_addr_count);

	if (mc_addr_count > 30) {
		msgbuf[0] |= E1000_VF_SET_MULTICAST_OVERFLOW;
		mc_addr_count = 30;
	}

	msgbuf[0] = E1000_VF_SET_MULTICAST;
	msgbuf[0] |= mc_addr_count << E1000_VT_MSGINFO_SHIFT;

	for (i = 0; i < mc_addr_count; i++) {
		hash_value = e1000_hash_mc_addr_vf(hw, mc_addr_list);
		DEBUGOUT1("Hash value = 0x%03X\n", hash_value);
		hash_list[i] = hash_value & 0x0FFF;
		mc_addr_list += ETHER_ADDR_LEN;
	}

	e1000_write_msg_read_ack(hw, msgbuf, E1000_VFMAILBOX_SIZE);
}