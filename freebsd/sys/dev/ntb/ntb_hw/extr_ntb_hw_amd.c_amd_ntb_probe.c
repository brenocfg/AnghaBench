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
struct pci_device_table {int /*<<< orphan*/  descr; scalar_t__ driver_data; } ;
struct amd_ntb_softc {struct amd_ntb_hw_info* hw_info; int /*<<< orphan*/  spad_count; } ;
struct amd_ntb_hw_info {int /*<<< orphan*/  spad_count; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_GENERIC ; 
 int ENXIO ; 
 struct pci_device_table* PCI_MATCH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amd_ntb_devs ; 
 struct amd_ntb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
amd_ntb_probe(device_t device)
{
	struct amd_ntb_softc *ntb = device_get_softc(device);
	const struct pci_device_table *tbl;

	tbl = PCI_MATCH(device, amd_ntb_devs);
	if (tbl == NULL)
		return (ENXIO);

	ntb->hw_info = (struct amd_ntb_hw_info *)tbl->driver_data;
	ntb->spad_count = ntb->hw_info->spad_count;
	device_set_desc(device, tbl->descr);

	return (BUS_PROBE_GENERIC);
}