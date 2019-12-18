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
struct cdev_priv {int cdp_flags; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int CDP_UNREF_DTR ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct cdev_priv*,int /*<<< orphan*/ ) ; 
 struct cdev_priv* cdev2priv (struct cdev*) ; 
 int /*<<< orphan*/  cdevp_free_list ; 
 int /*<<< orphan*/  cdp_list ; 
 int /*<<< orphan*/  devmtx ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dev_free_devlocked(struct cdev *cdev)
{
	struct cdev_priv *cdp;

	mtx_assert(&devmtx, MA_OWNED);
	cdp = cdev2priv(cdev);
	KASSERT((cdp->cdp_flags & CDP_UNREF_DTR) == 0,
	    ("destroy_dev() was not called after delist_dev(%p)", cdev));
	TAILQ_INSERT_HEAD(&cdevp_free_list, cdp, cdp_list);
}