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
struct ofw_compat_data {scalar_t__ ocd_data; int /*<<< orphan*/ * ocd_str; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int BUS_PROBE_NOWILDCARD ; 
 int ENXIO ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  ds1307_compat_data ; 
 struct ofw_compat_data* ofw_bus_search_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_status_okay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ds1307_probe(device_t dev)
{
#ifdef FDT
	const struct ofw_compat_data *compat;

	if (!ofw_bus_status_okay(dev))
		return (ENXIO);

	compat = ofw_bus_search_compatible(dev, ds1307_compat_data);

	if (compat->ocd_str == NULL)
		return (ENXIO);

	device_set_desc(dev, (const char *)compat->ocd_data);

	return (BUS_PROBE_DEFAULT);
#else
	device_set_desc(dev, "Maxim DS1307 RTC");

	return (BUS_PROBE_NOWILDCARD);
#endif
}