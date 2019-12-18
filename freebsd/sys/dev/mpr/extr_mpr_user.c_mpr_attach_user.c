#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mpr_softc {TYPE_1__* mpr_cdev; int /*<<< orphan*/  mpr_dev; } ;
struct TYPE_2__ {struct mpr_softc* si_drv1; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GID_OPERATOR ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 TYPE_1__* make_dev (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  mpr_cdevsw ; 

int
mpr_attach_user(struct mpr_softc *sc)
{
	int unit;

	unit = device_get_unit(sc->mpr_dev);
	sc->mpr_cdev = make_dev(&mpr_cdevsw, unit, UID_ROOT, GID_OPERATOR, 0640,
	    "mpr%d", unit);

	if (sc->mpr_cdev == NULL)
		return (ENOMEM);

	sc->mpr_cdev->si_drv1 = sc;
	return (0);
}