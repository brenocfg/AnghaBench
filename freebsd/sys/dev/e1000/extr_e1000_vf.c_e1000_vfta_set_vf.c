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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct e1000_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_VF_SET_VLAN ; 
 int /*<<< orphan*/  E1000_VF_SET_VLAN_ADD ; 
 int /*<<< orphan*/  e1000_write_msg_read_ack (struct e1000_hw*,int /*<<< orphan*/ *,int) ; 

void e1000_vfta_set_vf(struct e1000_hw *hw, u16 vid, bool set)
{
	u32 msgbuf[2];

	msgbuf[0] = E1000_VF_SET_VLAN;
	msgbuf[1] = vid;
	/* Setting the 8 bit field MSG INFO to TRUE indicates "add" */
	if (set)
		msgbuf[0] |= E1000_VF_SET_VLAN_ADD;

	e1000_write_msg_read_ack(hw, msgbuf, 2);
}