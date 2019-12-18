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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct e1000_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_ERR_MBX ; 
 int /*<<< orphan*/  E1000_P2VMAILBOX (int /*<<< orphan*/ ) ; 
 int E1000_P2VMAILBOX_PFU ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usec_delay (int) ; 

__attribute__((used)) static s32 e1000_obtain_mbx_lock_pf(struct e1000_hw *hw, u16 vf_number)
{
	s32 ret_val = -E1000_ERR_MBX;
	u32 p2v_mailbox;
	int count = 10;

	DEBUGFUNC("e1000_obtain_mbx_lock_pf");

	do {
		/* Take ownership of the buffer */
		E1000_WRITE_REG(hw, E1000_P2VMAILBOX(vf_number),
				E1000_P2VMAILBOX_PFU);

		/* reserve mailbox for pf use */
		p2v_mailbox = E1000_READ_REG(hw, E1000_P2VMAILBOX(vf_number));
		if (p2v_mailbox & E1000_P2VMAILBOX_PFU) {
			ret_val = E1000_SUCCESS;
			break;
		}
		usec_delay(1000);
	} while (count-- > 0);

	return ret_val;

}