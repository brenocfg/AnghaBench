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
struct pci_dev {int irq_managed; int irq; int /*<<< orphan*/  dev; int /*<<< orphan*/  device; } ;
struct irq_alloc_info {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
#define  INTEL_MID_CPU_CHIP_TANGIER 128 
 int /*<<< orphan*/  IOAPIC_MAP_ALLOC ; 
 int IOAPIC_POL_HIGH ; 
 int IOAPIC_POL_LOW ; 
 int /*<<< orphan*/  PCI_DEVICE_ID_INTEL_MRFLD_HSU ; 
 int /*<<< orphan*/  PCI_DEVICE_ID_INTEL_MRFLD_MMC ; 
 int /*<<< orphan*/  PCI_INTERRUPT_LINE ; 
 int /*<<< orphan*/  dev_to_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int intel_mid_identify_cpu () ; 
 int /*<<< orphan*/  ioapic_set_alloc_attr (struct irq_alloc_info*,int /*<<< orphan*/ ,int,int) ; 
 int mp_map_gsi_to_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct irq_alloc_info*) ; 
 int pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int intel_mid_pci_irq_enable(struct pci_dev *dev)
{
	struct irq_alloc_info info;
	int polarity;
	int ret;
	u8 gsi;

	if (dev->irq_managed && dev->irq > 0)
		return 0;

	ret = pci_read_config_byte(dev, PCI_INTERRUPT_LINE, &gsi);
	if (ret < 0) {
		dev_warn(&dev->dev, "Failed to read interrupt line: %d\n", ret);
		return ret;
	}

	switch (intel_mid_identify_cpu()) {
	case INTEL_MID_CPU_CHIP_TANGIER:
		polarity = IOAPIC_POL_HIGH;

		/* Special treatment for IRQ0 */
		if (gsi == 0) {
			/*
			 * Skip HS UART common registers device since it has
			 * IRQ0 assigned and not used by the kernel.
			 */
			if (dev->device == PCI_DEVICE_ID_INTEL_MRFLD_HSU)
				return -EBUSY;
			/*
			 * TNG has IRQ0 assigned to eMMC controller. But there
			 * are also other devices with bogus PCI configuration
			 * that have IRQ0 assigned. This check ensures that
			 * eMMC gets it. The rest of devices still could be
			 * enabled without interrupt line being allocated.
			 */
			if (dev->device != PCI_DEVICE_ID_INTEL_MRFLD_MMC)
				return 0;
		}
		break;
	default:
		polarity = IOAPIC_POL_LOW;
		break;
	}

	ioapic_set_alloc_attr(&info, dev_to_node(&dev->dev), 1, polarity);

	/*
	 * MRST only have IOAPIC, the PCI irq lines are 1:1 mapped to
	 * IOAPIC RTE entries, so we just enable RTE for the device.
	 */
	ret = mp_map_gsi_to_irq(gsi, IOAPIC_MAP_ALLOC, &info);
	if (ret < 0)
		return ret;

	dev->irq = ret;
	dev->irq_managed = 1;

	return 0;
}