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
struct ipmi_softc {int ipmi_io_type; int ipmi_io_spacing; scalar_t__ ipmi_irq_rid; void* ipmi_irq_res; int /*<<< orphan*/ ** ipmi_io_res; scalar_t__ ipmi_io_rid; int /*<<< orphan*/  ipmi_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BT_MODE ; 
 int ENXIO ; 
#define  KCS_MODE 132 
#define  PCIP_SERIALBUS_IPMI_BT 131 
#define  PCIP_SERIALBUS_IPMI_KCS 130 
#define  PCIP_SERIALBUS_IPMI_SMIC 129 
 scalar_t__ PCIR_BAR (int /*<<< orphan*/ ) ; 
 scalar_t__ PCI_BAR_IO (int /*<<< orphan*/ ) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
#define  SMIC_MODE 128 
 int SYS_RES_IOPORT ; 
 int SYS_RES_IRQ ; 
 int SYS_RES_MEMORY ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int,scalar_t__*,int) ; 
 struct ipmi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int ipmi_attach (int /*<<< orphan*/ ) ; 
 int ipmi_kcs_attach (struct ipmi_softc*) ; 
 int /*<<< orphan*/  ipmi_kcs_probe_align (struct ipmi_softc*) ; 
 int /*<<< orphan*/  ipmi_release_resources (int /*<<< orphan*/ ) ; 
 int ipmi_smic_attach (struct ipmi_softc*) ; 
 int pci_get_progif (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int
ipmi2_pci_attach(device_t dev)
{
	struct ipmi_softc *sc;
	int error, iface, type;

	sc = device_get_softc(dev);
	sc->ipmi_dev = dev;

	/* Interface is determined by progif. */
	switch (pci_get_progif(dev)) {
	case PCIP_SERIALBUS_IPMI_SMIC:
		iface = SMIC_MODE;
		break;
	case PCIP_SERIALBUS_IPMI_KCS:
		iface = KCS_MODE;
		break;
	case PCIP_SERIALBUS_IPMI_BT:
		iface = BT_MODE;
		device_printf(dev, "BT interface unsupported\n");
		return (ENXIO);
	default:
		device_printf(dev, "Unsupported interface: %d\n",
		    pci_get_progif(dev));
		return (ENXIO);
	}

	/* Check the BAR to determine our resource type. */
	sc->ipmi_io_rid = PCIR_BAR(0);
	if (PCI_BAR_IO(pci_read_config(dev, PCIR_BAR(0), 4)))
		type = SYS_RES_IOPORT;
	else
		type = SYS_RES_MEMORY;
	sc->ipmi_io_type = type;
	sc->ipmi_io_spacing = 1;
	sc->ipmi_io_res[0] = bus_alloc_resource_any(dev, type,
	    &sc->ipmi_io_rid, RF_ACTIVE);
	if (sc->ipmi_io_res[0] == NULL) {
		device_printf(dev, "couldn't map ports/memory\n");
		return (ENXIO);
	}

	sc->ipmi_irq_rid = 0;
	sc->ipmi_irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ,
	    &sc->ipmi_irq_rid, RF_SHAREABLE | RF_ACTIVE);

	switch (iface) {
	case KCS_MODE:
		device_printf(dev, "using KSC interface\n");

		/*
		 * We have to examine the resource directly to determine the
		 * alignment.
		 */
		if (!ipmi_kcs_probe_align(sc)) {
			device_printf(dev, "Unable to determine alignment\n");
			error = ENXIO;
			goto bad;
		}

		error = ipmi_kcs_attach(sc);
		if (error)
			goto bad;
		break;
	case SMIC_MODE:
		device_printf(dev, "using SMIC interface\n");

		error = ipmi_smic_attach(sc);
		if (error)
			goto bad;
		break;
	}
	error = ipmi_attach(dev);
	if (error)
		goto bad;

	return (0);
bad:
	ipmi_release_resources(dev);
	return (error);
}