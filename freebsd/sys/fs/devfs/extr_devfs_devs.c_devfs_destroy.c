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
struct cdev_priv {int /*<<< orphan*/  cdp_flags; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDP_ACTIVE ; 
 int /*<<< orphan*/  MA_OWNED ; 
 struct cdev_priv* cdev2priv (struct cdev*) ; 
 int /*<<< orphan*/  devfs_generation ; 
 int /*<<< orphan*/  devmtx ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
devfs_destroy(struct cdev *dev)
{
	struct cdev_priv *cdp;

	mtx_assert(&devmtx, MA_OWNED);
	cdp = cdev2priv(dev);
	cdp->cdp_flags &= ~CDP_ACTIVE;
	devfs_generation++;
}