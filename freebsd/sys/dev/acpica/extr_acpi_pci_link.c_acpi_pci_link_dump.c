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
struct link {int l_irq; int l_references; int l_num_irqs; int* l_irqs; scalar_t__ l_routed; } ;
struct acpi_pci_link_softc {int pl_num_links; struct link* pl_links; int /*<<< orphan*/  pl_dev; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SERIAL_ASSERT (int /*<<< orphan*/ ) ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_link ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static void
acpi_pci_link_dump(struct acpi_pci_link_softc *sc, int header, const char *tag)
{
	struct link *link;
	char buf[16];
	int i, j;

	ACPI_SERIAL_ASSERT(pci_link);
	if (header) {
		snprintf(buf, sizeof(buf), "%s:",
		    device_get_nameunit(sc->pl_dev));
		printf("%-16.16s  Index  IRQ  Rtd  Ref  IRQs\n", buf);
	}
	for (i = 0; i < sc->pl_num_links; i++) {
		link = &sc->pl_links[i];
		printf("  %-14.14s  %5d  %3d   %c   %3d ", i == 0 ? tag : "", i,
		    link->l_irq, link->l_routed ? 'Y' : 'N',
		    link->l_references);
		if (link->l_num_irqs == 0)
			printf(" none");
		else for (j = 0; j < link->l_num_irqs; j++)
			printf(" %d", link->l_irqs[j]);
		printf("\n");
	}
}