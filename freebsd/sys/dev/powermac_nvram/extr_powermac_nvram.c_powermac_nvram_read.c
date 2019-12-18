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
struct uio {scalar_t__ uio_resid; } ;
struct powermac_nvram_softc {int sc_rpos; scalar_t__ sc_data; } ;
struct cdev {struct powermac_nvram_softc* si_drv1; } ;

/* Variables and functions */
 int MIN (scalar_t__,int) ; 
 int uiomove (void*,int,struct uio*) ; 

__attribute__((used)) static int
powermac_nvram_read(struct cdev *dev, struct uio *uio, int ioflag)
{
	int rv, amnt, data_available;
	struct powermac_nvram_softc *sc = dev->si_drv1;

	rv = 0;
	while (uio->uio_resid > 0) {
		data_available = sizeof(sc->sc_data) - sc->sc_rpos;
		if (data_available > 0) {
			amnt = MIN(uio->uio_resid, data_available);
			rv = uiomove((void *)(sc->sc_data + sc->sc_rpos),
			    amnt, uio);
			if (rv != 0)
				break;
			sc->sc_rpos += amnt;
		} else {
			break;
		}
	}
	return rv;
}