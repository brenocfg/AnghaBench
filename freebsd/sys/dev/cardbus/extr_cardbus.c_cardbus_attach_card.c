#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pci_devinfo {int dummy; } ;
struct cardbus_softc {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/ * dev; scalar_t__ mfdev; } ;
struct TYPE_5__ {TYPE_4__ cfg; int /*<<< orphan*/  resources; } ;
struct cardbus_devinfo {TYPE_1__ pci; int /*<<< orphan*/  mprefetchable; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEVPRINTF (int /*<<< orphan*/ *) ; 
 int ENOENT ; 
 int /*<<< orphan*/  Giant ; 
 int PCI_FUNCMAX ; 
 int /*<<< orphan*/  POWER_DISABLE_SOCKET (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  POWER_ENABLE_SOCKET (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cardbus_detach_card (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cardbus_device_create (struct cardbus_softc*,struct cardbus_devinfo*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cardbus_device_setup_regs (TYPE_4__*) ; 
 scalar_t__ cardbus_do_cis (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * device_get_parent (int /*<<< orphan*/ *) ; 
 struct cardbus_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 scalar_t__ device_probe_and_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,struct cardbus_devinfo*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_add_resources (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_cfg_restore (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  pci_cfg_save (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  pci_freecfg (struct pci_devinfo*) ; 
 int /*<<< orphan*/  pci_print_verbose (TYPE_1__*) ; 
 scalar_t__ pci_read_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int) ; 
 int pcib_get_bus (int /*<<< orphan*/ *) ; 
 int pcib_get_domain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_list_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cardbus_attach_card(device_t cbdev)
{
	device_t brdev = device_get_parent(cbdev);
	device_t child;
	int bus, domain, slot, func;
	int cardattached = 0;
	int cardbusfunchigh = 0;
	struct cardbus_softc *sc;

	sc = device_get_softc(cbdev);
	cardbus_detach_card(cbdev); /* detach existing cards */
	POWER_DISABLE_SOCKET(brdev, cbdev); /* Turn the socket off first */
	POWER_ENABLE_SOCKET(brdev, cbdev);
	domain = pcib_get_domain(cbdev);
	bus = pcib_get_bus(cbdev);
	slot = 0;
	mtx_lock(&Giant);
	/* For each function, set it up and try to attach a driver to it */
	for (func = 0; func <= cardbusfunchigh; func++) {
		struct cardbus_devinfo *dinfo;

		dinfo = (struct cardbus_devinfo *)
		    pci_read_device(brdev, cbdev, domain, bus, slot, func);
		if (dinfo == NULL)
			continue;
		if (dinfo->pci.cfg.mfdev)
			cardbusfunchigh = PCI_FUNCMAX;

		child = device_add_child(cbdev, NULL, -1);
		if (child == NULL) {
			DEVPRINTF((cbdev, "Cannot add child!\n"));
			pci_freecfg((struct pci_devinfo *)dinfo);
			continue;
		}
		dinfo->pci.cfg.dev = child;
		resource_list_init(&dinfo->pci.resources);
		device_set_ivars(child, dinfo);
		cardbus_device_create(sc, dinfo, cbdev, child);
		if (cardbus_do_cis(cbdev, child) != 0)
			DEVPRINTF((cbdev, "Warning: Bogus CIS ignored\n"));
		pci_cfg_save(dinfo->pci.cfg.dev, &dinfo->pci, 0);
		pci_cfg_restore(dinfo->pci.cfg.dev, &dinfo->pci);
		cardbus_device_setup_regs(&dinfo->pci.cfg);
		pci_add_resources(cbdev, child, 1, dinfo->mprefetchable);
		pci_print_verbose(&dinfo->pci);
		if (device_probe_and_attach(child) == 0)
			cardattached++;
		else
			pci_cfg_save(dinfo->pci.cfg.dev, &dinfo->pci, 1);
	}
	mtx_unlock(&Giant);
	if (cardattached > 0)
		return (0);
/*	POWER_DISABLE_SOCKET(brdev, cbdev); */
	return (ENOENT);
}