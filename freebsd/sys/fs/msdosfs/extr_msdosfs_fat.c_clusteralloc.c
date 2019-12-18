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
 int /*<<< orphan*/  MSDOSFS_LOCK_MP (struct msdosfsmount*) ; 
 int /*<<< orphan*/  MSDOSFS_UNLOCK_MP (struct msdosfsmount*) ; 
 int clusteralloc1 (struct msdosfsmount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
clusteralloc(struct msdosfsmount *pmp, u_long start, u_long count,
    u_long fillwith, u_long *retcluster, u_long *got)
{
	int error;

	MSDOSFS_LOCK_MP(pmp);
	error = clusteralloc1(pmp, start, count, fillwith, retcluster, got);
	MSDOSFS_UNLOCK_MP(pmp);
	return (error);
}