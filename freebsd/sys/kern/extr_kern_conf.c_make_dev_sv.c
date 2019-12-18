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
typedef  int /*<<< orphan*/  va_list ;
struct make_dev_args {int mda_size; int mda_flags; int /*<<< orphan*/  mda_mode; int /*<<< orphan*/  mda_gid; int /*<<< orphan*/  mda_uid; int /*<<< orphan*/ * mda_cr; TYPE_1__* mda_devsw; } ;
struct cdev {int si_flags; int /*<<< orphan*/  si_mode; int /*<<< orphan*/  si_gid; int /*<<< orphan*/  si_uid; int /*<<< orphan*/  si_cred; int /*<<< orphan*/  si_name; } ;
typedef  int /*<<< orphan*/  args ;
struct TYPE_2__ {int /*<<< orphan*/  d_name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct cdev*,int /*<<< orphan*/ ) ; 
 int MAKEDEV_CHECKNAME ; 
 int MAKEDEV_ETERNAL ; 
 int MAKEDEV_NOWAIT ; 
 int MAKEDEV_REF ; 
 int MAKEDEV_WAITOK ; 
 int SI_ETERNAL ; 
 int SI_NAMED ; 
 int /*<<< orphan*/  bcopy (struct make_dev_args*,struct make_dev_args*,int) ; 
 int /*<<< orphan*/  bzero (struct make_dev_args*,int) ; 
 int /*<<< orphan*/  clean_unrhdrl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crhold (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev2unit (struct cdev*) ; 
 int /*<<< orphan*/  dev_lock () ; 
 int /*<<< orphan*/  dev_refl (struct cdev*) ; 
 int /*<<< orphan*/  dev_unlock () ; 
 int /*<<< orphan*/  dev_unlock_and_free () ; 
 struct cdev* devfs_alloc (int) ; 
 int /*<<< orphan*/  devfs_create (struct cdev*) ; 
 int /*<<< orphan*/  devfs_free (struct cdev*) ; 
 int /*<<< orphan*/  devfs_inos ; 
 int /*<<< orphan*/  devtoname (struct cdev*) ; 
 struct cdev* newdev (struct make_dev_args*,struct cdev*) ; 
 int /*<<< orphan*/  notify_create (struct cdev*,int) ; 
 int /*<<< orphan*/  panic (char*,int,int /*<<< orphan*/ ) ; 
 int prep_cdevsw (TYPE_1__*,int) ; 
 int prep_devname (struct cdev*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  si_list ; 

__attribute__((used)) static int
make_dev_sv(struct make_dev_args *args1, struct cdev **dres,
    const char *fmt, va_list ap)
{
	struct cdev *dev, *dev_new;
	struct make_dev_args args;
	int res;

	bzero(&args, sizeof(args));
	if (sizeof(args) < args1->mda_size)
		return (EINVAL);
	bcopy(args1, &args, args1->mda_size);
	KASSERT((args.mda_flags & MAKEDEV_WAITOK) == 0 ||
	    (args.mda_flags & MAKEDEV_NOWAIT) == 0,
	    ("make_dev_sv: both WAITOK and NOWAIT specified"));
	dev_new = devfs_alloc(args.mda_flags);
	if (dev_new == NULL)
		return (ENOMEM);
	dev_lock();
	res = prep_cdevsw(args.mda_devsw, args.mda_flags);
	if (res != 0) {
		dev_unlock();
		devfs_free(dev_new);
		return (res);
	}
	dev = newdev(&args, dev_new);
	if ((dev->si_flags & SI_NAMED) == 0) {
		res = prep_devname(dev, fmt, ap);
		if (res != 0) {
			if ((args.mda_flags & MAKEDEV_CHECKNAME) == 0) {
				panic(
			"make_dev_sv: bad si_name (error=%d, si_name=%s)",
				    res, dev->si_name);
			}
			if (dev == dev_new) {
				LIST_REMOVE(dev, si_list);
				dev_unlock();
				devfs_free(dev);
			} else
				dev_unlock();
			return (res);
		}
	}
	if ((args.mda_flags & MAKEDEV_REF) != 0)
		dev_refl(dev);
	if ((args.mda_flags & MAKEDEV_ETERNAL) != 0)
		dev->si_flags |= SI_ETERNAL;
	KASSERT(!(dev->si_flags & SI_NAMED),
	    ("make_dev() by driver %s on pre-existing device (min=%x, name=%s)",
	    args.mda_devsw->d_name, dev2unit(dev), devtoname(dev)));
	dev->si_flags |= SI_NAMED;
	if (args.mda_cr != NULL)
		dev->si_cred = crhold(args.mda_cr);
	dev->si_uid = args.mda_uid;
	dev->si_gid = args.mda_gid;
	dev->si_mode = args.mda_mode;

	devfs_create(dev);
	clean_unrhdrl(devfs_inos);
	dev_unlock_and_free();

	notify_create(dev, args.mda_flags);

	*dres = dev;
	return (0);
}