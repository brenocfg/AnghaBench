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
typedef  int /*<<< orphan*/  va_list ;
struct cdev {int /*<<< orphan*/  si_flags; int /*<<< orphan*/  si_name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MAKEDEV_CHECKNAME ; 
 int MAKEDEV_NOWAIT ; 
 int MAKEDEV_WAITOK ; 
 int /*<<< orphan*/  SI_ALIAS ; 
 int /*<<< orphan*/  SI_NAMED ; 
 int /*<<< orphan*/  clean_unrhdrl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dependsl (struct cdev*,struct cdev*) ; 
 int /*<<< orphan*/  dev_lock () ; 
 int /*<<< orphan*/  dev_unlock () ; 
 struct cdev* devfs_alloc (int) ; 
 int /*<<< orphan*/  devfs_create (struct cdev*) ; 
 int /*<<< orphan*/  devfs_free (struct cdev*) ; 
 int /*<<< orphan*/  devfs_inos ; 
 int /*<<< orphan*/  notify_create (struct cdev*,int) ; 
 int /*<<< orphan*/  panic (char*,int,int /*<<< orphan*/ ) ; 
 int prep_devname (struct cdev*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
make_dev_alias_v(int flags, struct cdev **cdev, struct cdev *pdev,
    const char *fmt, va_list ap)
{
	struct cdev *dev;
	int error;

	KASSERT(pdev != NULL, ("make_dev_alias_v: pdev is NULL"));
	KASSERT((flags & MAKEDEV_WAITOK) == 0 || (flags & MAKEDEV_NOWAIT) == 0,
	    ("make_dev_alias_v: both WAITOK and NOWAIT specified"));
	KASSERT((flags & ~(MAKEDEV_WAITOK | MAKEDEV_NOWAIT |
	    MAKEDEV_CHECKNAME)) == 0,
	    ("make_dev_alias_v: invalid flags specified (flags=%02x)", flags));

	dev = devfs_alloc(flags);
	if (dev == NULL)
		return (ENOMEM);
	dev_lock();
	dev->si_flags |= SI_ALIAS;
	error = prep_devname(dev, fmt, ap);
	if (error != 0) {
		if ((flags & MAKEDEV_CHECKNAME) == 0) {
			panic("make_dev_alias_v: bad si_name "
			    "(error=%d, si_name=%s)", error, dev->si_name);
		}
		dev_unlock();
		devfs_free(dev);
		return (error);
	}
	dev->si_flags |= SI_NAMED;
	devfs_create(dev);
	dev_dependsl(pdev, dev);
	clean_unrhdrl(devfs_inos);
	dev_unlock();

	notify_create(dev, flags);
	*cdev = dev;

	return (0);
}