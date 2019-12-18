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
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  devt; } ;

/* Variables and functions */
 int DFL_FPGA_DEVT_MAX ; 
 scalar_t__ MINORMASK ; 
 int alloc_chrdev_region (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dfl_chardev_uinit () ; 
 TYPE_1__* dfl_chrdevs ; 

__attribute__((used)) static int dfl_chardev_init(void)
{
	int i, ret;

	for (i = 0; i < DFL_FPGA_DEVT_MAX; i++) {
		ret = alloc_chrdev_region(&dfl_chrdevs[i].devt, 0,
					  MINORMASK + 1, dfl_chrdevs[i].name);
		if (ret)
			goto exit;
	}

	return 0;

exit:
	dfl_chardev_uinit();
	return ret;
}