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
typedef  int uint64_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 int /*<<< orphan*/  EST_TRANS_LAT ; 
 int /*<<< orphan*/  MSR_PERF_CTL ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  est_get_id16 (int*) ; 
 int rdmsr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
est_set_id16(device_t dev, uint16_t id16, int need_check)
{
	uint64_t msr;
	uint16_t new_id16;
	int ret = 0;

	/* Read the current register, mask out the old, set the new id. */
	msr = rdmsr(MSR_PERF_CTL);
	msr = (msr & ~0xffff) | id16;
	wrmsr(MSR_PERF_CTL, msr);

	if  (need_check) {
		/* Wait a short while and read the new status. */
		DELAY(EST_TRANS_LAT);
		est_get_id16(&new_id16);
		if (new_id16 != id16) {
			if (bootverbose)
				device_printf(dev, "Invalid id16 (set, cur) "
				    "= (%u, %u)\n", id16, new_id16);
			ret = ENXIO;
		}
	}
	return (ret);
}