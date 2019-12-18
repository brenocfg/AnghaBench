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
struct pci_link_lookup {scalar_t__ bus; scalar_t__ device; int pin; int /*<<< orphan*/ * pci_link_ptr; } ;
struct PIR_intpin {int /*<<< orphan*/  link; } ;
struct PIR_entry {scalar_t__ pe_bus; scalar_t__ pe_device; struct PIR_intpin* pe_intpin; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_pir_find_link (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pci_pir_find_link_handler(struct PIR_entry *entry, struct PIR_intpin *intpin,
    void *arg)
{
	struct pci_link_lookup *lookup;

	lookup = (struct pci_link_lookup *)arg;
	if (entry->pe_bus == lookup->bus &&
	    entry->pe_device == lookup->device &&
	    intpin - entry->pe_intpin == lookup->pin)
		*lookup->pci_link_ptr = pci_pir_find_link(intpin->link);
}