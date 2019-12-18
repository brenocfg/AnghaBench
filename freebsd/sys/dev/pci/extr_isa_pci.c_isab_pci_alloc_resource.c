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
typedef  int /*<<< orphan*/  u_int ;
struct resource {int dummy; } ;
struct isab_pci_softc {TYPE_1__* isab_pci_res; } ;
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  scalar_t__ device_t ;
struct TYPE_2__ {struct resource* ip_res; int /*<<< orphan*/  ip_refs; } ;

/* Variables and functions */
 struct resource* BUS_ALLOC_RESOURCE (scalar_t__,scalar_t__,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PCIR_MAX_BAR_0 ; 
 int PCI_RID2BAR (int) ; 
#define  SYS_RES_IOPORT 129 
#define  SYS_RES_MEMORY 128 
 struct resource* bus_alloc_resource (scalar_t__,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource* bus_generic_alloc_resource (scalar_t__,scalar_t__,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 
 struct isab_pci_softc* device_get_softc (scalar_t__) ; 

__attribute__((used)) static struct resource *
isab_pci_alloc_resource(device_t dev, device_t child, int type, int *rid,
    rman_res_t start, rman_res_t end, rman_res_t count, u_int flags)
{
	struct isab_pci_softc *sc;
	int bar;

	if (device_get_parent(child) != dev)
		return bus_generic_alloc_resource(dev, child, type, rid, start,
		    end, count, flags);

	switch (type) {
	case SYS_RES_MEMORY:
	case SYS_RES_IOPORT:
		/*
		 * For BARs, we cache the resource so that we only allocate it
		 * from the PCI bus once.
		 */
		bar = PCI_RID2BAR(*rid);
		if (bar < 0 || bar > PCIR_MAX_BAR_0)
			return (NULL);
		sc = device_get_softc(dev);
		if (sc->isab_pci_res[bar].ip_res == NULL)
			sc->isab_pci_res[bar].ip_res = bus_alloc_resource(dev, type,
			    rid, start, end, count, flags);
		if (sc->isab_pci_res[bar].ip_res != NULL)
			sc->isab_pci_res[bar].ip_refs++;
		return (sc->isab_pci_res[bar].ip_res);
	}

	return (BUS_ALLOC_RESOURCE(device_get_parent(dev), child, type, rid,
		start, end, count, flags));
}