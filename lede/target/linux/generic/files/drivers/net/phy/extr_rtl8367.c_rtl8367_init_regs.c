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
 int ENODEV ; 
 int /*<<< orphan*/  REG_RD (struct rtl8366_smi*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  REG_WR (struct rtl8366_smi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RTL8367_CHIP_MODE_MASK ; 
 int /*<<< orphan*/  RTL8367_CHIP_MODE_REG ; 
 int /*<<< orphan*/  RTL8367_CHIP_VER_REG ; 
 int RTL8367_CHIP_VER_RLVID_MASK ; 
 int RTL8367_CHIP_VER_RLVID_SHIFT ; 
 int /*<<< orphan*/  RTL8367_RTL_MAGIC_ID_REG ; 
 int /*<<< orphan*/  RTL8367_RTL_MAGIC_ID_VAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int rtl8367_init_regs0 (struct rtl8366_smi*,int) ; 
 int rtl8367_init_regs1 (struct rtl8366_smi*,int) ; 
 int rtl8367_init_regs2 (struct rtl8366_smi*,int) ; 
 int rtl8367_read_phy_reg (struct rtl8366_smi*,int /*<<< orphan*/ ,int,int*) ; 
 int rtl8367_write_phy_reg (struct rtl8366_smi*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int rtl8367_init_regs(struct rtl8366_smi *smi)
{
	u32 data;
	u32 rlvid;
	u32 mode;
	int err;

	REG_WR(smi, RTL8367_RTL_MAGIC_ID_REG, RTL8367_RTL_MAGIC_ID_VAL);

	REG_RD(smi, RTL8367_CHIP_VER_REG, &data);
	rlvid = (data >> RTL8367_CHIP_VER_RLVID_SHIFT) &
		RTL8367_CHIP_VER_RLVID_MASK;

	REG_RD(smi, RTL8367_CHIP_MODE_REG, &data);
	mode = data & RTL8367_CHIP_MODE_MASK;

	switch (rlvid) {
	case 0:
		err = rtl8367_init_regs0(smi, mode);
		break;

	case 1:
		err = rtl8367_write_phy_reg(smi, 0, 31, 5);
		if (err)
			break;

		err = rtl8367_write_phy_reg(smi, 0, 5, 0x3ffe);
		if (err)
			break;

		err = rtl8367_read_phy_reg(smi, 0, 6, &data);
		if (err)
			break;

		if (data == 0x94eb) {
			err = rtl8367_init_regs1(smi, mode);
		} else if (data == 0x2104) {
			err = rtl8367_init_regs2(smi, mode);
		} else {
			dev_err(smi->parent, "unknow phy data %04x\n", data);
			return -ENODEV;
		}

		break;

	default:
		dev_err(smi->parent, "unknow rlvid %u\n", rlvid);
		err = -ENODEV;
		break;
	}

	return err;
}