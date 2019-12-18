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
struct TYPE_2__ {char* d_name; } ;
struct tuntap_driver {TYPE_1__ cdevsw; int /*<<< orphan*/  clones; int /*<<< orphan*/  unrhdr; } ;
struct if_clone {int dummy; } ;
struct cdev {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int EEXIST ; 
 int ENXIO ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int alloc_unr (int /*<<< orphan*/ ) ; 
 int alloc_unr_specific (int /*<<< orphan*/ ,int) ; 
 int clone_create (int /*<<< orphan*/ *,TYPE_1__*,int*,struct cdev**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*,int) ; 
 int tun_create_device (struct tuntap_driver*,int,int /*<<< orphan*/ *,struct cdev**,char*) ; 
 int /*<<< orphan*/  tuncreate (struct cdev*) ; 
 struct tuntap_driver* tuntap_driver_from_flags (int) ; 
 int tuntap_name2info (char*,int*,int*) ; 

__attribute__((used)) static int
tun_clone_create(struct if_clone *ifc, char *name, size_t len, caddr_t params)
{
	struct tuntap_driver *drv;
	struct cdev *dev;
	int err, i, tunflags, unit;

	tunflags = 0;
	/* The name here tells us exactly what we're creating */
	err = tuntap_name2info(name, &unit, &tunflags);
	if (err != 0)
		return (err);

	drv = tuntap_driver_from_flags(tunflags);
	if (drv == NULL)
		return (ENXIO);

	if (unit != -1) {
		/* If this unit number is still available that's okay. */
		if (alloc_unr_specific(drv->unrhdr, unit) == -1)
			return (EEXIST);
	} else {
		unit = alloc_unr(drv->unrhdr);
	}

	snprintf(name, IFNAMSIZ, "%s%d", drv->cdevsw.d_name, unit);

	/* find any existing device, or allocate new unit number */
	dev = NULL;
	i = clone_create(&drv->clones, &drv->cdevsw, &unit, &dev, 0);
	/* No preexisting struct cdev *, create one */
	if (i != 0)
		i = tun_create_device(drv, unit, NULL, &dev, name);
	if (i == 0)
		tuncreate(dev);

	return (i);
}