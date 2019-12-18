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
struct thunder_pem_softc {int /*<<< orphan*/  id; } ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_RELEASE_RESOURCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct resource*) ; 
 int PCI_RES_BUS ; 
 int SYS_RES_IOPORT ; 
 int SYS_RES_MEMORY ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct thunder_pem_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int pci_domain_release_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 
 int rman_release_resource (struct resource*) ; 

__attribute__((used)) static int
thunder_pem_release_resource(device_t dev, device_t child, int type, int rid,
    struct resource *res)
{
	device_t parent_dev;
#if defined(NEW_PCIB) && defined(PCI_RES_BUS)
	struct thunder_pem_softc *sc = device_get_softc(dev);

	if (type == PCI_RES_BUS)
		return (pci_domain_release_bus(sc->id, child, rid, res));
#endif
	/* Find parent device. On ThunderX we know an exact path. */
	parent_dev = device_get_parent(device_get_parent(dev));

	if ((type != SYS_RES_MEMORY) && (type != SYS_RES_IOPORT))
		return (BUS_RELEASE_RESOURCE(parent_dev, child,
		    type, rid, res));

	return (rman_release_resource(res));
}