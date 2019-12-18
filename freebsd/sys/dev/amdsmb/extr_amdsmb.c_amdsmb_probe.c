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
struct pci_device_table {int /*<<< orphan*/  descr; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 struct pci_device_table* PCI_MATCH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdsmb_devs ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
amdsmb_probe(device_t dev)
{
	const struct pci_device_table *tbl;

	tbl = PCI_MATCH(dev, amdsmb_devs);
	if (tbl == NULL)
		return (ENXIO);
	device_set_desc(dev, tbl->descr);

	return (BUS_PROBE_DEFAULT);
}