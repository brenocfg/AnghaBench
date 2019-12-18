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
struct rtl8366_smi {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int RTL8366S_CHIP_CTRL_RESET_HW ; 
 int /*<<< orphan*/  RTL8366S_RESET_CTRL_REG ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  printk (char*) ; 
 scalar_t__ rtl8366_smi_read_reg (struct rtl8366_smi*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rtl8366_smi_write_reg_noack (struct rtl8366_smi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rtl8366s_reset_chip(struct rtl8366_smi *smi)
{
	int timeout = 10;
	u32 data;

	rtl8366_smi_write_reg_noack(smi, RTL8366S_RESET_CTRL_REG,
				    RTL8366S_CHIP_CTRL_RESET_HW);
	do {
		msleep(1);
		if (rtl8366_smi_read_reg(smi, RTL8366S_RESET_CTRL_REG, &data))
			return -EIO;

		if (!(data & RTL8366S_CHIP_CTRL_RESET_HW))
			break;
	} while (--timeout);

	if (!timeout) {
		printk("Timeout waiting for the switch to reset\n");
		return -EIO;
	}

	return 0;
}