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
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bhnd_clock ;

/* Variables and functions */
 int BHND_PMU_GET_CLOCK_LATENCY (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int
bhnd_pmu_get_clock_latency(device_t dev, bhnd_clock clock, u_int *latency)
{
	return (BHND_PMU_GET_CLOCK_LATENCY(dev, clock, latency));
}