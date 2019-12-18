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
struct isci_softc {int /*<<< orphan*/  device; struct ISCI_PCI_BAR* pci_bar; } ;
struct ISCI_PCI_BAR {int /*<<< orphan*/ * resource; int /*<<< orphan*/  bus_handle; int /*<<< orphan*/  bus_tag; int /*<<< orphan*/  resource_id; } ;

/* Variables and functions */
 int ISCI_NUM_PCI_BARS ; 
 int /*<<< orphan*/  PCIR_BAR (int) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isci_log_message (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
isci_allocate_pci_memory(struct isci_softc *isci)
{
	int i;

	for (i = 0; i < ISCI_NUM_PCI_BARS; i++)
	{
		struct ISCI_PCI_BAR *pci_bar = &isci->pci_bar[i];

		pci_bar->resource_id = PCIR_BAR(i*2);
		pci_bar->resource = bus_alloc_resource_any(isci->device,
		    SYS_RES_MEMORY, &pci_bar->resource_id,
		    RF_ACTIVE);

		if(pci_bar->resource == NULL)
			isci_log_message(0, "ISCI",
			    "unable to allocate pci resource\n");
		else {
			pci_bar->bus_tag = rman_get_bustag(pci_bar->resource);
			pci_bar->bus_handle =
			    rman_get_bushandle(pci_bar->resource);
		}
	}

	return (0);
}