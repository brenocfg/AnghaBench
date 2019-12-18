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
typedef  int /*<<< orphan*/  u_long ;
struct thread {int dummy; } ;
struct pps_softc {int /*<<< orphan*/  pps_mtx; int /*<<< orphan*/  pps_state; } ;
struct cdev {struct pps_softc* si_drv1; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int pps_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
gpiopps_ioctl(struct cdev *dev, u_long cmd, caddr_t data, int flags, struct thread *td)
{
	struct pps_softc *sc = dev->si_drv1;
	int err;

	/* Let the kernel do the heavy lifting for ioctl. */
	mtx_lock(&sc->pps_mtx);
	err = pps_ioctl(cmd, data, &sc->pps_state);
	mtx_unlock(&sc->pps_mtx);

	return err;
}