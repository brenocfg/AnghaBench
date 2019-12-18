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
struct cdev_priv {scalar_t__ cdp_maxdirent; struct cdev_priv* cdp_dirents; int /*<<< orphan*/  cdp_inode; } ;
struct cdev {int /*<<< orphan*/ * si_cred; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_CDEVP ; 
 int /*<<< orphan*/  M_DEVFS2 ; 
 struct cdev_priv* cdev2priv (struct cdev*) ; 
 int /*<<< orphan*/  crfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devfs_free_cdp_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct cdev_priv*,int /*<<< orphan*/ ) ; 

void
devfs_free(struct cdev *cdev)
{
	struct cdev_priv *cdp;

	cdp = cdev2priv(cdev);
	if (cdev->si_cred != NULL)
		crfree(cdev->si_cred);
	devfs_free_cdp_inode(cdp->cdp_inode);
	if (cdp->cdp_maxdirent > 0) 
		free(cdp->cdp_dirents, M_DEVFS2);
	free(cdp, M_CDEVP);
}