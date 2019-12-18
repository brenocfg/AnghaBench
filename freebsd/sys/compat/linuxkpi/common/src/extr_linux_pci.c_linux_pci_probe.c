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
struct pci_driver {int /*<<< orphan*/  name; int /*<<< orphan*/  bsddriver; } ;
struct pci_device_id {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/ * device_get_driver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pci_driver* linux_pci_find (int /*<<< orphan*/ ,struct pci_device_id const**) ; 

__attribute__((used)) static int
linux_pci_probe(device_t dev)
{
	const struct pci_device_id *id;
	struct pci_driver *pdrv;

	if ((pdrv = linux_pci_find(dev, &id)) == NULL)
		return (ENXIO);
	if (device_get_driver(dev) != &pdrv->bsddriver)
		return (ENXIO);
	device_set_desc(dev, pdrv->name);
	return (0);
}