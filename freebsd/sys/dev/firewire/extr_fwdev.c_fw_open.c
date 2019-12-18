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
struct fw_drv1 {int /*<<< orphan*/  rq; int /*<<< orphan*/  binds; int /*<<< orphan*/  fc; } ;
struct firewire_softc {int /*<<< orphan*/  fc; } ;
struct cdev {int si_flags; struct fw_drv1* si_drv1; } ;
typedef  int /*<<< orphan*/  fw_proc ;

/* Variables and functions */
 int DEV2SUB (struct cdev*) ; 
 int DEV2UNIT (struct cdev*) ; 
 scalar_t__ DEV_FWMEM (struct cdev*) ; 
 int EBUSY ; 
 int ENXIO ; 
 int /*<<< orphan*/  FW_GLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_GUNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GID_OPERATOR ; 
 int /*<<< orphan*/  M_FW ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int SI_NAMED ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  dev2unit (struct cdev*) ; 
 struct firewire_softc* devclass_get_softc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  firewire_cdevsw ; 
 int /*<<< orphan*/  firewire_devclass ; 
 int fwmem_open (struct cdev*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int,int) ; 
 struct fw_drv1* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
fw_open(struct cdev *dev, int flags, int fmt, fw_proc *td)
{
	int err = 0;
	int unit = DEV2UNIT(dev);
	struct fw_drv1 *d;
	struct firewire_softc *sc;

	if (DEV_FWMEM(dev))
		return fwmem_open(dev, flags, fmt, td);

	sc = devclass_get_softc(firewire_devclass, unit);
	if (sc == NULL)
		return (ENXIO);

	FW_GLOCK(sc->fc);
	if (dev->si_drv1 != NULL) {
		FW_GUNLOCK(sc->fc);
		return (EBUSY);
	}
	/* set dummy value for allocation */
	dev->si_drv1 = (void *)-1;
	FW_GUNLOCK(sc->fc);

	dev->si_drv1 = malloc(sizeof(struct fw_drv1), M_FW, M_WAITOK | M_ZERO);

	if ((dev->si_flags & SI_NAMED) == 0) {
		int unit = DEV2UNIT(dev);
		int sub = DEV2SUB(dev);

		make_dev(&firewire_cdevsw, dev2unit(dev),
		    UID_ROOT, GID_OPERATOR, 0660, "fw%d.%d", unit, sub);
	}

	d = dev->si_drv1;
	d->fc = sc->fc;
	STAILQ_INIT(&d->binds);
	STAILQ_INIT(&d->rq);

	return err;
}