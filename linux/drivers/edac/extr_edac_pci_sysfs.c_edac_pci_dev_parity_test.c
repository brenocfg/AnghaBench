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
typedef  int u8 ;
typedef  int u16 ;
struct pci_dev {int /*<<< orphan*/  broken_parity_status; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDAC_PCI ; 
 int /*<<< orphan*/  KERN_CRIT ; 
 int /*<<< orphan*/  PCI_HEADER_TYPE ; 
 int PCI_HEADER_TYPE_BRIDGE ; 
 int PCI_STATUS_DETECTED_PARITY ; 
 int PCI_STATUS_PARITY ; 
 int PCI_STATUS_SIG_SYSTEM_ERROR ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  edac_dbg (int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int get_pci_parity_status (struct pci_dev*,int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_nonparity_count ; 
 int /*<<< orphan*/  pci_parity_count ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void edac_pci_dev_parity_test(struct pci_dev *dev)
{
	unsigned long flags;
	u16 status;
	u8 header_type;

	/* stop any interrupts until we can acquire the status */
	local_irq_save(flags);

	/* read the STATUS register on this device */
	status = get_pci_parity_status(dev, 0);

	/* read the device TYPE, looking for bridges */
	pci_read_config_byte(dev, PCI_HEADER_TYPE, &header_type);

	local_irq_restore(flags);

	edac_dbg(4, "PCI STATUS= 0x%04x %s\n", status, dev_name(&dev->dev));

	/* check the status reg for errors on boards NOT marked as broken
	 * if broken, we cannot trust any of the status bits
	 */
	if (status && !dev->broken_parity_status) {
		if (status & (PCI_STATUS_SIG_SYSTEM_ERROR)) {
			edac_printk(KERN_CRIT, EDAC_PCI,
				"Signaled System Error on %s\n",
				pci_name(dev));
			atomic_inc(&pci_nonparity_count);
		}

		if (status & (PCI_STATUS_PARITY)) {
			edac_printk(KERN_CRIT, EDAC_PCI,
				"Master Data Parity Error on %s\n",
				pci_name(dev));

			atomic_inc(&pci_parity_count);
		}

		if (status & (PCI_STATUS_DETECTED_PARITY)) {
			edac_printk(KERN_CRIT, EDAC_PCI,
				"Detected Parity Error on %s\n",
				pci_name(dev));

			atomic_inc(&pci_parity_count);
		}
	}


	edac_dbg(4, "PCI HEADER TYPE= 0x%02x %s\n",
		 header_type, dev_name(&dev->dev));

	if ((header_type & 0x7F) == PCI_HEADER_TYPE_BRIDGE) {
		/* On bridges, need to examine secondary status register  */
		status = get_pci_parity_status(dev, 1);

		edac_dbg(4, "PCI SEC_STATUS= 0x%04x %s\n",
			 status, dev_name(&dev->dev));

		/* check the secondary status reg for errors,
		 * on NOT broken boards
		 */
		if (status && !dev->broken_parity_status) {
			if (status & (PCI_STATUS_SIG_SYSTEM_ERROR)) {
				edac_printk(KERN_CRIT, EDAC_PCI, "Bridge "
					"Signaled System Error on %s\n",
					pci_name(dev));
				atomic_inc(&pci_nonparity_count);
			}

			if (status & (PCI_STATUS_PARITY)) {
				edac_printk(KERN_CRIT, EDAC_PCI, "Bridge "
					"Master Data Parity Error on "
					"%s\n", pci_name(dev));

				atomic_inc(&pci_parity_count);
			}

			if (status & (PCI_STATUS_DETECTED_PARITY)) {
				edac_printk(KERN_CRIT, EDAC_PCI, "Bridge "
					"Detected Parity Error on %s\n",
					pci_name(dev));

				atomic_inc(&pci_parity_count);
			}
		}
	}
}