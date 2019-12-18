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
struct cf_setting {int /*<<< orphan*/ * spec; int /*<<< orphan*/  dev; int /*<<< orphan*/  volts; int /*<<< orphan*/  lat; int /*<<< orphan*/  power; int /*<<< orphan*/  freq; } ;
struct acpi_px {int /*<<< orphan*/  sts_val; int /*<<< orphan*/  ctrl_val; int /*<<< orphan*/  trans_lat; int /*<<< orphan*/  power; int /*<<< orphan*/  core_freq; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_VAL_UNKNOWN ; 
 int EINVAL ; 
 size_t PX_SPEC_CONTROL ; 
 size_t PX_SPEC_STATUS ; 

__attribute__((used)) static int
acpi_px_to_set(device_t dev, struct acpi_px *px, struct cf_setting *set)
{

	if (px == NULL || set == NULL)
		return (EINVAL);

	set->freq = px->core_freq;
	set->power = px->power;
	/* XXX Include BM latency too? */
	set->lat = px->trans_lat;
	set->volts = CPUFREQ_VAL_UNKNOWN;
	set->dev = dev;
	set->spec[PX_SPEC_CONTROL] = px->ctrl_val;
	set->spec[PX_SPEC_STATUS] = px->sts_val;

	return (0);
}