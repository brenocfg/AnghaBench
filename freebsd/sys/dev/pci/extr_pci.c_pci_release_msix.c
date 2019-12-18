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
struct resource_list_entry {int /*<<< orphan*/ * res; } ;
struct pcicfg_msix {int msix_alloc; int msix_table_len; TYPE_2__* msix_vectors; TYPE_2__* msix_table; int /*<<< orphan*/  msix_ctrl; scalar_t__ msix_location; } ;
struct TYPE_3__ {struct pcicfg_msix msix; } ;
struct pci_devinfo {int /*<<< orphan*/  resources; TYPE_1__ cfg; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {scalar_t__ mte_vector; scalar_t__ mte_handlers; int /*<<< orphan*/  mv_irq; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  PCIB_RELEASE_MSIX (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCIM_MSIXCTRL_MSIX_ENABLE ; 
 scalar_t__ PCIR_MSIX_CTRL ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  resource_list_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct resource_list_entry* resource_list_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
pci_release_msix(device_t dev, device_t child)
{
	struct pci_devinfo *dinfo = device_get_ivars(child);
	struct pcicfg_msix *msix = &dinfo->cfg.msix;
	struct resource_list_entry *rle;
	int i;

	/* Do we have any messages to release? */
	if (msix->msix_alloc == 0)
		return (ENODEV);

	/* Make sure none of the resources are allocated. */
	for (i = 0; i < msix->msix_table_len; i++) {
		if (msix->msix_table[i].mte_vector == 0)
			continue;
		if (msix->msix_table[i].mte_handlers > 0)
			return (EBUSY);
		rle = resource_list_find(&dinfo->resources, SYS_RES_IRQ, i + 1);
		KASSERT(rle != NULL, ("missing resource"));
		if (rle->res != NULL)
			return (EBUSY);
	}

	/* Update control register to disable MSI-X. */
	msix->msix_ctrl &= ~PCIM_MSIXCTRL_MSIX_ENABLE;
	pci_write_config(child, msix->msix_location + PCIR_MSIX_CTRL,
	    msix->msix_ctrl, 2);

	/* Free the resource list entries. */
	for (i = 0; i < msix->msix_table_len; i++) {
		if (msix->msix_table[i].mte_vector == 0)
			continue;
		resource_list_delete(&dinfo->resources, SYS_RES_IRQ, i + 1);
	}
	free(msix->msix_table, M_DEVBUF);
	msix->msix_table_len = 0;

	/* Release the IRQs. */
	for (i = 0; i < msix->msix_alloc; i++)
		PCIB_RELEASE_MSIX(device_get_parent(dev), child,
		    msix->msix_vectors[i].mv_irq);
	free(msix->msix_vectors, M_DEVBUF);
	msix->msix_alloc = 0;
	return (0);
}