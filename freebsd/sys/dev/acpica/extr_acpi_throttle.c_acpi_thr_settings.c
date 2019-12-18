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
struct cf_setting {int /*<<< orphan*/  dev; int /*<<< orphan*/  freq; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_VAL_UNKNOWN ; 
 int CPU_MAX_SPEED ; 
 int /*<<< orphan*/  CPU_SPEED_PERCENT (int) ; 
 int E2BIG ; 
 int EINVAL ; 
 int /*<<< orphan*/  memset (struct cf_setting*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
acpi_thr_settings(device_t dev, struct cf_setting *sets, int *count)
{
	int i, speed;

	if (sets == NULL || count == NULL)
		return (EINVAL);
	if (*count < CPU_MAX_SPEED)
		return (E2BIG);

	/* Return a list of valid settings for this driver. */
	memset(sets, CPUFREQ_VAL_UNKNOWN, sizeof(*sets) * CPU_MAX_SPEED);
	for (i = 0, speed = CPU_MAX_SPEED; speed != 0; i++, speed--) {
		sets[i].freq = CPU_SPEED_PERCENT(speed);
		sets[i].dev = dev;
	}
	*count = CPU_MAX_SPEED;

	return (0);
}