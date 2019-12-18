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
typedef  int /*<<< orphan*/  uintmax_t ;
struct clonedevs {int /*<<< orphan*/  head; } ;
struct cdev_priv {int cdp_flags; } ;
struct cdev {int si_flags; int /*<<< orphan*/  si_name; } ;

/* Variables and functions */
 int CDP_SCHED_DTR ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 struct cdev* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct cdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int SI_CLONELIST ; 
 int SI_NAMED ; 
 struct cdev_priv* cdev2priv (struct cdev*) ; 
 int /*<<< orphan*/  destroy_devl (struct cdev*) ; 
 scalar_t__ dev2udev (struct cdev*) ; 
 int /*<<< orphan*/  dev2unit (struct cdev*) ; 
 int /*<<< orphan*/  dev_lock () ; 
 int /*<<< orphan*/  dev_unlock_and_free () ; 
 int /*<<< orphan*/  free (struct clonedevs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  si_clone ; 

void
clone_cleanup(struct clonedevs **cdp)
{
	struct cdev *dev;
	struct cdev_priv *cp;
	struct clonedevs *cd;
	
	cd = *cdp;
	if (cd == NULL)
		return;
	dev_lock();
	while (!LIST_EMPTY(&cd->head)) {
		dev = LIST_FIRST(&cd->head);
		LIST_REMOVE(dev, si_clone);
		KASSERT(dev->si_flags & SI_CLONELIST,
		    ("Dev %p(%s) should be on clonelist", dev, dev->si_name));
		dev->si_flags &= ~SI_CLONELIST;
		cp = cdev2priv(dev);
		if (!(cp->cdp_flags & CDP_SCHED_DTR)) {
			cp->cdp_flags |= CDP_SCHED_DTR;
			KASSERT(dev->si_flags & SI_NAMED,
				("Driver has goofed in cloning underways udev %jx unit %x",
				(uintmax_t)dev2udev(dev), dev2unit(dev)));
			destroy_devl(dev);
		}
	}
	dev_unlock_and_free();
	free(cd, M_DEVBUF);
	*cdp = NULL;
}