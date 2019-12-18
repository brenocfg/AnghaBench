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
struct TYPE_2__ {scalar_t__ bus_type; } ;

/* Variables and functions */
 scalar_t__ PCI ; 
 TYPE_1__* busses ; 
 int mptable_maxbusid ; 
 int /*<<< orphan*/  panic (char*) ; 
 int pci0 ; 

__attribute__((used)) static void
mptable_pci_setup(void)
{
	int i;

	/*
	 * Find the first pci bus and call it 0.  Panic if pci0 is not
	 * bus zero and there are multiple PCI buses.
	 */
	for (i = 0; i <= mptable_maxbusid; i++)
		if (busses[i].bus_type == PCI) {
			if (pci0 == -1)
				pci0 = i;
			else if (pci0 != 0)
				panic(
		"MPTable contains multiple PCI buses but no PCI bus 0");
		}
}