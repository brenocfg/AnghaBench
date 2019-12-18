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
typedef  int uint8_t ;
typedef  int uint16_t ;
struct pci_devinfo {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCIB_MAXSLOTS (int /*<<< orphan*/ ) ; 
 int PCIB_READ_CONFIG (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PCIB_WRITE_CONFIG (int /*<<< orphan*/ ,int,int,int,int,int,int) ; 
 int PCIM_HDRTYPE ; 
 int PCIM_MFDEV ; 
 int /*<<< orphan*/  PCIR_DEVICE ; 
 int /*<<< orphan*/  PCIR_HDRTYPE ; 
#define  PCI_DEVICE_ID_NLM_EHCI 135 
#define  PCI_DEVICE_ID_NLM_FMN 134 
#define  PCI_DEVICE_ID_NLM_I2C 133 
#define  PCI_DEVICE_ID_NLM_ICI 132 
#define  PCI_DEVICE_ID_NLM_MMC 131 
#define  PCI_DEVICE_ID_NLM_NOR 130 
#define  PCI_DEVICE_ID_NLM_PIC 129 
#define  PCI_DEVICE_ID_NLM_UART 128 
 int PCI_FUNCMAX ; 
 int PCI_MAXHDRTYPE ; 
 int PIC_USB_IRQ (int) ; 
 int XLP_HDR_OFFSET (int,int /*<<< orphan*/ ,int,int) ; 
 int XLP_PCI_DEVSCRATCH_REG0 ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_dev_exists (int) ; 
 int /*<<< orphan*/  pci_add_child (int /*<<< orphan*/ ,struct pci_devinfo*) ; 
 struct pci_devinfo* pci_read_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int pcib_get_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcib_get_domain (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xlp_pci_attach(device_t dev)
{
	struct pci_devinfo *dinfo;
	device_t pcib;
	int maxslots, s, f, pcifunchigh, irq;
	int busno, node, devoffset;
	uint16_t devid;
	uint8_t hdrtype;

	/*
	 * The on-chip devices are on a bus that is almost, but not
	 * quite, completely like PCI. Add those things by hand.
	 */
	pcib = device_get_parent(dev);
	busno = pcib_get_bus(dev);
	maxslots = PCIB_MAXSLOTS(pcib);
	for (s = 0; s <= maxslots; s++) {
		pcifunchigh = 0;
		f = 0;
		hdrtype = PCIB_READ_CONFIG(pcib, busno, s, f, PCIR_HDRTYPE, 1);
		if ((hdrtype & PCIM_HDRTYPE) > PCI_MAXHDRTYPE)
			continue;
		if (hdrtype & PCIM_MFDEV)
			pcifunchigh = PCI_FUNCMAX;
		node = s / 8;
		for (f = 0; f <= pcifunchigh; f++) {
			devoffset = XLP_HDR_OFFSET(node, 0, s % 8, f);
			if (!nlm_dev_exists(devoffset))
				continue;

			/* Find if there is a desc for the SoC device */
			devid = PCIB_READ_CONFIG(pcib, busno, s, f, PCIR_DEVICE, 2);

			/* Skip devices that don't have a proper PCI header */
			switch (devid) {
			case PCI_DEVICE_ID_NLM_ICI:
			case PCI_DEVICE_ID_NLM_PIC:
			case PCI_DEVICE_ID_NLM_FMN:
			case PCI_DEVICE_ID_NLM_UART:
			case PCI_DEVICE_ID_NLM_I2C:
			case PCI_DEVICE_ID_NLM_NOR:
			case PCI_DEVICE_ID_NLM_MMC:
				continue;
			case PCI_DEVICE_ID_NLM_EHCI:
				irq = PIC_USB_IRQ(f);
				PCIB_WRITE_CONFIG(pcib, busno, s, f,
				    XLP_PCI_DEVSCRATCH_REG0 << 2,
				    (1 << 8) | irq, 4);
			}
			dinfo = pci_read_device(pcib, dev, pcib_get_domain(dev),
			    busno, s, f);
			pci_add_child(dev, dinfo);
		}
	}
	return (bus_generic_attach(dev));
}