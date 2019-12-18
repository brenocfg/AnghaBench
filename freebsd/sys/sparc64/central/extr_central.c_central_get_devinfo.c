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
struct ofw_bus_devinfo {int dummy; } ;
struct central_devinfo {struct ofw_bus_devinfo const cdi_obdinfo; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct central_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct ofw_bus_devinfo *
central_get_devinfo(device_t bus, device_t child)
{
	struct central_devinfo *cdi;

	cdi = device_get_ivars(child);
	return (&cdi->cdi_obdinfo);
}