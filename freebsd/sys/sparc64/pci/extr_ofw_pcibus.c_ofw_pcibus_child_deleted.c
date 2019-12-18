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
struct ofw_pcibus_devinfo {int /*<<< orphan*/  opd_obdinfo; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct ofw_pcibus_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_gen_destroy_devinfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_child_deleted (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ofw_pcibus_child_deleted(device_t dev, device_t child)
{
	struct ofw_pcibus_devinfo *dinfo;

	dinfo = device_get_ivars(dev);
	ofw_bus_gen_destroy_devinfo(&dinfo->opd_obdinfo);
	pci_child_deleted(dev, child);
}