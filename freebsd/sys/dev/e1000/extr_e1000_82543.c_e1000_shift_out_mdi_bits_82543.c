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
typedef  int u16 ;
struct e1000_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_CTRL ; 
 int E1000_CTRL_MDC_DIR ; 
 int E1000_CTRL_MDIO ; 
 int E1000_CTRL_MDIO_DIR ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_WRITE_FLUSH (struct e1000_hw*) ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  e1000_lower_mdi_clk_82543 (struct e1000_hw*,int*) ; 
 int /*<<< orphan*/  e1000_raise_mdi_clk_82543 (struct e1000_hw*,int*) ; 
 int /*<<< orphan*/  usec_delay (int) ; 

__attribute__((used)) static void e1000_shift_out_mdi_bits_82543(struct e1000_hw *hw, u32 data,
					   u16 count)
{
	u32 ctrl, mask;

	/*
	 * We need to shift "count" number of bits out to the PHY.  So, the
	 * value in the "data" parameter will be shifted out to the PHY one
	 * bit at a time.  In order to do this, "data" must be broken down
	 * into bits.
	 */
	mask = 0x01;
	mask <<= (count - 1);

	ctrl = E1000_READ_REG(hw, E1000_CTRL);

	/* Set MDIO_DIR and MDC_DIR direction bits to be used as output pins. */
	ctrl |= (E1000_CTRL_MDIO_DIR | E1000_CTRL_MDC_DIR);

	while (mask) {
		/*
		 * A "1" is shifted out to the PHY by setting the MDIO bit to
		 * "1" and then raising and lowering the Management Data Clock.
		 * A "0" is shifted out to the PHY by setting the MDIO bit to
		 * "0" and then raising and lowering the clock.
		 */
		if (data & mask)
			ctrl |= E1000_CTRL_MDIO;
		else
			ctrl &= ~E1000_CTRL_MDIO;

		E1000_WRITE_REG(hw, E1000_CTRL, ctrl);
		E1000_WRITE_FLUSH(hw);

		usec_delay(10);

		e1000_raise_mdi_clk_82543(hw, &ctrl);
		e1000_lower_mdi_clk_82543(hw, &ctrl);

		mask >>= 1;
	}
}