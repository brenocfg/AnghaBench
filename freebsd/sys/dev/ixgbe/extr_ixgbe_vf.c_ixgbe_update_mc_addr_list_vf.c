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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {int /*<<< orphan*/  (* write_posted ) (struct ixgbe_hw*,int*,int,int /*<<< orphan*/ ) ;} ;
struct ixgbe_mbx_info {TYPE_1__ ops; } ;
struct ixgbe_hw {struct ixgbe_mbx_info mbx; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  (* ixgbe_mc_addr_itr ) (struct ixgbe_hw*,int /*<<< orphan*/ **,int*) ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT1 (char*,int) ; 
 int IXGBE_VFMAILBOX_SIZE ; 
 int IXGBE_VF_SET_MULTICAST ; 
 int IXGBE_VT_MSGINFO_SHIFT ; 
 int /*<<< orphan*/  UNREFERENCED_1PARAMETER (int) ; 
 int ixgbe_mta_vector (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,int*,int,int /*<<< orphan*/ ) ; 

s32 ixgbe_update_mc_addr_list_vf(struct ixgbe_hw *hw, u8 *mc_addr_list,
				 u32 mc_addr_count, ixgbe_mc_addr_itr next,
				 bool clear)
{
	struct ixgbe_mbx_info *mbx = &hw->mbx;
	u32 msgbuf[IXGBE_VFMAILBOX_SIZE];
	u16 *vector_list = (u16 *)&msgbuf[1];
	u32 vector;
	u32 cnt, i;
	u32 vmdq;

	UNREFERENCED_1PARAMETER(clear);

	DEBUGFUNC("ixgbe_update_mc_addr_list_vf");

	/* Each entry in the list uses 1 16 bit word.  We have 30
	 * 16 bit words available in our HW msg buffer (minus 1 for the
	 * msg type).  That's 30 hash values if we pack 'em right.  If
	 * there are more than 30 MC addresses to add then punt the
	 * extras for now and then add code to handle more than 30 later.
	 * It would be unusual for a server to request that many multi-cast
	 * addresses except for in large enterprise network environments.
	 */

	DEBUGOUT1("MC Addr Count = %d\n", mc_addr_count);

	cnt = (mc_addr_count > 30) ? 30 : mc_addr_count;
	msgbuf[0] = IXGBE_VF_SET_MULTICAST;
	msgbuf[0] |= cnt << IXGBE_VT_MSGINFO_SHIFT;

	for (i = 0; i < cnt; i++) {
		vector = ixgbe_mta_vector(hw, next(hw, &mc_addr_list, &vmdq));
		DEBUGOUT1("Hash value = 0x%03X\n", vector);
		vector_list[i] = (u16)vector;
	}

	return mbx->ops.write_posted(hw, msgbuf, IXGBE_VFMAILBOX_SIZE, 0);
}