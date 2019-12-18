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
struct TYPE_2__ {unsigned int id; int state; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  TS78XX_FPGA_REGS_VIRT_BASE ; 
 int /*<<< orphan*/  pr_err (char*,int,int,unsigned int,unsigned int) ; 
 unsigned int readl (int /*<<< orphan*/ ) ; 
 TYPE_1__ ts78xx_fpga ; 
 scalar_t__ ts78xx_fpga_unload_devices () ; 

__attribute__((used)) static int ts78xx_fpga_unload(void)
{
	unsigned int fpga_id;

	fpga_id = readl(TS78XX_FPGA_REGS_VIRT_BASE);

	/*
	 * There does not seem to be a feasible way to block access to the GPIO
	 * pins from userspace (/dev/mem).  This if clause should hopefully warn
	 * those foolish enough not to follow 'policy' :)
	 *
	 * UrJTAG SVN since r1381 can be used to reprogram the FPGA
	 */
	if (ts78xx_fpga.id != fpga_id) {
		pr_err("FPGA magic/rev mismatch\n"
			"TS-78xx FPGA: was 0x%.6x/%.2x but now 0x%.6x/%.2x\n",
			(ts78xx_fpga.id >> 8) & 0xffffff, ts78xx_fpga.id & 0xff,
			(fpga_id >> 8) & 0xffffff, fpga_id & 0xff);
		ts78xx_fpga.state = -1;
		return -EBUSY;
	}

	if (ts78xx_fpga_unload_devices()) {
		ts78xx_fpga.state = -1;
		return -EBUSY;
	}

	return 0;
}