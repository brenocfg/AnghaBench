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
struct cdev {int dummy; } ;
struct apm_softc {scalar_t__ initialized; int sc_flags; int /*<<< orphan*/  event_filter; } ;

/* Variables and functions */
#define  APMDEV_CTL 129 
#define  APMDEV_NORMAL 128 
 int EBUSY ; 
 int EINVAL ; 
 int ENXIO ; 
 int FWRITE ; 
 int SCFLAG_OCTL ; 
 int SCFLAG_ONORMAL ; 
 struct apm_softc apm_softc ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 int dev2unit (struct cdev*) ; 

__attribute__((used)) static int
apmopen(struct cdev *dev, int flag, int fmt, struct thread *td)
{
	struct apm_softc *sc = &apm_softc;

	if (sc == NULL || sc->initialized == 0)
		return (ENXIO);

	switch (dev2unit(dev)) {
	case APMDEV_CTL:
		if (!(flag & FWRITE))
			return EINVAL;
		if (sc->sc_flags & SCFLAG_OCTL)
			return EBUSY;
		sc->sc_flags |= SCFLAG_OCTL;
		bzero(sc->event_filter, sizeof sc->event_filter);
		break;
	case APMDEV_NORMAL:
		sc->sc_flags |= SCFLAG_ONORMAL;
		break;
	}
	return 0;
}