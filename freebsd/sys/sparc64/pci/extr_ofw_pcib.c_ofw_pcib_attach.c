#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct ofw_pcib_gen_softc {TYPE_1__ ops_pcib_sc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCIB_SUBTRACTIVE ; 
 int /*<<< orphan*/  PCIR_PRIBUS_1 ; 
 int /*<<< orphan*/  PCIR_SECBUS_1 ; 
#define  PCI_DEVID_ALI_M5249 129 
#define  PCI_VENDOR_PLX 128 
 struct ofw_pcib_gen_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_pcib_gen_setup (int /*<<< orphan*/ ) ; 
 int pci_get_devid (int /*<<< orphan*/ ) ; 
 int pci_get_vendor (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int pcib_attach_child (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcib_attach_common (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ofw_pcib_attach(device_t dev)
{
	struct ofw_pcib_gen_softc *sc;

	sc = device_get_softc(dev);

	switch (pci_get_devid(dev)) {
	/*
	 * The ALi M5249 found in Fire-based machines by definition must me
	 * subtractive as they have a ISA bridge on their secondary side but
	 * don't indicate this in the class code although the ISA I/O range
	 * isn't included in their bridge decode.
	 */
	case PCI_DEVID_ALI_M5249:
		sc->ops_pcib_sc.flags |= PCIB_SUBTRACTIVE;
		break;
	}

	switch (pci_get_vendor(dev)) {
	/*
	 * Concurrently write the primary and secondary bus numbers in order
	 * to work around a bug in PLX PEX 8114 causing the internal shadow
	 * copies of these not to be updated when setting them bytewise.
	 */
	case PCI_VENDOR_PLX:
		pci_write_config(dev, PCIR_PRIBUS_1,
		    pci_read_config(dev, PCIR_SECBUS_1, 1) << 8 |
		    pci_read_config(dev, PCIR_PRIBUS_1, 1), 2);
		break;
	}

	ofw_pcib_gen_setup(dev);
	pcib_attach_common(dev);
	return (pcib_attach_child(dev));
}