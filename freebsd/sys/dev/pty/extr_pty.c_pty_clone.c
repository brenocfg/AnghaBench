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
struct ucred {int dummy; } ;
struct make_dev_args {int mda_flags; int mda_mode; int /*<<< orphan*/  mda_gid; int /*<<< orphan*/  mda_uid; int /*<<< orphan*/ * mda_devsw; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GID_WHEEL ; 
 int MAKEDEV_CHECKNAME ; 
 int MAKEDEV_REF ; 
 int /*<<< orphan*/  UID_ROOT ; 
 scalar_t__ bcmp (char*,char*,int) ; 
 int /*<<< orphan*/  make_dev_args_init (struct make_dev_args*) ; 
 int make_dev_s (struct make_dev_args*,struct cdev**,char*,char*) ; 
 int /*<<< orphan*/  ptydev_cdevsw ; 

__attribute__((used)) static void
pty_clone(void *arg, struct ucred *cr, char *name, int namelen,
    struct cdev **dev)
{
	struct make_dev_args mda;
	int error;

	/* Cloning is already satisfied. */
	if (*dev != NULL)
		return;

	/* Only catch /dev/ptyXX. */
	if (namelen != 5 || bcmp(name, "pty", 3) != 0)
		return;

	/* Only catch /dev/pty[l-sL-S]X. */
	if (!(name[3] >= 'l' && name[3] <= 's') &&
	    !(name[3] >= 'L' && name[3] <= 'S'))
		return;

	/* Only catch /dev/pty[l-sL-S][0-9a-v]. */
	if (!(name[4] >= '0' && name[4] <= '9') &&
	    !(name[4] >= 'a' && name[4] <= 'v'))
		return;

	/* Create the controller device node. */
	make_dev_args_init(&mda);
	mda.mda_flags =  MAKEDEV_CHECKNAME | MAKEDEV_REF;
	mda.mda_devsw = &ptydev_cdevsw;
	mda.mda_uid = UID_ROOT;
	mda.mda_gid = GID_WHEEL;
	mda.mda_mode = 0666;
	error = make_dev_s(&mda, dev, "%s", name);
	if (error != 0)
		*dev = NULL;
}