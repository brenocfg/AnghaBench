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
struct e1000_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_ERR_MBX ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_V2PMAILBOX (int /*<<< orphan*/ ) ; 
 int E1000_V2PMAILBOX_VFU ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int e1000_read_v2p_mailbox (struct e1000_hw*) ; 
 int /*<<< orphan*/  usec_delay (int) ; 

__attribute__((used)) static s32 e1000_obtain_mbx_lock_vf(struct e1000_hw *hw)
{
	s32 ret_val = -E1000_ERR_MBX;
	int count = 10;

	DEBUGFUNC("e1000_obtain_mbx_lock_vf");

	do {
		/* Take ownership of the buffer */
		E1000_WRITE_REG(hw, E1000_V2PMAILBOX(0), E1000_V2PMAILBOX_VFU);

		/* reserve mailbox for vf use */
		if (e1000_read_v2p_mailbox(hw) & E1000_V2PMAILBOX_VFU) {
			ret_val = E1000_SUCCESS;
			break;
		}
		usec_delay(1000);
	} while (count-- > 0);

	return ret_val;
}