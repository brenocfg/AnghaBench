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
struct free_cdevsw {int dummy; } ;
struct cdevsw {int dummy; } ;
struct cdev_priv_list {int dummy; } ;
struct cdev_priv {int /*<<< orphan*/  cdp_c; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  M_DEVT ; 
 struct cdevsw* SLIST_FIRST (struct free_cdevsw*) ; 
 int /*<<< orphan*/  SLIST_INIT (struct free_cdevsw*) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (struct free_cdevsw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_CONCAT (struct cdev_priv_list*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct cdev_priv* TAILQ_FIRST (struct cdev_priv_list*) ; 
 int /*<<< orphan*/  TAILQ_INIT (struct cdev_priv_list*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (struct cdev_priv_list*,struct cdev_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdevp_free_list ; 
 struct free_cdevsw cdevsw_gt_post_list ; 
 int /*<<< orphan*/  cdp_list ; 
 int /*<<< orphan*/  d_postfree_list ; 
 int /*<<< orphan*/  devfs_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devmtx ; 
 int /*<<< orphan*/  free (struct cdevsw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dev_unlock_and_free(void)
{
	struct cdev_priv_list cdp_free;
	struct free_cdevsw csw_free;
	struct cdev_priv *cdp;
	struct cdevsw *csw;

	mtx_assert(&devmtx, MA_OWNED);

	/*
	 * Make the local copy of the list heads while the dev_mtx is
	 * held. Free it later.
	 */
	TAILQ_INIT(&cdp_free);
	TAILQ_CONCAT(&cdp_free, &cdevp_free_list, cdp_list);
	csw_free = cdevsw_gt_post_list;
	SLIST_INIT(&cdevsw_gt_post_list);

	mtx_unlock(&devmtx);

	while ((cdp = TAILQ_FIRST(&cdp_free)) != NULL) {
		TAILQ_REMOVE(&cdp_free, cdp, cdp_list);
		devfs_free(&cdp->cdp_c);
	}
	while ((csw = SLIST_FIRST(&csw_free)) != NULL) {
		SLIST_REMOVE_HEAD(&csw_free, d_postfree_list);
		free(csw, M_DEVT);
	}
}