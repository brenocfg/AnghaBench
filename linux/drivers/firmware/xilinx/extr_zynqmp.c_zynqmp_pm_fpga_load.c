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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  PM_FPGA_LOAD ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/  const) ; 
 int zynqmp_pm_invoke_fn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int zynqmp_pm_fpga_load(const u64 address, const u32 size,
			       const u32 flags)
{
	return zynqmp_pm_invoke_fn(PM_FPGA_LOAD, lower_32_bits(address),
				   upper_32_bits(address), size, flags, NULL);
}