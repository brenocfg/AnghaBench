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
typedef  int /*<<< orphan*/  u_long ;
struct msdosfsmount {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAT_GET_AND_SET ; 
 int /*<<< orphan*/  MSDOSFSFREE ; 
 int /*<<< orphan*/  MSDOSFS_LOCK_MP (struct msdosfsmount*) ; 
 int /*<<< orphan*/  MSDOSFS_UNLOCK_MP (struct msdosfsmount*) ; 
 int fatentry (int /*<<< orphan*/ ,struct msdosfsmount*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usemap_free (struct msdosfsmount*,int /*<<< orphan*/ ) ; 

int
clusterfree(struct msdosfsmount *pmp, u_long cluster, u_long *oldcnp)
{
	int error;
	u_long oldcn;

	error = fatentry(FAT_GET_AND_SET, pmp, cluster, &oldcn, MSDOSFSFREE);
	if (error)
		return (error);
	/*
	 * If the cluster was successfully marked free, then update
	 * the count of free clusters, and turn off the "allocated"
	 * bit in the "in use" cluster bit map.
	 */
	MSDOSFS_LOCK_MP(pmp);
	usemap_free(pmp, cluster);
	MSDOSFS_UNLOCK_MP(pmp);
	if (oldcnp)
		*oldcnp = oldcn;
	return (0);
}