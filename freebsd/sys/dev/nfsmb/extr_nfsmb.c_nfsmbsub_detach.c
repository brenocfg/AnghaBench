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
struct nfsmb_softc {int /*<<< orphan*/ * res; int /*<<< orphan*/  rid; int /*<<< orphan*/  lock; int /*<<< orphan*/ * smbus; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct nfsmb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nfsmbsub_detach(device_t dev)
{
	device_t parent;
	struct nfsmb_softc *nfsmbsub_sc = device_get_softc(dev);

	parent = device_get_parent(dev);

	if (nfsmbsub_sc->smbus) {
		device_delete_child(dev, nfsmbsub_sc->smbus);
		nfsmbsub_sc->smbus = NULL;
	}
	mtx_destroy(&nfsmbsub_sc->lock);
	if (nfsmbsub_sc->res) {
		bus_release_resource(parent, SYS_RES_IOPORT, nfsmbsub_sc->rid,
		    nfsmbsub_sc->res);
		nfsmbsub_sc->res = NULL;
	}
	return (0);
}