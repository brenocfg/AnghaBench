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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bhnd_pmu_regulator ;

/* Variables and functions */
 int BHND_PMU_SET_VOLTAGE_RAW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
bhnd_pmu_set_voltage_raw(device_t dev, bhnd_pmu_regulator regulator,
    uint32_t value)
{
	return (BHND_PMU_SET_VOLTAGE_RAW(dev, regulator, value));
}