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
struct thread {int dummy; } ;
struct spigen_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_dev; } ;
struct cdev {int /*<<< orphan*/  si_drv1; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  device_busy (int /*<<< orphan*/ ) ; 
 struct spigen_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int 
spigen_open(struct cdev *cdev, int oflags, int devtype, struct thread *td)
{
	device_t dev;
	struct spigen_softc *sc;

	dev = cdev->si_drv1;
	sc = device_get_softc(dev);

	mtx_lock(&sc->sc_mtx);
	device_busy(sc->sc_dev);
	mtx_unlock(&sc->sc_mtx);

	return (0);
}