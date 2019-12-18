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
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_CIM_BOOT_CFG ; 
 int /*<<< orphan*/  A_PCIE_FW ; 
 int ETIMEDOUT ; 
 int FW_CMD_MAX_TIMEOUT ; 
 int FW_SUCCESS ; 
 int F_PCIE_FW_HALT ; 
 int /*<<< orphan*/  F_UPCRST ; 
 int /*<<< orphan*/  msleep (int) ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_set_reg_field (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int t4_fw_restart(struct adapter *adap, unsigned int mbox)
{
	int ms;

	t4_set_reg_field(adap, A_CIM_BOOT_CFG, F_UPCRST, 0);
	for (ms = 0; ms < FW_CMD_MAX_TIMEOUT; ) {
		if (!(t4_read_reg(adap, A_PCIE_FW) & F_PCIE_FW_HALT))
			return FW_SUCCESS;
		msleep(100);
		ms += 100;
	}

	return -ETIMEDOUT;
}