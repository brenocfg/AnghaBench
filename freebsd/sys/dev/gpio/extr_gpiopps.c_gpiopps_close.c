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
struct pps_softc {int /*<<< orphan*/  pps_mtx; int /*<<< orphan*/  dev; } ;
struct cdev {struct pps_softc* si_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_unbusy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static	int
gpiopps_close(struct cdev *dev, int flags, int fmt, struct thread *td)
{
	struct pps_softc *sc = dev->si_drv1;

	/*
	 * Un-busy on last close. We rely on the vfs counting stuff to only call
	 * this routine on last-close, so we don't need any open-count logic.
	 */
	mtx_lock(&sc->pps_mtx);
	device_unbusy(sc->dev);
	mtx_unlock(&sc->pps_mtx);

	return 0;
}