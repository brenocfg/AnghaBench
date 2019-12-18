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
typedef  int u64 ;
typedef  int u16 ;
struct pci_dev {scalar_t__ msi_cap; } ;
struct msi_msg {int address_lo; int address_hi; scalar_t__ data; } ;
struct msi_desc {int dummy; } ;

/* Variables and functions */
 int CVMX_NPEI_PCIE_MSI_RCV ; 
 int CVMX_PCI_MSI_RCV ; 
 int CVMX_SLI_PCIE_MSI_RCV ; 
#define  OCTEON_DMA_BAR_TYPE_BIG 131 
#define  OCTEON_DMA_BAR_TYPE_PCIE 130 
#define  OCTEON_DMA_BAR_TYPE_PCIE2 129 
#define  OCTEON_DMA_BAR_TYPE_SMALL 128 
 scalar_t__ OCTEON_IRQ_MSI_BIT0 ; 
 scalar_t__ PCI_MSI_FLAGS ; 
 int PCI_MSI_FLAGS_QMASK ; 
 int PCI_MSI_FLAGS_QSIZE ; 
 int /*<<< orphan*/  irq_set_msi_desc (int,struct msi_desc*) ; 
 int* msi_free_irq_bitmask ; 
 int /*<<< orphan*/  msi_free_irq_bitmask_lock ; 
 int msi_irq_size ; 
 int* msi_multiple_irq_bitmask ; 
 int octeon_dma_bar_type ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  pci_write_msi_msg (int,struct msi_msg*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int arch_setup_msi_irq(struct pci_dev *dev, struct msi_desc *desc)
{
	struct msi_msg msg;
	u16 control;
	int configured_private_bits;
	int request_private_bits;
	int irq = 0;
	int irq_step;
	u64 search_mask;
	int index;

	/*
	 * Read the MSI config to figure out how many IRQs this device
	 * wants.  Most devices only want 1, which will give
	 * configured_private_bits and request_private_bits equal 0.
	 */
	pci_read_config_word(dev, dev->msi_cap + PCI_MSI_FLAGS, &control);

	/*
	 * If the number of private bits has been configured then use
	 * that value instead of the requested number. This gives the
	 * driver the chance to override the number of interrupts
	 * before calling pci_enable_msi().
	 */
	configured_private_bits = (control & PCI_MSI_FLAGS_QSIZE) >> 4;
	if (configured_private_bits == 0) {
		/* Nothing is configured, so use the hardware requested size */
		request_private_bits = (control & PCI_MSI_FLAGS_QMASK) >> 1;
	} else {
		/*
		 * Use the number of configured bits, assuming the
		 * driver wanted to override the hardware request
		 * value.
		 */
		request_private_bits = configured_private_bits;
	}

	/*
	 * The PCI 2.3 spec mandates that there are at most 32
	 * interrupts. If this device asks for more, only give it one.
	 */
	if (request_private_bits > 5)
		request_private_bits = 0;

try_only_one:
	/*
	 * The IRQs have to be aligned on a power of two based on the
	 * number being requested.
	 */
	irq_step = 1 << request_private_bits;

	/* Mask with one bit for each IRQ */
	search_mask = (1 << irq_step) - 1;

	/*
	 * We're going to search msi_free_irq_bitmask_lock for zero
	 * bits. This represents an MSI interrupt number that isn't in
	 * use.
	 */
	spin_lock(&msi_free_irq_bitmask_lock);
	for (index = 0; index < msi_irq_size/64; index++) {
		for (irq = 0; irq < 64; irq += irq_step) {
			if ((msi_free_irq_bitmask[index] & (search_mask << irq)) == 0) {
				msi_free_irq_bitmask[index] |= search_mask << irq;
				msi_multiple_irq_bitmask[index] |= (search_mask >> 1) << irq;
				goto msi_irq_allocated;
			}
		}
	}
msi_irq_allocated:
	spin_unlock(&msi_free_irq_bitmask_lock);

	/* Make sure the search for available interrupts didn't fail */
	if (irq >= 64) {
		if (request_private_bits) {
			pr_err("arch_setup_msi_irq: Unable to find %d free interrupts, trying just one",
			       1 << request_private_bits);
			request_private_bits = 0;
			goto try_only_one;
		} else
			panic("arch_setup_msi_irq: Unable to find a free MSI interrupt");
	}

	/* MSI interrupts start at logical IRQ OCTEON_IRQ_MSI_BIT0 */
	irq += index*64;
	irq += OCTEON_IRQ_MSI_BIT0;

	switch (octeon_dma_bar_type) {
	case OCTEON_DMA_BAR_TYPE_SMALL:
		/* When not using big bar, Bar 0 is based at 128MB */
		msg.address_lo =
			((128ul << 20) + CVMX_PCI_MSI_RCV) & 0xffffffff;
		msg.address_hi = ((128ul << 20) + CVMX_PCI_MSI_RCV) >> 32;
		break;
	case OCTEON_DMA_BAR_TYPE_BIG:
		/* When using big bar, Bar 0 is based at 0 */
		msg.address_lo = (0 + CVMX_PCI_MSI_RCV) & 0xffffffff;
		msg.address_hi = (0 + CVMX_PCI_MSI_RCV) >> 32;
		break;
	case OCTEON_DMA_BAR_TYPE_PCIE:
		/* When using PCIe, Bar 0 is based at 0 */
		/* FIXME CVMX_NPEI_MSI_RCV* other than 0? */
		msg.address_lo = (0 + CVMX_NPEI_PCIE_MSI_RCV) & 0xffffffff;
		msg.address_hi = (0 + CVMX_NPEI_PCIE_MSI_RCV) >> 32;
		break;
	case OCTEON_DMA_BAR_TYPE_PCIE2:
		/* When using PCIe2, Bar 0 is based at 0 */
		msg.address_lo = (0 + CVMX_SLI_PCIE_MSI_RCV) & 0xffffffff;
		msg.address_hi = (0 + CVMX_SLI_PCIE_MSI_RCV) >> 32;
		break;
	default:
		panic("arch_setup_msi_irq: Invalid octeon_dma_bar_type");
	}
	msg.data = irq - OCTEON_IRQ_MSI_BIT0;

	/* Update the number of IRQs the device has available to it */
	control &= ~PCI_MSI_FLAGS_QSIZE;
	control |= request_private_bits << 4;
	pci_write_config_word(dev, dev->msi_cap + PCI_MSI_FLAGS, control);

	irq_set_msi_desc(irq, desc);
	pci_write_msi_msg(irq, &msg);
	return 0;
}