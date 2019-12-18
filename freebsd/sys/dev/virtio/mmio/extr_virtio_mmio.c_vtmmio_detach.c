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
struct vtmmio_softc {int /*<<< orphan*/ ** res; int /*<<< orphan*/ * vtmmio_child_dev; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int device_delete_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct vtmmio_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vtmmio_reset (struct vtmmio_softc*) ; 

__attribute__((used)) static int
vtmmio_detach(device_t dev)
{
	struct vtmmio_softc *sc;
	device_t child;
	int error;

	sc = device_get_softc(dev);

	if ((child = sc->vtmmio_child_dev) != NULL) {
		error = device_delete_child(dev, child);
		if (error)
			return (error);
		sc->vtmmio_child_dev = NULL;
	}

	vtmmio_reset(sc);

	if (sc->res[0] != NULL) {
		bus_release_resource(dev, SYS_RES_MEMORY, 0,
		    sc->res[0]);
		sc->res[0] = NULL;
	}

	return (0);
}