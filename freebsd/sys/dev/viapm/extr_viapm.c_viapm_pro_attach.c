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
typedef  int u_int32_t ;
struct viapm_softc {int /*<<< orphan*/  lock; scalar_t__ irqres; scalar_t__ irqrid; scalar_t__ iores; scalar_t__ iorid; int /*<<< orphan*/  smbus; int /*<<< orphan*/  irqih; } ;
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  MTX_DEF ; 
 scalar_t__ PCIC_BRIDGE ; 
 scalar_t__ PCIS_BRIDGE_ISA ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SMBHCTRL ; 
 int SMBHCTRL_ENABLE ; 
 int /*<<< orphan*/  SMBSCTRL ; 
 int SMBSCTRL_ENABLE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int VIAPM_INB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIAPM_OUTB (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VIAPM_PRO_REVID ; 
 int /*<<< orphan*/  VIAPM_PRO_SMBCTRL ; 
 scalar_t__ bootverbose ; 
 scalar_t__ bus_alloc_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int,int,int,int) ; 
 scalar_t__ bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *,struct viapm_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  isab_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_class (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_subclass (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ viasmb_intr ; 

__attribute__((used)) static int
viapm_pro_attach(device_t dev)
{
	struct viapm_softc *viapm = (struct viapm_softc *)device_get_softc(dev);
	u_int32_t l;

	mtx_init(&viapm->lock, device_get_nameunit(dev), "viapm", MTX_DEF);
	if (!(viapm->iores = bus_alloc_resource_any(dev, SYS_RES_IOPORT,
		&viapm->iorid, RF_ACTIVE))) {
		device_printf(dev, "could not allocate bus space\n");
		goto error;
	}

#ifdef notyet
	/* force irq 9 */
	l = pci_read_config(dev, VIAPM_PRO_SMBCTRL, 1);
	pci_write_config(dev, VIAPM_PRO_SMBCTRL, l | 0x80, 1);

	viapm->irqrid = 0;
	if (!(viapm->irqres = bus_alloc_resource(dev, SYS_RES_IRQ,
				&viapm->irqrid, 9, 9, 1,
				RF_SHAREABLE | RF_ACTIVE))) {
		device_printf(dev, "could not allocate irq\n");
		goto error;
	}

	if (bus_setup_intr(dev, viapm->irqres, INTR_TYPE_MISC | INTR_MPSAFE,
			(driver_intr_t *) viasmb_intr, viapm, &viapm->irqih)) {
		device_printf(dev, "could not setup irq\n");
		goto error;
	}
#endif

	if (bootverbose) {
		l = pci_read_config(dev, VIAPM_PRO_REVID, 1);
		device_printf(dev, "SMBus revision code 0x%x\n", l);
	}

	viapm->smbus = device_add_child(dev, "smbus", -1);

	/* probe and attach the smbus */
	bus_generic_attach(dev);

	/* disable slave function */
	VIAPM_OUTB(SMBSCTRL, VIAPM_INB(SMBSCTRL) & ~SMBSCTRL_ENABLE);

	/* enable the SMBus controller function */
	l = pci_read_config(dev, VIAPM_PRO_SMBCTRL, 1);
	pci_write_config(dev, VIAPM_PRO_SMBCTRL, l | 1, 1);

#ifdef notyet
	/* enable interrupts */
	VIAPM_OUTB(SMBHCTRL, VIAPM_INB(SMBHCTRL) | SMBHCTRL_ENABLE);
#endif

#ifdef DEV_ISA
	/* If this device is a PCI-ISA bridge, then attach an ISA bus. */
	if ((pci_get_class(dev) == PCIC_BRIDGE) &&
	    (pci_get_subclass(dev) == PCIS_BRIDGE_ISA))
		isab_attach(dev);
#endif
	return 0;

error:
	if (viapm->iores)
		bus_release_resource(dev, SYS_RES_IOPORT, viapm->iorid, viapm->iores);
#ifdef notyet
	if (viapm->irqres)
		bus_release_resource(dev, SYS_RES_IRQ, viapm->irqrid, viapm->irqres);
#endif
	mtx_destroy(&viapm->lock);

	return ENXIO;
}