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
typedef  int /*<<< orphan*/  u_int ;
struct bhnd_core_clkctl {int /*<<< orphan*/  cc_pmu_dev; } ;
typedef  scalar_t__ device_t ;
typedef  int /*<<< orphan*/  bhnd_clock ;

/* Variables and functions */
 int EINVAL ; 
 struct bhnd_core_clkctl* bhnd_get_pmu_info (scalar_t__) ; 
 int bhnd_pmu_get_clock_latency (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 
 int /*<<< orphan*/  panic (char*) ; 

int
bhnd_generic_get_clock_latency(device_t dev, device_t child, bhnd_clock clock,
    u_int *latency)
{
	struct bhnd_core_clkctl *clkctl;

	if (device_get_parent(child) != dev)
		return (EINVAL);

	if ((clkctl = bhnd_get_pmu_info(child)) == NULL)
		panic("no active PMU allocation");

	return (bhnd_pmu_get_clock_latency(clkctl->cc_pmu_dev, clock, latency));
}