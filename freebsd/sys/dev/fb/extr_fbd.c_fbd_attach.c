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
struct fbd_softc {int /*<<< orphan*/ * sc_info; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/ * FB_GETINFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct fbd_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int fbd_register (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
fbd_attach(device_t dev)
{
	struct fbd_softc *sc;
	int err;

	sc = device_get_softc(dev);

	sc->sc_dev = dev;
	sc->sc_info = FB_GETINFO(device_get_parent(dev));
	if (sc->sc_info == NULL)
		return (ENXIO);
	err = fbd_register(sc->sc_info);

	return (err);
}