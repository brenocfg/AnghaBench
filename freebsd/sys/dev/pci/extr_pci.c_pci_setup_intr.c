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
typedef  void* uint64_t ;
typedef  void* uint32_t ;
struct resource {int dummy; } ;
struct TYPE_5__ {scalar_t__ msix_alloc; int msix_table_len; struct msix_vector* msix_vectors; struct msix_table_entry* msix_table; } ;
struct TYPE_4__ {scalar_t__ msi_alloc; scalar_t__ msi_addr; scalar_t__ msi_handlers; void* msi_data; } ;
struct TYPE_6__ {TYPE_2__ msix; TYPE_1__ msi; } ;
struct pci_devinfo {TYPE_3__ cfg; } ;
struct msix_vector {scalar_t__ mv_irq; scalar_t__ mv_address; void* mv_data; } ;
struct msix_table_entry {int mte_vector; int mte_handlers; } ;
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  int /*<<< orphan*/  driver_filter_t ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PCIB_MAP_MSI (scalar_t__,scalar_t__,scalar_t__,void**,void**) ; 
 int /*<<< orphan*/  PCIM_CMD_INTxDIS ; 
 int /*<<< orphan*/  PCI_QUIRK_MSI_INTX_BUG ; 
 int bus_generic_setup_intr (scalar_t__,scalar_t__,struct resource*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,void**) ; 
 int /*<<< orphan*/  bus_generic_teardown_intr (scalar_t__,scalar_t__,struct resource*,void*) ; 
 struct pci_devinfo* device_get_ivars (scalar_t__) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 
 int /*<<< orphan*/  pci_clear_command_bit (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_enable_msi (scalar_t__,scalar_t__,void*) ; 
 int /*<<< orphan*/  pci_enable_msix (scalar_t__,int,scalar_t__,void*) ; 
 int /*<<< orphan*/  pci_get_devid (scalar_t__) ; 
 int /*<<< orphan*/  pci_has_quirk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_command_bit (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmask_msix (scalar_t__,int) ; 
 int rman_get_rid (struct resource*) ; 
 scalar_t__ rman_get_start (struct resource*) ; 

int
pci_setup_intr(device_t dev, device_t child, struct resource *irq, int flags,
    driver_filter_t *filter, driver_intr_t *intr, void *arg, void **cookiep)
{
	struct pci_devinfo *dinfo;
	struct msix_table_entry *mte;
	struct msix_vector *mv;
	uint64_t addr;
	uint32_t data;
	void *cookie;
	int error, rid;

	error = bus_generic_setup_intr(dev, child, irq, flags, filter, intr,
	    arg, &cookie);
	if (error)
		return (error);

	/* If this is not a direct child, just bail out. */
	if (device_get_parent(child) != dev) {
		*cookiep = cookie;
		return(0);
	}

	rid = rman_get_rid(irq);
	if (rid == 0) {
		/* Make sure that INTx is enabled */
		pci_clear_command_bit(dev, child, PCIM_CMD_INTxDIS);
	} else {
		/*
		 * Check to see if the interrupt is MSI or MSI-X.
		 * Ask our parent to map the MSI and give
		 * us the address and data register values.
		 * If we fail for some reason, teardown the
		 * interrupt handler.
		 */
		dinfo = device_get_ivars(child);
		if (dinfo->cfg.msi.msi_alloc > 0) {
			if (dinfo->cfg.msi.msi_addr == 0) {
				KASSERT(dinfo->cfg.msi.msi_handlers == 0,
			    ("MSI has handlers, but vectors not mapped"));
				error = PCIB_MAP_MSI(device_get_parent(dev),
				    child, rman_get_start(irq), &addr, &data);
				if (error)
					goto bad;
				dinfo->cfg.msi.msi_addr = addr;
				dinfo->cfg.msi.msi_data = data;
			}
			if (dinfo->cfg.msi.msi_handlers == 0)
				pci_enable_msi(child, dinfo->cfg.msi.msi_addr,
				    dinfo->cfg.msi.msi_data);
			dinfo->cfg.msi.msi_handlers++;
		} else {
			KASSERT(dinfo->cfg.msix.msix_alloc > 0,
			    ("No MSI or MSI-X interrupts allocated"));
			KASSERT(rid <= dinfo->cfg.msix.msix_table_len,
			    ("MSI-X index too high"));
			mte = &dinfo->cfg.msix.msix_table[rid - 1];
			KASSERT(mte->mte_vector != 0, ("no message vector"));
			mv = &dinfo->cfg.msix.msix_vectors[mte->mte_vector - 1];
			KASSERT(mv->mv_irq == rman_get_start(irq),
			    ("IRQ mismatch"));
			if (mv->mv_address == 0) {
				KASSERT(mte->mte_handlers == 0,
		    ("MSI-X table entry has handlers, but vector not mapped"));
				error = PCIB_MAP_MSI(device_get_parent(dev),
				    child, rman_get_start(irq), &addr, &data);
				if (error)
					goto bad;
				mv->mv_address = addr;
				mv->mv_data = data;
			}

			/*
			 * The MSIX table entry must be made valid by
			 * incrementing the mte_handlers before
			 * calling pci_enable_msix() and
			 * pci_resume_msix(). Else the MSIX rewrite
			 * table quirk will not work as expected.
			 */
			mte->mte_handlers++;
			if (mte->mte_handlers == 1) {
				pci_enable_msix(child, rid - 1, mv->mv_address,
				    mv->mv_data);
				pci_unmask_msix(child, rid - 1);
			}
		}

		/*
		 * Make sure that INTx is disabled if we are using MSI/MSI-X,
		 * unless the device is affected by PCI_QUIRK_MSI_INTX_BUG,
		 * in which case we "enable" INTx so MSI/MSI-X actually works.
		 */
		if (!pci_has_quirk(pci_get_devid(child),
		    PCI_QUIRK_MSI_INTX_BUG))
			pci_set_command_bit(dev, child, PCIM_CMD_INTxDIS);
		else
			pci_clear_command_bit(dev, child, PCIM_CMD_INTxDIS);
	bad:
		if (error) {
			(void)bus_generic_teardown_intr(dev, child, irq,
			    cookie);
			return (error);
		}
	}
	*cookiep = cookie;
	return (0);
}