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
struct resource {int dummy; } ;
struct isab_pci_softc {TYPE_1__* isab_pci_res; } ;
typedef  scalar_t__ device_t ;
struct TYPE_2__ {int ip_refs; struct resource* ip_res; } ;

/* Variables and functions */
 int BUS_RELEASE_RESOURCE (scalar_t__,scalar_t__,int,int,struct resource*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PCIR_MAX_BAR_0 ; 
 int PCI_RID2BAR (int) ; 
#define  SYS_RES_IOPORT 129 
#define  SYS_RES_MEMORY 128 
 int bus_generic_release_resource (scalar_t__,scalar_t__,int,int,struct resource*) ; 
 int bus_release_resource (scalar_t__,int,int,struct resource*) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 
 struct isab_pci_softc* device_get_softc (scalar_t__) ; 

__attribute__((used)) static int
isab_pci_release_resource(device_t dev, device_t child, int type, int rid,
    struct resource *r)
{
	struct isab_pci_softc *sc;
	int bar, error;

	if (device_get_parent(child) != dev)
		return bus_generic_release_resource(dev, child, type, rid, r);

	switch (type) {
	case SYS_RES_MEMORY:
	case SYS_RES_IOPORT:
		/*
		 * For BARs, we release the resource from the PCI bus
		 * when the last child reference goes away.
		 */
		bar = PCI_RID2BAR(rid);
		if (bar < 0 || bar > PCIR_MAX_BAR_0)
			return (EINVAL);
		sc = device_get_softc(dev);
		if (sc->isab_pci_res[bar].ip_res == NULL)
			return (EINVAL);
		KASSERT(sc->isab_pci_res[bar].ip_res == r,
		    ("isa_pci resource mismatch"));
		if (sc->isab_pci_res[bar].ip_refs > 1) {
			sc->isab_pci_res[bar].ip_refs--;
			return (0);
		}
		KASSERT(sc->isab_pci_res[bar].ip_refs > 0,
		    ("isa_pci resource reference count underflow"));
		error = bus_release_resource(dev, type, rid, r);
		if (error == 0) {
			sc->isab_pci_res[bar].ip_res = NULL;
			sc->isab_pci_res[bar].ip_refs = 0;
		}
		return (error);
	}

	return (BUS_RELEASE_RESOURCE(device_get_parent(dev), child, type,
		rid, r));
}