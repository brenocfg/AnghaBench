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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int type; } ;
struct e1000_hw {TYPE_1__ mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_DTXSWC ; 
 int /*<<< orphan*/  E1000_DTXSWC_VMDQ_LOOPBACK_EN ; 
 int /*<<< orphan*/  E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_TXSWC ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  e1000_82576 130 
#define  e1000_i350 129 
#define  e1000_i354 128 

void e1000_vmdq_set_loopback_pf(struct e1000_hw *hw, bool enable)
{
	u32 dtxswc;

	switch (hw->mac.type) {
	case e1000_82576:
		dtxswc = E1000_READ_REG(hw, E1000_DTXSWC);
		if (enable)
			dtxswc |= E1000_DTXSWC_VMDQ_LOOPBACK_EN;
		else
			dtxswc &= ~E1000_DTXSWC_VMDQ_LOOPBACK_EN;
		E1000_WRITE_REG(hw, E1000_DTXSWC, dtxswc);
		break;
	case e1000_i350:
	case e1000_i354:
		dtxswc = E1000_READ_REG(hw, E1000_TXSWC);
		if (enable)
			dtxswc |= E1000_DTXSWC_VMDQ_LOOPBACK_EN;
		else
			dtxswc &= ~E1000_DTXSWC_VMDQ_LOOPBACK_EN;
		E1000_WRITE_REG(hw, E1000_TXSWC, dtxswc);
		break;
	default:
		/* Currently no other hardware supports loopback */
		break;
	}


}