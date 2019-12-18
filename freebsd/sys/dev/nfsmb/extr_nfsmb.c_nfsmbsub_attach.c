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
struct nfsmb_softc {int rid; int /*<<< orphan*/ * smbus; int /*<<< orphan*/  lock; int /*<<< orphan*/ * res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int NF2PCI_SMBASE_2 ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct nfsmb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsmbsub_detach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfsmbsub_attach(device_t dev)
{
	device_t parent;
	struct nfsmb_softc *nfsmbsub_sc = device_get_softc(dev);

	parent = device_get_parent(dev);

	nfsmbsub_sc->rid = NF2PCI_SMBASE_2;

	nfsmbsub_sc->res = bus_alloc_resource_any(parent, SYS_RES_IOPORT,
	    &nfsmbsub_sc->rid, RF_ACTIVE);
	if (nfsmbsub_sc->res == NULL) {
		/* Older incarnations of the device used non-standard BARs. */
		nfsmbsub_sc->rid = 0x54;
		nfsmbsub_sc->res = bus_alloc_resource_any(parent,
		    SYS_RES_IOPORT, &nfsmbsub_sc->rid, RF_ACTIVE);
		if (nfsmbsub_sc->res == NULL) {
			device_printf(dev, "could not map i/o space\n");
			return (ENXIO);
		}
	}
	mtx_init(&nfsmbsub_sc->lock, device_get_nameunit(dev), "nfsmb",
	    MTX_DEF);

	nfsmbsub_sc->smbus = device_add_child(dev, "smbus", -1);
	if (nfsmbsub_sc->smbus == NULL) {
		nfsmbsub_detach(dev);
		return (EINVAL);
	}

	bus_generic_attach(dev);

	return (0);
}