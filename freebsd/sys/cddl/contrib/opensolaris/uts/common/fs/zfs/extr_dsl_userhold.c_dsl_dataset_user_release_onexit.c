#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ zhca_spa_load_guid; int /*<<< orphan*/  zhca_holds; int /*<<< orphan*/  zhca_spaname; } ;
typedef  TYPE_1__ zfs_hold_cleanup_arg_t ;
typedef  int /*<<< orphan*/  spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  dsl_dataset_user_release_tmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  spa_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_get_dsl (int /*<<< orphan*/ *) ; 
 scalar_t__ spa_load_guid (int /*<<< orphan*/ *) ; 
 int spa_open (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_dbgmsg (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dsl_dataset_user_release_onexit(void *arg)
{
	zfs_hold_cleanup_arg_t *ca = arg;
	spa_t *spa;
	int error;

	error = spa_open(ca->zhca_spaname, &spa, FTAG);
	if (error != 0) {
		zfs_dbgmsg("couldn't release holds on pool=%s "
		    "because pool is no longer loaded",
		    ca->zhca_spaname);
		return;
	}
	if (spa_load_guid(spa) != ca->zhca_spa_load_guid) {
		zfs_dbgmsg("couldn't release holds on pool=%s "
		    "because pool is no longer loaded (guid doesn't match)",
		    ca->zhca_spaname);
		spa_close(spa, FTAG);
		return;
	}

	(void) dsl_dataset_user_release_tmp(spa_get_dsl(spa), ca->zhca_holds);
	fnvlist_free(ca->zhca_holds);
	kmem_free(ca, sizeof (zfs_hold_cleanup_arg_t));
	spa_close(spa, FTAG);
}