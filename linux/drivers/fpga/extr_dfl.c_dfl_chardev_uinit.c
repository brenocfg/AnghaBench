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
struct TYPE_2__ {int /*<<< orphan*/  devt; } ;

/* Variables and functions */
 int DFL_FPGA_DEVT_MAX ; 
 scalar_t__ MAJOR (int /*<<< orphan*/ ) ; 
 scalar_t__ MINORMASK ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* dfl_chrdevs ; 
 int /*<<< orphan*/  unregister_chrdev_region (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void dfl_chardev_uinit(void)
{
	int i;

	for (i = 0; i < DFL_FPGA_DEVT_MAX; i++)
		if (MAJOR(dfl_chrdevs[i].devt)) {
			unregister_chrdev_region(dfl_chrdevs[i].devt,
						 MINORMASK + 1);
			dfl_chrdevs[i].devt = MKDEV(0, 0);
		}
}