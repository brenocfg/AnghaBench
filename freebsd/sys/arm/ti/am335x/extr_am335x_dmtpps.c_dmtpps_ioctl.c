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
struct dmtpps_softc {int /*<<< orphan*/  pps_mtx; int /*<<< orphan*/  pps_state; } ;
struct cdev {struct dmtpps_softc* si_drv1; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  dmtpps_set_hw_capture (struct dmtpps_softc*,int) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int pps_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dmtpps_ioctl(struct cdev *dev, u_long cmd, caddr_t data, 
    int flags, struct thread *td)
{
	struct dmtpps_softc *sc;
	int err;

	sc = dev->si_drv1;

	/* Let the kernel do the heavy lifting for ioctl. */
	mtx_lock_spin(&sc->pps_mtx);
	err = pps_ioctl(cmd, data, &sc->pps_state);
	mtx_unlock_spin(&sc->pps_mtx);
	if (err != 0)
		return (err);

	/*
	 * The capture mode could have changed, set the hardware to whatever
	 * mode is now current.  Effectively a no-op if nothing changed.
	 */
	dmtpps_set_hw_capture(sc, false);

	return (err);
}