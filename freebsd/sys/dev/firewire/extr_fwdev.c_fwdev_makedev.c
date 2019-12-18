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
struct firewire_softc {struct cdev* dev; TYPE_1__* fc; } ;
struct cdev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FWMEM_FLAG ; 
 int /*<<< orphan*/  GID_OPERATOR ; 
 int /*<<< orphan*/  MAKEMINOR (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  dev_depends (struct cdev*,struct cdev*) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  firewire_cdevsw ; 
 void* make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_dev_alias (struct cdev*,char*,int) ; 

int
fwdev_makedev(struct firewire_softc *sc)
{
	int err = 0;

	struct cdev *d;
	int unit;

	unit = device_get_unit(sc->fc->bdev);
	sc->dev = make_dev(&firewire_cdevsw, MAKEMINOR(0, unit, 0),
	    UID_ROOT, GID_OPERATOR, 0660, "fw%d.%d", unit, 0);
	d = make_dev(&firewire_cdevsw, MAKEMINOR(FWMEM_FLAG, unit, 0),
	    UID_ROOT, GID_OPERATOR, 0660, "fwmem%d.%d", unit, 0);
	dev_depends(sc->dev, d);
	make_dev_alias(sc->dev, "fw%d", unit);
	make_dev_alias(d, "fwmem%d", unit);

	return (err);
}