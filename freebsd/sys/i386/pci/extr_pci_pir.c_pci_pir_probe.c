#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* pt_entry; } ;
struct TYPE_3__ {int pe_bus; } ;

/* Variables and functions */
 int pci_route_count ; 
 TYPE_2__* pci_route_table ; 
 int /*<<< orphan*/  pir_parsed ; 

int
pci_pir_probe(int bus, int require_parse)
{
	int i;

	if (pci_route_table == NULL || (require_parse && !pir_parsed))
		return (0);
	for (i = 0; i < pci_route_count; i++)
		if (pci_route_table->pt_entry[i].pe_bus == bus)
			return (1);
	return (0);
}