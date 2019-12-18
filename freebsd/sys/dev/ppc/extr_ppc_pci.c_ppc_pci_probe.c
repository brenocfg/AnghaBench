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
typedef  int uint32_t ;
struct pci_id {int type; int /*<<< orphan*/  rid; int /*<<< orphan*/  desc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pci_get_devid (int /*<<< orphan*/ ) ; 
 struct pci_id* pci_ids ; 
 int ppc_probe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ppc_pci_probe(device_t dev)
{
	struct pci_id *id;
	uint32_t type;

	type = pci_get_devid(dev);
	id = pci_ids;
	while (id->type != 0xffff && id->type != type)
		id++;
	if (id->type == 0xffff)
		return (ENXIO);
	device_set_desc(dev, id->desc);
	return (ppc_probe(dev, id->rid));
}