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
struct resource {int dummy; } ;
struct mv_pcib_softc {int /*<<< orphan*/  ap_segment; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_RELEASE_RESOURCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct resource*) ; 
 int PCI_RES_BUS ; 
 int SYS_RES_IOPORT ; 
 int SYS_RES_MEMORY ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct mv_pcib_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int pci_domain_release_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 
 int rman_release_resource (struct resource*) ; 

__attribute__((used)) static int
mv_pcib_release_resource(device_t dev, device_t child, int type, int rid,
    struct resource *res)
{
#ifdef PCI_RES_BUS
	struct mv_pcib_softc *sc = device_get_softc(dev);

	if (type == PCI_RES_BUS)
		return (pci_domain_release_bus(sc->ap_segment, child, rid, res));
#endif
	if (type != SYS_RES_IOPORT && type != SYS_RES_MEMORY)
		return (BUS_RELEASE_RESOURCE(device_get_parent(dev), child,
		    type, rid, res));

	return (rman_release_resource(res));
}