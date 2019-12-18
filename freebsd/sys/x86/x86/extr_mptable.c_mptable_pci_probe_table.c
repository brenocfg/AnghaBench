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
struct pci_probe_table_args {int bus; scalar_t__ found; } ;
struct TYPE_2__ {scalar_t__ bus_type; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 scalar_t__ PCI ; 
 TYPE_1__* busses ; 
 int /*<<< orphan*/ * mpct ; 
 int mptable_maxbusid ; 
 int /*<<< orphan*/  mptable_pci_probe_table_handler ; 
 int /*<<< orphan*/  mptable_walk_table (int /*<<< orphan*/ ,struct pci_probe_table_args*) ; 
 int pci0 ; 

int
mptable_pci_probe_table(int bus)
{
	struct pci_probe_table_args args;

	if (bus < 0)
		return (EINVAL);
	if (mpct == NULL || pci0 == -1 || pci0 + bus > mptable_maxbusid)
		return (ENXIO);
	if (busses[pci0 + bus].bus_type != PCI)
		return (ENXIO);
	args.bus = pci0 + bus;
	args.found = 0;
	mptable_walk_table(mptable_pci_probe_table_handler, &args);
	if (args.found == 0)
		return (ENXIO);
	return (0);
}