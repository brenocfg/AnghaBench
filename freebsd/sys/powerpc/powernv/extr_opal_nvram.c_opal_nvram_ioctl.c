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
typedef  int u_long ;
struct thread {int dummy; } ;
struct opal_nvram_softc {int /*<<< orphan*/  sc_size; } ;
struct cdev {struct opal_nvram_softc* si_drv1; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
#define  DIOCGMEDIASIZE 128 
 int EINVAL ; 

__attribute__((used)) static int
opal_nvram_ioctl(struct cdev *dev, u_long cmd, caddr_t data, int fflag,
    struct thread *td)
{
	struct opal_nvram_softc *sc = dev->si_drv1;

	switch (cmd) {
	case DIOCGMEDIASIZE:
		*(off_t *)data = sc->sc_size;
		return (0);
	}
	return (EINVAL);
}