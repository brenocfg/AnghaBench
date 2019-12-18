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
struct fsi_master_acf {int /*<<< orphan*/  dev; scalar_t__ cvic; } ;

/* Variables and functions */
 scalar_t__ CVIC_EN_REG ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int copro_enable_sw_irq(struct fsi_master_acf *master)
{
	int timeout;
	uint32_t val;

	/*
	 * Enable coprocessor interrupt input. I've had problems getting the
	 * value to stick, so try in a loop
	 */
	for (timeout = 0; timeout < 10; timeout++) {
		iowrite32(0x2, master->cvic + CVIC_EN_REG);
		val = ioread32(master->cvic + CVIC_EN_REG);
		if (val & 2)
			break;
		msleep(1);
	}
	if (!(val & 2)) {
		dev_err(master->dev, "Failed to enable coprocessor interrupt !\n");
		return -ENODEV;
	}
	return 0;
}