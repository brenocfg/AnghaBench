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
struct sh_mobile_lcdc_sys_bus_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int /*<<< orphan*/  magic0_data ; 
 int /*<<< orphan*/  magic1_data ; 
 int /*<<< orphan*/  magic2_data ; 
 int /*<<< orphan*/  magic3_data ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  migor_lcd_qvga_seq (void*,struct sh_mobile_lcdc_sys_bus_ops*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int read_reg16 (void*,struct sh_mobile_lcdc_sys_bus_ops*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_lcd_module () ; 
 int /*<<< orphan*/  sync_data ; 
 int /*<<< orphan*/  write_reg (void*,struct sh_mobile_lcdc_sys_bus_ops*,int,int) ; 
 int /*<<< orphan*/  write_reg16 (void*,struct sh_mobile_lcdc_sys_bus_ops*,int,int) ; 

int migor_lcd_qvga_setup(void *sohandle, struct sh_mobile_lcdc_sys_bus_ops *so)
{
	unsigned long xres = 320;
	unsigned long yres = 240;
	int k;

	reset_lcd_module();
	migor_lcd_qvga_seq(sohandle, so, sync_data, ARRAY_SIZE(sync_data));

	if (read_reg16(sohandle, so, 0) != 0x1505)
		return -ENODEV;

	pr_info("Migo-R QVGA LCD Module detected.\n");

	migor_lcd_qvga_seq(sohandle, so, sync_data, ARRAY_SIZE(sync_data));
	write_reg16(sohandle, so, 0x00A4, 0x0001);
	mdelay(10);

	migor_lcd_qvga_seq(sohandle, so, magic0_data, ARRAY_SIZE(magic0_data));
	mdelay(100);

	migor_lcd_qvga_seq(sohandle, so, magic1_data, ARRAY_SIZE(magic1_data));
	write_reg16(sohandle, so, 0x0050, 0xef - (yres - 1));
	write_reg16(sohandle, so, 0x0051, 0x00ef);
	write_reg16(sohandle, so, 0x0052, 0x0000);
	write_reg16(sohandle, so, 0x0053, xres - 1);

	migor_lcd_qvga_seq(sohandle, so, magic2_data, ARRAY_SIZE(magic2_data));
	mdelay(10);

	migor_lcd_qvga_seq(sohandle, so, magic3_data, ARRAY_SIZE(magic3_data));
	mdelay(40);

	/* clear GRAM to avoid displaying garbage */

	write_reg16(sohandle, so, 0x0020, 0x0000); /* horiz addr */
	write_reg16(sohandle, so, 0x0021, 0x0000); /* vert addr */

	for (k = 0; k < (xres * 256); k++) /* yes, 256 words per line */
		write_reg16(sohandle, so, 0x0022, 0x0000);

	write_reg16(sohandle, so, 0x0020, 0x0000); /* reset horiz addr */
	write_reg16(sohandle, so, 0x0021, 0x0000); /* reset vert addr */
	write_reg16(sohandle, so, 0x0007, 0x0173);
	mdelay(40);

	/* enable display */
	write_reg(sohandle, so, 0x00, 0x22);
	mdelay(100);
	return 0;
}