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

/* Variables and functions */
 int ACPI_END ; 
 int ACPI_GPE0_BLK ; 
 int ACPI_PM_CNT_BLK ; 
 int ACPI_PM_EVT_BLK ; 
 int inl (int) ; 
 int /*<<< orphan*/  outl (int,int) ; 
 int /*<<< orphan*/  outw (int,int) ; 
 int pm2_ioread (int) ; 
 int /*<<< orphan*/  pm2_iowrite (int,int) ; 
 int pm_ioread (int) ; 
 int /*<<< orphan*/  pm_iowrite (int,int) ; 

void acpi_registers_setup(void)
{
	u32 value;

	/* PM Status Base */
	pm_iowrite(0x20, ACPI_PM_EVT_BLK & 0xff);
	pm_iowrite(0x21, ACPI_PM_EVT_BLK >> 8);

	/* PM Control Base */
	pm_iowrite(0x22, ACPI_PM_CNT_BLK & 0xff);
	pm_iowrite(0x23, ACPI_PM_CNT_BLK >> 8);

	/* GPM Base */
	pm_iowrite(0x28, ACPI_GPE0_BLK & 0xff);
	pm_iowrite(0x29, ACPI_GPE0_BLK >> 8);

	/* ACPI End */
	pm_iowrite(0x2e, ACPI_END & 0xff);
	pm_iowrite(0x2f, ACPI_END >> 8);

	/* IO Decode: When AcpiDecodeEnable set, South-Bridge uses the contents
	 * of the PM registers at index 0x20~0x2B to decode ACPI I/O address. */
	pm_iowrite(0x0e, 1 << 3);

	/* SCI_EN set */
	outw(1, ACPI_PM_CNT_BLK);

	/* Enable to generate SCI */
	pm_iowrite(0x10, pm_ioread(0x10) | 1);

	/* GPM3/GPM9 enable */
	value = inl(ACPI_GPE0_BLK + 4);
	outl(value | (1 << 14) | (1 << 22), ACPI_GPE0_BLK + 4);

	/* Set GPM9 as input */
	pm_iowrite(0x8d, pm_ioread(0x8d) & (~(1 << 1)));

	/* Set GPM9 as non-output */
	pm_iowrite(0x94, pm_ioread(0x94) | (1 << 3));

	/* GPM3 config ACPI trigger SCIOUT */
	pm_iowrite(0x33, pm_ioread(0x33) & (~(3 << 4)));

	/* GPM9 config ACPI trigger SCIOUT */
	pm_iowrite(0x3d, pm_ioread(0x3d) & (~(3 << 2)));

	/* GPM3 config falling edge trigger */
	pm_iowrite(0x37, pm_ioread(0x37) & (~(1 << 6)));

	/* No wait for STPGNT# in ACPI Sx state */
	pm_iowrite(0x7c, pm_ioread(0x7c) | (1 << 6));

	/* Set GPM3 pull-down enable */
	value = pm2_ioread(0xf6);
	value |= ((1 << 7) | (1 << 3));
	pm2_iowrite(0xf6, value);

	/* Set GPM9 pull-down enable */
	value = pm2_ioread(0xf8);
	value |= ((1 << 5) | (1 << 1));
	pm2_iowrite(0xf8, value);
}