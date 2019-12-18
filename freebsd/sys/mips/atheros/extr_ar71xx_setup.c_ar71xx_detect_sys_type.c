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
typedef  int uint32_t ;

/* Variables and functions */
#define  AR71XX_REV_ID_MINOR_AR7130 146 
#define  AR71XX_REV_ID_MINOR_AR7141 145 
#define  AR71XX_REV_ID_MINOR_AR7161 144 
 int AR71XX_REV_ID_MINOR_MASK ; 
 int AR71XX_REV_ID_REVISION_MASK ; 
 int AR71XX_REV_ID_REVISION_SHIFT ; 
 int /*<<< orphan*/  AR71XX_RST_RESET_REG_REV_ID ; 
 int /*<<< orphan*/  AR71XX_SOC_AR7130 ; 
 int /*<<< orphan*/  AR71XX_SOC_AR7141 ; 
 int /*<<< orphan*/  AR71XX_SOC_AR7161 ; 
 int /*<<< orphan*/  AR71XX_SOC_AR7240 ; 
 int /*<<< orphan*/  AR71XX_SOC_AR7241 ; 
 int /*<<< orphan*/  AR71XX_SOC_AR7242 ; 
 int /*<<< orphan*/  AR71XX_SOC_AR9130 ; 
 int /*<<< orphan*/  AR71XX_SOC_AR9132 ; 
 int /*<<< orphan*/  AR71XX_SOC_AR9330 ; 
 int /*<<< orphan*/  AR71XX_SOC_AR9331 ; 
 int /*<<< orphan*/  AR71XX_SOC_AR9341 ; 
 int /*<<< orphan*/  AR71XX_SOC_AR9342 ; 
 int /*<<< orphan*/  AR71XX_SOC_AR9344 ; 
 int /*<<< orphan*/  AR71XX_SOC_QCA9533 ; 
 int /*<<< orphan*/  AR71XX_SOC_QCA9533_V2 ; 
 int /*<<< orphan*/  AR71XX_SOC_QCA9556 ; 
 int /*<<< orphan*/  AR71XX_SOC_QCA9558 ; 
 int AR724X_REV_ID_REVISION_MASK ; 
#define  AR91XX_REV_ID_MINOR_AR9130 143 
#define  AR91XX_REV_ID_MINOR_AR9132 142 
 int AR91XX_REV_ID_MINOR_MASK ; 
 int AR91XX_REV_ID_REVISION_MASK ; 
 int AR91XX_REV_ID_REVISION_SHIFT ; 
 int AR933X_REV_ID_REVISION_MASK ; 
 int AR934X_REV_ID_REVISION_MASK ; 
 int ATH_READ_REG (int /*<<< orphan*/ ) ; 
 int QCA953X_REV_ID_REVISION_MASK ; 
 int QCA955X_REV_ID_REVISION_MASK ; 
#define  REV_ID_MAJOR_AR71XX 141 
#define  REV_ID_MAJOR_AR7240 140 
#define  REV_ID_MAJOR_AR7241 139 
#define  REV_ID_MAJOR_AR7242 138 
#define  REV_ID_MAJOR_AR913X 137 
#define  REV_ID_MAJOR_AR9330 136 
#define  REV_ID_MAJOR_AR9331 135 
#define  REV_ID_MAJOR_AR9341 134 
#define  REV_ID_MAJOR_AR9342 133 
#define  REV_ID_MAJOR_AR9344 132 
 int REV_ID_MAJOR_MASK ; 
#define  REV_ID_MAJOR_QCA9533 131 
#define  REV_ID_MAJOR_QCA9533_V2 130 
#define  REV_ID_MAJOR_QCA9556 129 
#define  REV_ID_MAJOR_QCA9558 128 
 int /*<<< orphan*/  ar71xx_chip_def ; 
 int /*<<< orphan*/ * ar71xx_cpu_ops ; 
 int /*<<< orphan*/  ar71xx_soc ; 
 int /*<<< orphan*/  ar71xx_sys_type ; 
 int /*<<< orphan*/  ar724x_chip_def ; 
 int /*<<< orphan*/  ar91xx_chip_def ; 
 int /*<<< orphan*/  ar933x_chip_def ; 
 int /*<<< orphan*/  ar934x_chip_def ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  qca953x_chip_def ; 
 int /*<<< orphan*/  qca955x_chip_def ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,int) ; 

void
ar71xx_detect_sys_type(void)
{
	char *chip = "????";
	uint32_t id;
	uint32_t major;
	uint32_t minor;
	uint32_t rev = 0;

	id = ATH_READ_REG(AR71XX_RST_RESET_REG_REV_ID);
	major = id & REV_ID_MAJOR_MASK;

	switch (major) {
	case REV_ID_MAJOR_AR71XX:
		minor = id & AR71XX_REV_ID_MINOR_MASK;
		rev = id >> AR71XX_REV_ID_REVISION_SHIFT;
		rev &= AR71XX_REV_ID_REVISION_MASK;
		ar71xx_cpu_ops = &ar71xx_chip_def;
		switch (minor) {
		case AR71XX_REV_ID_MINOR_AR7130:
			ar71xx_soc = AR71XX_SOC_AR7130;
			chip = "7130";
			break;

		case AR71XX_REV_ID_MINOR_AR7141:
			ar71xx_soc = AR71XX_SOC_AR7141;
			chip = "7141";
			break;

		case AR71XX_REV_ID_MINOR_AR7161:
			ar71xx_soc = AR71XX_SOC_AR7161;
			chip = "7161";
			break;
		}
		break;

	case REV_ID_MAJOR_AR7240:
		ar71xx_soc = AR71XX_SOC_AR7240;
		chip = "7240";
		ar71xx_cpu_ops = &ar724x_chip_def;
		rev = (id & AR724X_REV_ID_REVISION_MASK);
		break;

	case REV_ID_MAJOR_AR7241:
		ar71xx_soc = AR71XX_SOC_AR7241;
		chip = "7241";
		ar71xx_cpu_ops = &ar724x_chip_def;
		rev = (id & AR724X_REV_ID_REVISION_MASK);
		break;

	case REV_ID_MAJOR_AR7242:
		ar71xx_soc = AR71XX_SOC_AR7242;
		chip = "7242";
		ar71xx_cpu_ops = &ar724x_chip_def;
		rev = (id & AR724X_REV_ID_REVISION_MASK);
		break;

	case REV_ID_MAJOR_AR913X:
		minor = id & AR91XX_REV_ID_MINOR_MASK;
		rev = id >> AR91XX_REV_ID_REVISION_SHIFT;
		rev &= AR91XX_REV_ID_REVISION_MASK;
		ar71xx_cpu_ops = &ar91xx_chip_def;
		switch (minor) {
		case AR91XX_REV_ID_MINOR_AR9130:
			ar71xx_soc = AR71XX_SOC_AR9130;
			chip = "9130";
			break;

		case AR91XX_REV_ID_MINOR_AR9132:
			ar71xx_soc = AR71XX_SOC_AR9132;
			chip = "9132";
			break;
		}
		break;
	case REV_ID_MAJOR_AR9330:
		minor = 0;
		rev = (id & AR933X_REV_ID_REVISION_MASK);
		chip = "9330";
		ar71xx_cpu_ops = &ar933x_chip_def;
		ar71xx_soc = AR71XX_SOC_AR9330;
		break;
	case REV_ID_MAJOR_AR9331:
		minor = 1;
		rev = (id & AR933X_REV_ID_REVISION_MASK);
		chip = "9331";
		ar71xx_soc = AR71XX_SOC_AR9331;
		ar71xx_cpu_ops = &ar933x_chip_def;
		break;

	case REV_ID_MAJOR_AR9341:
		minor = 0;
		rev = (id & AR934X_REV_ID_REVISION_MASK);
		chip = "9341";
		ar71xx_soc = AR71XX_SOC_AR9341;
		ar71xx_cpu_ops = &ar934x_chip_def;
		break;

	case REV_ID_MAJOR_AR9342:
		minor = 0;
		rev = (id & AR934X_REV_ID_REVISION_MASK);
		chip = "9342";
		ar71xx_soc = AR71XX_SOC_AR9342;
		ar71xx_cpu_ops = &ar934x_chip_def;
		break;

	case REV_ID_MAJOR_AR9344:
		minor = 0;
		rev = (id & AR934X_REV_ID_REVISION_MASK);
		chip = "9344";
		ar71xx_soc = AR71XX_SOC_AR9344;
		ar71xx_cpu_ops = &ar934x_chip_def;
		break;

	case REV_ID_MAJOR_QCA9533:
		minor = 0;
		rev = (id & QCA953X_REV_ID_REVISION_MASK);
		chip = "9533";
		ar71xx_soc = AR71XX_SOC_QCA9533;
		ar71xx_cpu_ops = &qca953x_chip_def;
		break;

	case REV_ID_MAJOR_QCA9533_V2:
		minor = 0;
		rev = (id & QCA953X_REV_ID_REVISION_MASK);
		chip = "9533v2";
		ar71xx_soc = AR71XX_SOC_QCA9533_V2;
		ar71xx_cpu_ops = &qca953x_chip_def;
		break;

	case REV_ID_MAJOR_QCA9556:
		minor = 0;
		rev = (id & QCA955X_REV_ID_REVISION_MASK);
		chip = "9556";
		ar71xx_soc = AR71XX_SOC_QCA9556;
		ar71xx_cpu_ops = &qca955x_chip_def;
		break;

	case REV_ID_MAJOR_QCA9558:
		minor = 0;
		rev = (id & QCA955X_REV_ID_REVISION_MASK);
		chip = "9558";
		ar71xx_soc = AR71XX_SOC_QCA9558;
		ar71xx_cpu_ops = &qca955x_chip_def;
		break;

	default:
		panic("ar71xx: unknown chip id:0x%08x\n", id);
	}

	sprintf(ar71xx_sys_type, "Atheros AR%s rev %u", chip, rev);
}