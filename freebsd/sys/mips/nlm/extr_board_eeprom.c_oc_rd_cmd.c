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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  OC_I2C_CMD_REG ; 
 int /*<<< orphan*/  OC_I2C_DATA_REG ; 
 int /*<<< orphan*/  OC_STATUS_TIP ; 
 int oc_read_reg (int /*<<< orphan*/ ) ; 
 scalar_t__ oc_wait_on_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oc_write_reg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
oc_rd_cmd(uint8_t cmd)
{
	uint8_t data;

		oc_write_reg(OC_I2C_CMD_REG, cmd);
		if (oc_wait_on_status(OC_STATUS_TIP) < 0)
			return (-1);

	data = oc_read_reg(OC_I2C_DATA_REG);
	return (data);
}