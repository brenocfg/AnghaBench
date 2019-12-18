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
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* ds_devs ; 
 int ds_finddev (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_get_devid (int /*<<< orphan*/ ) ; 
 int pci_get_subdevice (int /*<<< orphan*/ ) ; 
 int pci_get_subvendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ds_pci_probe(device_t dev)
{
	int i;
	u_int32_t subdev;

	subdev = (pci_get_subdevice(dev) << 16) | pci_get_subvendor(dev);
	i = ds_finddev(pci_get_devid(dev), subdev);
	if (i >= 0) {
		device_set_desc(dev, ds_devs[i].name);
		return BUS_PROBE_DEFAULT;
	} else
		return ENXIO;
}