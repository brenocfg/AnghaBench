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
struct powermac_nvram_softc {int sc_isopen; scalar_t__ sc_wpos; scalar_t__ sc_rpos; } ;
struct cdev {struct powermac_nvram_softc* si_drv1; } ;

/* Variables and functions */
 int EBUSY ; 

__attribute__((used)) static int
powermac_nvram_open(struct cdev *dev, int flags, int fmt, struct thread *td)
{
	struct powermac_nvram_softc *sc = dev->si_drv1;

	if (sc->sc_isopen)
		return EBUSY;
	sc->sc_isopen = 1;
	sc->sc_rpos = sc->sc_wpos = 0;
	return 0;
}