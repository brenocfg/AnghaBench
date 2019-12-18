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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  device_quiet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int pci_get_devid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
emujoy_pci_probe(device_t dev)
{
	char *s = NULL;

	switch (pci_get_devid(dev)) {
	case 0x70021102:
		s = "Creative EMU10K1 Joystick";
		device_quiet(dev);
		break;
	case 0x70031102:
		s = "Creative EMU10K2 Joystick";
		device_quiet(dev);
		break;
	}

	if (s) device_set_desc(dev, s);
	return s ? -1000 : ENXIO;
}