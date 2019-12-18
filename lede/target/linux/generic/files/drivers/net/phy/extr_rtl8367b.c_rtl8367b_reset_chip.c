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
struct rtl8366_smi {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  REG_RD (struct rtl8366_smi*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  REG_WR (struct rtl8366_smi*,int /*<<< orphan*/ ,int) ; 
 int RTL8367B_CHIP_RESET_HW ; 
 int /*<<< orphan*/  RTL8367B_CHIP_RESET_REG ; 
 int RTL8367B_RESET_DELAY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int rtl8367b_reset_chip(struct rtl8366_smi *smi)
{
	int timeout = 10;
	int err;
	u32 data;

	REG_WR(smi, RTL8367B_CHIP_RESET_REG, RTL8367B_CHIP_RESET_HW);
	msleep(RTL8367B_RESET_DELAY);

	do {
		REG_RD(smi, RTL8367B_CHIP_RESET_REG, &data);
		if (!(data & RTL8367B_CHIP_RESET_HW))
			break;

		msleep(1);
	} while (--timeout);

	if (!timeout) {
		dev_err(smi->parent, "chip reset timed out\n");
		return -ETIMEDOUT;
	}

	return 0;
}