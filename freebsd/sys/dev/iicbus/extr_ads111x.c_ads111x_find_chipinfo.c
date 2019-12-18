#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ads111x_chipinfo {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ ocd_data; } ;

/* Variables and functions */
 struct ads111x_chipinfo* ads111x_chip_infos ; 
 int /*<<< orphan*/  compat_data ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int nitems (struct ads111x_chipinfo*) ; 
 TYPE_1__* ofw_bus_search_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_status_okay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_string_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const**) ; 
 scalar_t__ strcasecmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct ads111x_chipinfo *
ads111x_find_chipinfo(device_t dev)
{
	const struct ads111x_chipinfo *info;
	const char *chiptype;
	int i;

#ifdef FDT
	if (ofw_bus_status_okay(dev)) {
		info = (struct ads111x_chipinfo*)
		    ofw_bus_search_compatible(dev, compat_data)->ocd_data;
		if (info != NULL)
			return (info);
	}
#endif

	/* For hinted devices, we must be told the chip type. */
	chiptype = NULL;
	resource_string_value(device_get_name(dev), device_get_unit(dev),
	    "type", &chiptype);
	if (chiptype != NULL) {
		for (i = 0; i < nitems(ads111x_chip_infos); ++i) {
			info = &ads111x_chip_infos[i];
			if (strcasecmp(chiptype, info->name) == 0)
				return (info);
		}
	}
	return (NULL);
}