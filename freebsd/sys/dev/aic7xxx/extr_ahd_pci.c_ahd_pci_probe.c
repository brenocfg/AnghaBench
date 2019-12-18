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
struct ahd_pci_identity {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 struct ahd_pci_identity* ahd_find_pci_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ahd_pci_probe(device_t dev)
{
	struct	ahd_pci_identity *entry;

	entry = ahd_find_pci_device(dev);
	if (entry != NULL) {
		device_set_desc(dev, entry->name);
		return (BUS_PROBE_DEFAULT);
	}
	return (ENXIO);
}