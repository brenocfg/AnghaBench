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
struct cdev {scalar_t__ si_refcount; int /*<<< orphan*/ * si_devsw; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct cdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int /*<<< orphan*/  dev_lock () ; 
 int /*<<< orphan*/  dev_unlock () ; 
 int /*<<< orphan*/  devfs_free (struct cdev*) ; 
 int /*<<< orphan*/  devmtx ; 
 int /*<<< orphan*/  devtoname (struct cdev*) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  si_list ; 

void
dev_rel(struct cdev *dev)
{
	int flag = 0;

	mtx_assert(&devmtx, MA_NOTOWNED);
	dev_lock();
	dev->si_refcount--;
	KASSERT(dev->si_refcount >= 0,
	    ("dev_rel(%s) gave negative count", devtoname(dev)));
	if (dev->si_devsw == NULL && dev->si_refcount == 0) {
		LIST_REMOVE(dev, si_list);
		flag = 1;
	}
	dev_unlock();
	if (flag)
		devfs_free(dev);
}