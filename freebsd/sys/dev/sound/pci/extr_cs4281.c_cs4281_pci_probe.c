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
 int BUS_PROBE_DEFAULT ; 
#define  CS4281_PCI_ID 128 
 int ENXIO ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int pci_get_devid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cs4281_pci_probe(device_t dev)
{
    char *s = NULL;

    switch (pci_get_devid(dev)) {
    case CS4281_PCI_ID:
	s = "Crystal Semiconductor CS4281";
	break;
    }

    if (s)
	device_set_desc(dev, s);
    return s ? BUS_PROBE_DEFAULT : ENXIO;
}