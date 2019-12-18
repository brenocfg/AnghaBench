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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ pmu ; 
 int /*<<< orphan*/  pmu_extint ; 
 int setup_pmu_intr (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pmuextint_attach(device_t dev)
{
	pmu_extint = dev;
	if (pmu)
		return (setup_pmu_intr(pmu,dev));

	return (0);
}