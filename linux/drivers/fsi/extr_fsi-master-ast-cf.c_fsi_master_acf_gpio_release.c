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
struct fsi_master_acf {scalar_t__ cvic; scalar_t__ sram; } ;

/* Variables and functions */
 scalar_t__ ARB_REG ; 
 scalar_t__ CVIC_TRIG_REG ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  iowrite8 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int fsi_master_acf_gpio_release(void *data)
{
	struct fsi_master_acf *master = data;

	/* Write release */
	iowrite8(0, master->sram + ARB_REG);

	/* Ring doorbell if any */
	if (master->cvic)
		iowrite32(0x2, master->cvic + CVIC_TRIG_REG);

	return 0;
}