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

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SBCR ; 
 unsigned int SCBR_I2CCEN ; 
 unsigned int SCBR_I2CMEN ; 
 unsigned int fpga_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpga_write_reg (unsigned int,int /*<<< orphan*/ ) ; 
 int i2c_register_board_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdk7786_i2c_devices ; 

__attribute__((used)) static int sdk7786_i2c_setup(void)
{
	unsigned int tmp;

	/*
	 * Hand over I2C control to the FPGA.
	 */
	tmp = fpga_read_reg(SBCR);
	tmp &= ~SCBR_I2CCEN;
	tmp |= SCBR_I2CMEN;
	fpga_write_reg(tmp, SBCR);

	return i2c_register_board_info(0, sdk7786_i2c_devices,
				       ARRAY_SIZE(sdk7786_i2c_devices));
}