#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct resource_list_entry {int start; int /*<<< orphan*/ * res; } ;
struct TYPE_9__ {int msix_alloc; scalar_t__ msix_location; int msix_table_bar; scalar_t__ msix_pba_bar; int msix_msgnum; int msix_table_len; int /*<<< orphan*/  msix_ctrl; TYPE_3__* msix_table; TYPE_2__* msix_vectors; int /*<<< orphan*/ * msix_pba_res; int /*<<< orphan*/ * msix_table_res; } ;
struct TYPE_6__ {scalar_t__ msi_alloc; } ;
struct TYPE_10__ {TYPE_4__ msix; TYPE_1__ msi; } ;
struct pci_devinfo {int /*<<< orphan*/  resources; TYPE_5__ cfg; } ;
struct msix_vector {int dummy; } ;
struct msix_table_entry {int dummy; } ;
typedef  TYPE_5__ pcicfgregs ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_8__ {int mte_vector; } ;
struct TYPE_7__ {int mv_irq; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENXIO ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int PCIB_ALLOC_MSIX (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  PCIM_MSIXCTRL_MSIX_ENABLE ; 
 scalar_t__ PCIR_MSIX_CTRL ; 
 int RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ bootverbose ; 
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  pci_do_msix ; 
 int /*<<< orphan*/  pci_mask_msix (int /*<<< orphan*/ ,int) ; 
 scalar_t__ pci_msix_blacklisted () ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  resource_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 
 struct resource_list_entry* resource_list_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int rman_get_flags (int /*<<< orphan*/ *) ; 

int
pci_alloc_msix_method(device_t dev, device_t child, int *count)
{
	struct pci_devinfo *dinfo = device_get_ivars(child);
	pcicfgregs *cfg = &dinfo->cfg;
	struct resource_list_entry *rle;
	int actual, error, i, irq, max;

	/* Don't let count == 0 get us into trouble. */
	if (*count == 0)
		return (EINVAL);

	/* If rid 0 is allocated, then fail. */
	rle = resource_list_find(&dinfo->resources, SYS_RES_IRQ, 0);
	if (rle != NULL && rle->res != NULL)
		return (ENXIO);

	/* Already have allocated messages? */
	if (cfg->msi.msi_alloc != 0 || cfg->msix.msix_alloc != 0)
		return (ENXIO);

	/* If MSI-X is blacklisted for this system, fail. */
	if (pci_msix_blacklisted())
		return (ENXIO);

	/* MSI-X capability present? */
	if (cfg->msix.msix_location == 0 || !pci_do_msix)
		return (ENODEV);

	/* Make sure the appropriate BARs are mapped. */
	rle = resource_list_find(&dinfo->resources, SYS_RES_MEMORY,
	    cfg->msix.msix_table_bar);
	if (rle == NULL || rle->res == NULL ||
	    !(rman_get_flags(rle->res) & RF_ACTIVE))
		return (ENXIO);
	cfg->msix.msix_table_res = rle->res;
	if (cfg->msix.msix_pba_bar != cfg->msix.msix_table_bar) {
		rle = resource_list_find(&dinfo->resources, SYS_RES_MEMORY,
		    cfg->msix.msix_pba_bar);
		if (rle == NULL || rle->res == NULL ||
		    !(rman_get_flags(rle->res) & RF_ACTIVE))
			return (ENXIO);
	}
	cfg->msix.msix_pba_res = rle->res;

	if (bootverbose)
		device_printf(child,
		    "attempting to allocate %d MSI-X vectors (%d supported)\n",
		    *count, cfg->msix.msix_msgnum);
	max = min(*count, cfg->msix.msix_msgnum);
	for (i = 0; i < max; i++) {
		/* Allocate a message. */
		error = PCIB_ALLOC_MSIX(device_get_parent(dev), child, &irq);
		if (error) {
			if (i == 0)
				return (error);
			break;
		}
		resource_list_add(&dinfo->resources, SYS_RES_IRQ, i + 1, irq,
		    irq, 1);
	}
	actual = i;

	if (bootverbose) {
		rle = resource_list_find(&dinfo->resources, SYS_RES_IRQ, 1);
		if (actual == 1)
			device_printf(child, "using IRQ %ju for MSI-X\n",
			    rle->start);
		else {
			int run;

			/*
			 * Be fancy and try to print contiguous runs of
			 * IRQ values as ranges.  'irq' is the previous IRQ.
			 * 'run' is true if we are in a range.
			 */
			device_printf(child, "using IRQs %ju", rle->start);
			irq = rle->start;
			run = 0;
			for (i = 1; i < actual; i++) {
				rle = resource_list_find(&dinfo->resources,
				    SYS_RES_IRQ, i + 1);

				/* Still in a run? */
				if (rle->start == irq + 1) {
					run = 1;
					irq++;
					continue;
				}

				/* Finish previous range. */
				if (run) {
					printf("-%d", irq);
					run = 0;
				}

				/* Start new range. */
				printf(",%ju", rle->start);
				irq = rle->start;
			}

			/* Unfinished range? */
			if (run)
				printf("-%d", irq);
			printf(" for MSI-X\n");
		}
	}

	/* Mask all vectors. */
	for (i = 0; i < cfg->msix.msix_msgnum; i++)
		pci_mask_msix(child, i);

	/* Allocate and initialize vector data and virtual table. */
	cfg->msix.msix_vectors = malloc(sizeof(struct msix_vector) * actual,
	    M_DEVBUF, M_WAITOK | M_ZERO);
	cfg->msix.msix_table = malloc(sizeof(struct msix_table_entry) * actual,
	    M_DEVBUF, M_WAITOK | M_ZERO);
	for (i = 0; i < actual; i++) {
		rle = resource_list_find(&dinfo->resources, SYS_RES_IRQ, i + 1);
		cfg->msix.msix_vectors[i].mv_irq = rle->start;
		cfg->msix.msix_table[i].mte_vector = i + 1;
	}

	/* Update control register to enable MSI-X. */
	cfg->msix.msix_ctrl |= PCIM_MSIXCTRL_MSIX_ENABLE;
	pci_write_config(child, cfg->msix.msix_location + PCIR_MSIX_CTRL,
	    cfg->msix.msix_ctrl, 2);

	/* Update counts of alloc'd messages. */
	cfg->msix.msix_alloc = actual;
	cfg->msix.msix_table_len = actual;
	*count = actual;
	return (0);
}