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
struct pps_data {int /*<<< orphan*/  ppbus; int /*<<< orphan*/ * pps; } ;
struct cdev {int /*<<< orphan*/  si_drv2; struct pps_data* si_drv1; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ppb_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_unlock (int /*<<< orphan*/ ) ; 
 int pps_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ppsioctl(struct cdev *dev, u_long cmd, caddr_t data, int flags, struct thread *td)
{
	struct pps_data *sc = dev->si_drv1;
	int subdev = (intptr_t)dev->si_drv2;
	int err;

	ppb_lock(sc->ppbus);
	err = pps_ioctl(cmd, data, &sc->pps[subdev]);
	ppb_unlock(sc->ppbus);
	return (err);
}