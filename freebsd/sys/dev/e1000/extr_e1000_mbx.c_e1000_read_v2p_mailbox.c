#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int v2p_mailbox; } ;
struct TYPE_4__ {TYPE_1__ vf; } ;
struct e1000_hw {TYPE_2__ dev_spec; } ;

/* Variables and functions */
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_V2PMAILBOX (int /*<<< orphan*/ ) ; 
 int E1000_V2PMAILBOX_R2C_BITS ; 

__attribute__((used)) static u32 e1000_read_v2p_mailbox(struct e1000_hw *hw)
{
	u32 v2p_mailbox = E1000_READ_REG(hw, E1000_V2PMAILBOX(0));

	v2p_mailbox |= hw->dev_spec.vf.v2p_mailbox;
	hw->dev_spec.vf.v2p_mailbox |= v2p_mailbox & E1000_V2PMAILBOX_R2C_BITS;

	return v2p_mailbox;
}