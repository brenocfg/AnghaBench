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
struct make_dev_args {int mda_flags; int mda_mode; struct evdev_dev* mda_si_drv1; int /*<<< orphan*/  mda_gid; int /*<<< orphan*/  mda_uid; int /*<<< orphan*/ * mda_devsw; } ;
struct evdev_dev {int ev_unit; int /*<<< orphan*/  ev_cdev; } ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  GID_WHEEL ; 
 int MAKEDEV_CHECKNAME ; 
 int MAKEDEV_WAITOK ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  evdev_cdevsw ; 
 int /*<<< orphan*/  make_dev_args_init (struct make_dev_args*) ; 
 int make_dev_s (struct make_dev_args*,int /*<<< orphan*/ *,char*,int) ; 

int
evdev_cdev_create(struct evdev_dev *evdev)
{
	struct make_dev_args mda;
	int ret, unit = 0;

	make_dev_args_init(&mda);
	mda.mda_flags = MAKEDEV_WAITOK | MAKEDEV_CHECKNAME;
	mda.mda_devsw = &evdev_cdevsw;
	mda.mda_uid = UID_ROOT;
	mda.mda_gid = GID_WHEEL;
	mda.mda_mode = 0600;
	mda.mda_si_drv1 = evdev;

	/* Try to coexist with cuse-backed input/event devices */
	while ((ret = make_dev_s(&mda, &evdev->ev_cdev, "input/event%d", unit))
	    == EEXIST)
		unit++;

	if (ret == 0)
		evdev->ev_unit = unit;

	return (ret);
}