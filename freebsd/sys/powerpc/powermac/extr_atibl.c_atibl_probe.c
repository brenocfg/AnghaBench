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
typedef  int phandle_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  control ;

/* Variables and functions */
 int ENXIO ; 
 int OF_finddevice (char*) ; 
 scalar_t__ OF_getprop (int,char*,char**,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int pci_get_vendor (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
atibl_probe(device_t dev)
{
	char		control[8];
	phandle_t	handle;

	handle = OF_finddevice("mac-io/backlight");

	if (handle == -1)
		return (ENXIO);

	if (OF_getprop(handle, "backlight-control", &control, sizeof(control)) < 0)
		return (ENXIO);

	if (strcmp(control, "ati") != 0 &&
	    (strcmp(control, "mnca") != 0 ||
	    pci_get_vendor(device_get_parent(dev)) != 0x1002))
		return (ENXIO);

	device_set_desc(dev, "PowerBook backlight for ATI graphics");

	return (0);
}