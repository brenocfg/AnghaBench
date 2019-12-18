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
typedef  enum dfl_fpga_devt_type { ____Placeholder_dfl_fpga_devt_type } dfl_fpga_devt_type ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_2__ {int /*<<< orphan*/  devt; } ;

/* Variables and functions */
 int DFL_FPGA_DEVT_MAX ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* dfl_chrdevs ; 

__attribute__((used)) static dev_t dfl_get_devt(enum dfl_fpga_devt_type type, int id)
{
	if (type >= DFL_FPGA_DEVT_MAX)
		return 0;

	return MKDEV(MAJOR(dfl_chrdevs[type].devt), id);
}