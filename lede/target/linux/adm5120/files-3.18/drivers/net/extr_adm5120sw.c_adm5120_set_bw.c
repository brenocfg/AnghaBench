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
 int /*<<< orphan*/  SWITCH_REG_BW_CNTL0 ; 
 int /*<<< orphan*/  SWITCH_REG_BW_CNTL1 ; 
 int /*<<< orphan*/  SW_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sw_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sw_write_reg (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void adm5120_set_bw(char *matrix)
{
	unsigned long val;

	/* Port 0 to 3 are set using the bandwidth control 0 register */
	val = matrix[0] + (matrix[1]<<8) + (matrix[2]<<16) + (matrix[3]<<24);
	sw_write_reg(SWITCH_REG_BW_CNTL0, val);

	/* Port 4 and 5 are set using the bandwidth control 1 register */
	val = matrix[4];
	if (matrix[5] == 1)
		sw_write_reg(SWITCH_REG_BW_CNTL1, val | 0x80000000);
	else
		sw_write_reg(SWITCH_REG_BW_CNTL1, val & ~0x8000000);

	SW_DBG("D: ctl0 0x%ux, ctl1 0x%ux\n", sw_read_reg(SWITCH_REG_BW_CNTL0),
		sw_read_reg(SWITCH_REG_BW_CNTL1));
}