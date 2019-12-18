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
struct TYPE_2__ {int /*<<< orphan*/  (* read_posted ) (struct e1000_hw*,int*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* write_posted ) (struct e1000_hw*,int*,int,int /*<<< orphan*/ ) ;} ;
struct e1000_mbx_info {TYPE_1__ ops; } ;
struct e1000_hw {struct e1000_mbx_info mbx; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  enum e1000_promisc_type { ____Placeholder_e1000_promisc_type } e1000_promisc_type ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_ERR_MAC_INIT ; 
 int E1000_VF_SET_PROMISC ; 
 int E1000_VF_SET_PROMISC_MULTICAST ; 
 int E1000_VF_SET_PROMISC_UNICAST ; 
 int E1000_VT_MSGTYPE_ACK ; 
#define  e1000_promisc_disabled 131 
#define  e1000_promisc_enabled 130 
#define  e1000_promisc_multicast 129 
#define  e1000_promisc_unicast 128 
 int /*<<< orphan*/  stub1 (struct e1000_hw*,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*,int*,int,int /*<<< orphan*/ ) ; 

s32 e1000_promisc_set_vf(struct e1000_hw *hw, enum e1000_promisc_type type)
{
	struct e1000_mbx_info *mbx = &hw->mbx;
	u32 msgbuf = E1000_VF_SET_PROMISC;
	s32 ret_val;

	switch (type) {
	case e1000_promisc_multicast:
		msgbuf |= E1000_VF_SET_PROMISC_MULTICAST;
		break;
	case e1000_promisc_enabled:
		msgbuf |= E1000_VF_SET_PROMISC_MULTICAST;
		/* FALLTHROUGH */
	case e1000_promisc_unicast:
		msgbuf |= E1000_VF_SET_PROMISC_UNICAST;
		/* FALLTHROUGH */
	case e1000_promisc_disabled:
		break;
	default:
		return -E1000_ERR_MAC_INIT;
	}

	 ret_val = mbx->ops.write_posted(hw, &msgbuf, 1, 0);

	if (!ret_val)
		ret_val = mbx->ops.read_posted(hw, &msgbuf, 1, 0);

	if (!ret_val && !(msgbuf & E1000_VT_MSGTYPE_ACK))
		ret_val = -E1000_ERR_MAC_INIT;

	return ret_val;
}