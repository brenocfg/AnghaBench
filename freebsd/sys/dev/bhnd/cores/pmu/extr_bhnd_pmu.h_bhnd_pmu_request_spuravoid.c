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
typedef  int /*<<< orphan*/  bhnd_pmu_spuravoid ;

/* Variables and functions */
 int BHND_PMU_REQUEST_SPURAVOID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
bhnd_pmu_request_spuravoid(device_t dev, bhnd_pmu_spuravoid spuravoid)
{
	return (BHND_PMU_REQUEST_SPURAVOID(dev, spuravoid));
}