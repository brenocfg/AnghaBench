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
typedef  int /*<<< orphan*/  u8 ;
struct pci_dev {int irq_managed; int irq; int class; int /*<<< orphan*/  dev; int /*<<< orphan*/  pin; } ;
struct acpi_prt_entry {int index; scalar_t__ link; } ;
typedef  int /*<<< orphan*/  link_desc ;

/* Variables and functions */
 int ACPI_ACTIVE_HIGH ; 
 int ACPI_ACTIVE_LOW ; 
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_IRQ_MODEL_GIC ; 
 int ACPI_LEVEL_SENSITIVE ; 
 int PCI_CLASS_STORAGE_IDE ; 
 scalar_t__ acpi_irq_model ; 
 scalar_t__ acpi_isa_register_gsi (struct pci_dev*) ; 
 struct acpi_prt_entry* acpi_pci_irq_lookup (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_pci_irq_valid (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int acpi_pci_link_allocate_irq (scalar_t__,int,int*,int*,char**) ; 
 int acpi_register_gsi (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,int,char*,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct acpi_prt_entry*) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pin_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

int acpi_pci_irq_enable(struct pci_dev *dev)
{
	struct acpi_prt_entry *entry;
	int gsi;
	u8 pin;
	int triggering = ACPI_LEVEL_SENSITIVE;
	/*
	 * On ARM systems with the GIC interrupt model, level interrupts
	 * are always polarity high by specification; PCI legacy
	 * IRQs lines are inverted before reaching the interrupt
	 * controller and must therefore be considered active high
	 * as default.
	 */
	int polarity = acpi_irq_model == ACPI_IRQ_MODEL_GIC ?
				      ACPI_ACTIVE_HIGH : ACPI_ACTIVE_LOW;
	char *link = NULL;
	char link_desc[16];
	int rc;

	pin = dev->pin;
	if (!pin) {
		ACPI_DEBUG_PRINT((ACPI_DB_INFO,
				  "No interrupt pin configured for device %s\n",
				  pci_name(dev)));
		return 0;
	}

	if (dev->irq_managed && dev->irq > 0)
		return 0;

	entry = acpi_pci_irq_lookup(dev, pin);
	if (!entry) {
		/*
		 * IDE legacy mode controller IRQs are magic. Why do compat
		 * extensions always make such a nasty mess.
		 */
		if (dev->class >> 8 == PCI_CLASS_STORAGE_IDE &&
				(dev->class & 0x05) == 0)
			return 0;
	}

	if (entry) {
		if (entry->link)
			gsi = acpi_pci_link_allocate_irq(entry->link,
							 entry->index,
							 &triggering, &polarity,
							 &link);
		else
			gsi = entry->index;
	} else
		gsi = -1;

	if (gsi < 0) {
		/*
		 * No IRQ known to the ACPI subsystem - maybe the BIOS /
		 * driver reported one, then use it. Exit in any case.
		 */
		if (!acpi_pci_irq_valid(dev, pin)) {
			kfree(entry);
			return 0;
		}

		if (acpi_isa_register_gsi(dev))
			dev_warn(&dev->dev, "PCI INT %c: no GSI\n",
				 pin_name(pin));

		kfree(entry);
		return 0;
	}

	rc = acpi_register_gsi(&dev->dev, gsi, triggering, polarity);
	if (rc < 0) {
		dev_warn(&dev->dev, "PCI INT %c: failed to register GSI\n",
			 pin_name(pin));
		kfree(entry);
		return rc;
	}
	dev->irq = rc;
	dev->irq_managed = 1;

	if (link)
		snprintf(link_desc, sizeof(link_desc), " -> Link[%s]", link);
	else
		link_desc[0] = '\0';

	dev_dbg(&dev->dev, "PCI INT %c%s -> GSI %u (%s, %s) -> IRQ %d\n",
		pin_name(pin), link_desc, gsi,
		(triggering == ACPI_LEVEL_SENSITIVE) ? "level" : "edge",
		(polarity == ACPI_ACTIVE_LOW) ? "low" : "high", dev->irq);

	kfree(entry);
	return 0;
}