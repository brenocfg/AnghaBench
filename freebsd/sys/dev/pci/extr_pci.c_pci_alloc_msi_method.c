#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct resource_list_entry {int /*<<< orphan*/ * res; } ;
struct TYPE_5__ {int msi_alloc; scalar_t__ msi_location; int msi_msgnum; int msi_ctrl; scalar_t__ msi_handlers; } ;
struct TYPE_4__ {scalar_t__ msix_alloc; } ;
struct TYPE_6__ {TYPE_2__ msi; TYPE_1__ msix; } ;
struct pci_devinfo {int /*<<< orphan*/  resources; TYPE_3__ cfg; } ;
typedef  TYPE_3__ pcicfgregs ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENXIO ; 
 int PCIB_ALLOC_MSI (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int*) ; 
 int PCIM_MSICTRL_MME_MASK ; 
 scalar_t__ PCIR_MSI_CTRL ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 scalar_t__ bootverbose ; 
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 int ffs (int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  pci_do_msi ; 
 scalar_t__ pci_msi_blacklisted () ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  powerof2 (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  resource_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 
 struct resource_list_entry* resource_list_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
pci_alloc_msi_method(device_t dev, device_t child, int *count)
{
	struct pci_devinfo *dinfo = device_get_ivars(child);
	pcicfgregs *cfg = &dinfo->cfg;
	struct resource_list_entry *rle;
	int actual, error, i, irqs[32];
	uint16_t ctrl;

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

	/* If MSI is blacklisted for this system, fail. */
	if (pci_msi_blacklisted())
		return (ENXIO);

	/* MSI capability present? */
	if (cfg->msi.msi_location == 0 || !pci_do_msi)
		return (ENODEV);

	if (bootverbose)
		device_printf(child,
		    "attempting to allocate %d MSI vectors (%d supported)\n",
		    *count, cfg->msi.msi_msgnum);

	/* Don't ask for more than the device supports. */
	actual = min(*count, cfg->msi.msi_msgnum);

	/* Don't ask for more than 32 messages. */
	actual = min(actual, 32);

	/* MSI requires power of 2 number of messages. */
	if (!powerof2(actual))
		return (EINVAL);

	for (;;) {
		/* Try to allocate N messages. */
		error = PCIB_ALLOC_MSI(device_get_parent(dev), child, actual,
		    actual, irqs);
		if (error == 0)
			break;
		if (actual == 1)
			return (error);

		/* Try N / 2. */
		actual >>= 1;
	}

	/*
	 * We now have N actual messages mapped onto SYS_RES_IRQ
	 * resources in the irqs[] array, so add new resources
	 * starting at rid 1.
	 */
	for (i = 0; i < actual; i++)
		resource_list_add(&dinfo->resources, SYS_RES_IRQ, i + 1,
		    irqs[i], irqs[i], 1);

	if (bootverbose) {
		if (actual == 1)
			device_printf(child, "using IRQ %d for MSI\n", irqs[0]);
		else {
			int run;

			/*
			 * Be fancy and try to print contiguous runs
			 * of IRQ values as ranges.  'run' is true if
			 * we are in a range.
			 */
			device_printf(child, "using IRQs %d", irqs[0]);
			run = 0;
			for (i = 1; i < actual; i++) {

				/* Still in a run? */
				if (irqs[i] == irqs[i - 1] + 1) {
					run = 1;
					continue;
				}

				/* Finish previous range. */
				if (run) {
					printf("-%d", irqs[i - 1]);
					run = 0;
				}

				/* Start new range. */
				printf(",%d", irqs[i]);
			}

			/* Unfinished range? */
			if (run)
				printf("-%d", irqs[actual - 1]);
			printf(" for MSI\n");
		}
	}

	/* Update control register with actual count. */
	ctrl = cfg->msi.msi_ctrl;
	ctrl &= ~PCIM_MSICTRL_MME_MASK;
	ctrl |= (ffs(actual) - 1) << 4;
	cfg->msi.msi_ctrl = ctrl;
	pci_write_config(child, cfg->msi.msi_location + PCIR_MSI_CTRL, ctrl, 2);

	/* Update counts of alloc'd messages. */
	cfg->msi.msi_alloc = actual;
	cfg->msi.msi_handlers = 0;
	*count = actual;
	return (0);
}