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
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_IMPL_CAVIUM ; 
 int CPU_IMPL_MASK ; 
 int /*<<< orphan*/  CPU_MATCH (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CPU_PART_MASK ; 
 int /*<<< orphan*/  CPU_PART_THUNDERX ; 
 int EINVAL ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int THUNDER_CFG_BASE_TO_ECAM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_get_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 

int
thunder_pcie_identify_ecam(device_t dev, int *ecam)
{
	rman_res_t start;

	/* Check if we're running on Cavium ThunderX */
	if (!CPU_MATCH(CPU_IMPL_MASK | CPU_PART_MASK,
	    CPU_IMPL_CAVIUM, CPU_PART_THUNDERX, 0, 0))
		return (EINVAL);

	start = bus_get_resource_start(dev, SYS_RES_MEMORY, 0);
	*ecam = THUNDER_CFG_BASE_TO_ECAM(start);

	device_printf(dev, "ThunderX quirk, setting ECAM to %d\n", *ecam);

	return (0);
}