#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {scalar_t__ msi_alloc; int msi_ctrl; } ;
struct TYPE_4__ {TYPE_1__ msi; } ;
struct pci_devinfo {TYPE_2__ cfg; } ;
struct opalpci_softc {int base_msi_irq; int msi_base; int /*<<< orphan*/  phb_id; int /*<<< orphan*/ * msi_vmem; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENODEV ; 
 int ENXIO ; 
 int /*<<< orphan*/  OPAL_GET_MSI_32 ; 
 int /*<<< orphan*/  OPAL_GET_MSI_64 ; 
 int /*<<< orphan*/  OPAL_PCI_DEFAULT_PE ; 
 int /*<<< orphan*/  OPAL_PCI_SET_XIVE_PE ; 
 int PCIM_MSICTRL_64BIT ; 
 int /*<<< orphan*/  be32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64toh (int /*<<< orphan*/ ) ; 
 scalar_t__ bootverbose ; 
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 struct opalpci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int opal_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  vtophys (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
opalpci_map_msi(device_t dev, device_t child, int irq, uint64_t *addr,
    uint32_t *data)
{
	struct opalpci_softc *sc;
	struct pci_devinfo *dinfo;
	int err, xive;

	sc = device_get_softc(dev);
	if (sc->msi_vmem == NULL)
		return (ENODEV);

	xive = irq - sc->base_msi_irq - sc->msi_base;
	opal_call(OPAL_PCI_SET_XIVE_PE, sc->phb_id, OPAL_PCI_DEFAULT_PE, xive);

	dinfo = device_get_ivars(child);
	if (dinfo->cfg.msi.msi_alloc > 0 &&
	    (dinfo->cfg.msi.msi_ctrl & PCIM_MSICTRL_64BIT) == 0) {
		uint32_t msi32;
		err = opal_call(OPAL_GET_MSI_32, sc->phb_id,
		    OPAL_PCI_DEFAULT_PE, xive, 1, vtophys(&msi32),
		    vtophys(data));
		*addr = be32toh(msi32);
	} else {
		err = opal_call(OPAL_GET_MSI_64, sc->phb_id,
		    OPAL_PCI_DEFAULT_PE, xive, 1, vtophys(addr), vtophys(data));
		*addr = be64toh(*addr);
	}
	*data = be32toh(*data);

	if (bootverbose && err != 0)
		device_printf(child, "OPAL MSI mapping error: %d\n", err);

	return ((err == 0) ? 0 : ENXIO);
}