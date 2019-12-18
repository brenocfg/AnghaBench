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
struct ofw_compat_data {int /*<<< orphan*/ * ocd_str; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ ofw_bus_is_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

const struct ofw_compat_data *
ofw_bus_search_compatible(device_t dev, const struct ofw_compat_data *compat)
{

	if (compat == NULL)
		return NULL;

	for (; compat->ocd_str != NULL; ++compat) {
		if (ofw_bus_is_compatible(dev, compat->ocd_str))
			break;
	}

	return (compat);
}