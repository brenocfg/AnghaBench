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
struct pci_dev_lookup {scalar_t__ link; int bus; struct PIR_intpin* pin; int /*<<< orphan*/  device; } ;
struct PIR_intpin {scalar_t__ link; } ;
struct PIR_entry {int pe_bus; int pe_intpin; int /*<<< orphan*/  pe_device; } ;

/* Variables and functions */

__attribute__((used)) static void
pir_resume_find_device(struct PIR_entry *entry, struct PIR_intpin *intpin,
    void *arg)
{
	struct pci_dev_lookup *pd;

	pd = (struct pci_dev_lookup *)arg;
	if (intpin->link != pd->link || pd->bus != -1)
		return;
	pd->bus = entry->pe_bus;
	pd->device = entry->pe_device;
	pd->pin = intpin - entry->pe_intpin;
}