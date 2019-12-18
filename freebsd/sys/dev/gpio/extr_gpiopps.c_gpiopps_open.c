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
 scalar_t__ DS_BUSY ; 
 int /*<<< orphan*/  device_busy (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
gpiopps_open(struct cdev *dev, int flags, int fmt, struct thread *td)
{
	struct pps_softc *sc = dev->si_drv1;

	/* We can't be unloaded while open, so mark ourselves BUSY. */
	mtx_lock(&sc->pps_mtx);
	if (device_get_state(sc->dev) < DS_BUSY) {
		device_busy(sc->dev);
	}
	mtx_unlock(&sc->pps_mtx);

	return 0;
}