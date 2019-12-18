#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int id; int state; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  TS78XX_FPGA_REGS_VIRT_BASE ; 
 int /*<<< orphan*/  pr_info (char*,int,int) ; 
 int readl (int /*<<< orphan*/ ) ; 
 TYPE_1__ ts78xx_fpga ; 
 scalar_t__ ts78xx_fpga_load_devices () ; 
 int /*<<< orphan*/  ts78xx_fpga_supports () ; 

__attribute__((used)) static int ts78xx_fpga_load(void)
{
	ts78xx_fpga.id = readl(TS78XX_FPGA_REGS_VIRT_BASE);

	pr_info("FPGA magic=0x%.6x, rev=0x%.2x\n",
			(ts78xx_fpga.id >> 8) & 0xffffff,
			ts78xx_fpga.id & 0xff);

	ts78xx_fpga_supports();

	if (ts78xx_fpga_load_devices()) {
		ts78xx_fpga.state = -1;
		return -EBUSY;
	}

	return 0;
}