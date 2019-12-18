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
struct viapm_softc {int /*<<< orphan*/  lock; scalar_t__ iores; int /*<<< orphan*/  iorid; scalar_t__ iicbb; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
viapm_586b_detach(device_t dev)
{
	struct viapm_softc *viapm = (struct viapm_softc *)device_get_softc(dev);

	bus_generic_detach(dev);
	if (viapm->iicbb) {
		device_delete_child(dev, viapm->iicbb);
	}

	if (viapm->iores)
		bus_release_resource(dev, SYS_RES_IOPORT, viapm->iorid,
		    viapm->iores);
	mtx_destroy(&viapm->lock);

	return 0;
}