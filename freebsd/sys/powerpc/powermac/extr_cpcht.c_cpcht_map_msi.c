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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct pcicfg_ht {int /*<<< orphan*/  ht_msiaddr; } ;
struct TYPE_2__ {struct pcicfg_ht ht; } ;
struct pci_devinfo {TYPE_1__ cfg; } ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int ENXIO ; 
 struct pci_devinfo* device_get_ivars (scalar_t__) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 

__attribute__((used)) static int
cpcht_map_msi(device_t dev, device_t child, int irq, uint64_t *addr,
    uint32_t *data)
{
	device_t pcib;
	struct pci_devinfo *dinfo;
	struct pcicfg_ht *ht = NULL;

	for (pcib = child; pcib != dev; pcib =
	    device_get_parent(device_get_parent(pcib))) {
		dinfo = device_get_ivars(pcib);
		ht = &dinfo->cfg.ht;

		if (ht == NULL)
			continue;
	}

	if (ht == NULL)
		return (ENXIO);

	*addr = ht->ht_msiaddr;
	*data = irq & 0xff;

	return (0);
}