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
struct siosc {int /*<<< orphan*/  conf_lock; int /*<<< orphan*/  io_res; int /*<<< orphan*/  io_rid; int /*<<< orphan*/ * chardev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_children (int /*<<< orphan*/ ) ; 
 struct siosc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
superio_detach(device_t dev)
{
	struct siosc *sc = device_get_softc(dev);
	int error;

	error = bus_generic_detach(dev);
	if (error != 0)
		return (error);
	if (sc->chardev != NULL)
		destroy_dev(sc->chardev);
	device_delete_children(dev);
	bus_release_resource(dev, SYS_RES_IOPORT, sc->io_rid, sc->io_res);
	mtx_destroy(&sc->conf_lock);
	return (0);
}