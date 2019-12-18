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
struct e1000_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_I2CPARAMS ; 
 int /*<<< orphan*/  E1000_I2C_T_BUF ; 
 int /*<<< orphan*/  E1000_I2C_T_SU_STO ; 
 int /*<<< orphan*/  E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e1000_raise_i2c_clk (struct e1000_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e1000_set_i2c_data (struct e1000_hw*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usec_delay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void e1000_i2c_stop(struct e1000_hw *hw)
{
	u32 i2cctl = E1000_READ_REG(hw, E1000_I2CPARAMS);

	DEBUGFUNC("e1000_i2c_stop");

	/* Stop condition must begin with data low and clock high */
	e1000_set_i2c_data(hw, &i2cctl, 0);
	e1000_raise_i2c_clk(hw, &i2cctl);

	/* Setup time for stop condition (4us) */
	usec_delay(E1000_I2C_T_SU_STO);

	e1000_set_i2c_data(hw, &i2cctl, 1);

	/* bus free time between stop and start (4.7us)*/
	usec_delay(E1000_I2C_T_BUF);
}