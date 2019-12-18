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
struct gxemul_disk_softc {int /*<<< orphan*/  sc_size; int /*<<< orphan*/ * sc_provider; int /*<<< orphan*/ * sc_geom; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_WAITOK ; 
 struct gxemul_disk_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 unsigned int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_post_event (int /*<<< orphan*/ ,struct gxemul_disk_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gxemul_disk_attach_geom ; 
 int /*<<< orphan*/  gxemul_disk_controller_mutex ; 
 int gxemul_disk_size (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
gxemul_disk_attach(device_t dev)
{
	struct gxemul_disk_softc *sc;
	unsigned diskid;
	int error;

	diskid = device_get_unit(dev);

	sc = device_get_softc(dev);
	sc->sc_dev = dev;
	sc->sc_geom = NULL;
	sc->sc_provider = NULL;

	mtx_lock(&gxemul_disk_controller_mutex);
	error = gxemul_disk_size(diskid, &sc->sc_size);
	if (error != 0) {
		mtx_unlock(&gxemul_disk_controller_mutex);
		return (error);
	}
	mtx_unlock(&gxemul_disk_controller_mutex);

	g_post_event(gxemul_disk_attach_geom, sc, M_WAITOK, NULL);

	return (0);
}