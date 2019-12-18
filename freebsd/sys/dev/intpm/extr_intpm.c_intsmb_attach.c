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
struct intsmb_softc {int cfg_irq9; int sb8xx; int io_rid; int poll; int /*<<< orphan*/ * io_res; int /*<<< orphan*/ * smbus; scalar_t__ isbusy; int /*<<< orphan*/  irq_hand; int /*<<< orphan*/ * irq_res; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
#define  AMDCZ_SMBUS_DEVID 133 
#define  AMDFCH_SMBUS_DEVID 132 
 int /*<<< orphan*/  AMDSB8_SMBUS_REVID ; 
#define  AMDSB_SMBUS_DEVID 131 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  PCIR_INTLINE ; 
 int PCI_BASE_ADDR_SMB ; 
 int /*<<< orphan*/  PCI_HST_CFG_SMB ; 
 int PCI_INTR_SMB_ENABLE ; 
#define  PCI_INTR_SMB_IRQ9 130 
#define  PCI_INTR_SMB_IRQ_PCI 129 
 int PCI_INTR_SMB_MASK ; 
#define  PCI_INTR_SMB_SMI 128 
 int /*<<< orphan*/  PCI_REVID_SMB ; 
 int /*<<< orphan*/  PIIX4_SMBSLVCNT ; 
 int /*<<< orphan*/  PIIX4_SMBSLVCNT_ALTEN ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  bus_set_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct intsmb_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_write_1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct intsmb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int device_probe_and_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intsmb_rawintr ; 
 int /*<<< orphan*/  intsmb_release_resources (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int pci_get_devid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_revid (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int sb8xx_attach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
intsmb_attach(device_t dev)
{
	struct intsmb_softc *sc = device_get_softc(dev);
	int error, rid, value;
	int intr;
	char *str;

	sc->dev = dev;

	mtx_init(&sc->lock, device_get_nameunit(dev), "intsmb", MTX_DEF);

	sc->cfg_irq9 = 0;
	switch (pci_get_devid(dev)) {
#ifndef NO_CHANGE_PCICONF
	case 0x71138086:	/* Intel 82371AB */
	case 0x719b8086:	/* Intel 82443MX */
		/* Changing configuration is allowed. */
		sc->cfg_irq9 = 1;
		break;
#endif
	case AMDSB_SMBUS_DEVID:
		if (pci_get_revid(dev) >= AMDSB8_SMBUS_REVID)
			sc->sb8xx = 1;
		break;
	case AMDFCH_SMBUS_DEVID:
	case AMDCZ_SMBUS_DEVID:
		sc->sb8xx = 1;
		break;
	}

	if (sc->sb8xx) {
		error = sb8xx_attach(dev);
		if (error != 0)
			goto fail;
		else
			goto no_intr;
	}

	sc->io_rid = PCI_BASE_ADDR_SMB;
	sc->io_res = bus_alloc_resource_any(dev, SYS_RES_IOPORT, &sc->io_rid,
	    RF_ACTIVE);
	if (sc->io_res == NULL) {
		device_printf(dev, "Could not allocate I/O space\n");
		error = ENXIO;
		goto fail;
	}

	if (sc->cfg_irq9) {
		pci_write_config(dev, PCIR_INTLINE, 0x9, 1);
		pci_write_config(dev, PCI_HST_CFG_SMB,
		    PCI_INTR_SMB_IRQ9 | PCI_INTR_SMB_ENABLE, 1);
	}
	value = pci_read_config(dev, PCI_HST_CFG_SMB, 1);
	sc->poll = (value & PCI_INTR_SMB_ENABLE) == 0;
	intr = value & PCI_INTR_SMB_MASK;
	switch (intr) {
	case PCI_INTR_SMB_SMI:
		str = "SMI";
		break;
	case PCI_INTR_SMB_IRQ9:
		str = "IRQ 9";
		break;
	case PCI_INTR_SMB_IRQ_PCI:
		str = "PCI IRQ";
		break;
	default:
		str = "BOGUS";
	}

	device_printf(dev, "intr %s %s ", str,
	    sc->poll == 0 ? "enabled" : "disabled");
	printf("revision %d\n", pci_read_config(dev, PCI_REVID_SMB, 1));

	if (!sc->poll && intr == PCI_INTR_SMB_SMI) {
		device_printf(dev,
		    "using polling mode when configured interrupt is SMI\n");
		sc->poll = 1;
	}

	if (sc->poll)
	    goto no_intr;

	if (intr != PCI_INTR_SMB_IRQ9 && intr != PCI_INTR_SMB_IRQ_PCI) {
		device_printf(dev, "Unsupported interrupt mode\n");
		error = ENXIO;
		goto fail;
	}

	/* Force IRQ 9. */
	rid = 0;
	if (sc->cfg_irq9)
		bus_set_resource(dev, SYS_RES_IRQ, rid, 9, 1);

	sc->irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
	    RF_SHAREABLE | RF_ACTIVE);
	if (sc->irq_res == NULL) {
		device_printf(dev, "Could not allocate irq\n");
		error = ENXIO;
		goto fail;
	}

	error = bus_setup_intr(dev, sc->irq_res, INTR_TYPE_MISC | INTR_MPSAFE,
	    NULL, intsmb_rawintr, sc, &sc->irq_hand);
	if (error) {
		device_printf(dev, "Failed to map intr\n");
		goto fail;
	}

no_intr:
	sc->isbusy = 0;
	sc->smbus = device_add_child(dev, "smbus", -1);
	if (sc->smbus == NULL) {
		device_printf(dev, "failed to add smbus child\n");
		error = ENXIO;
		goto fail;
	}
	error = device_probe_and_attach(sc->smbus);
	if (error) {
		device_printf(dev, "failed to probe+attach smbus child\n");
		goto fail;
	}

#ifdef ENABLE_ALART
	/* Enable Arart */
	bus_write_1(sc->io_res, PIIX4_SMBSLVCNT, PIIX4_SMBSLVCNT_ALTEN);
#endif
	return (0);

fail:
	intsmb_release_resources(dev);
	return (error);
}