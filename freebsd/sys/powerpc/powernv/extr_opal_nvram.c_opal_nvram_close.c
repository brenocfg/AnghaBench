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
struct opal_nvram_softc {scalar_t__ sc_isopen; } ;
struct cdev {struct opal_nvram_softc* si_drv1; } ;

/* Variables and functions */

__attribute__((used)) static int
opal_nvram_close(struct cdev *dev, int fflag, int devtype, struct thread *td)
{
	struct opal_nvram_softc *sc = dev->si_drv1;

	sc->sc_isopen = 0;
	return (0);
}