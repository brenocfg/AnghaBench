#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ z_links; int /*<<< orphan*/  z_unlinked; int /*<<< orphan*/  z_sa_hdl; } ;
typedef  TYPE_1__ znode_t ;
struct TYPE_13__ {int /*<<< orphan*/  z_os; int /*<<< orphan*/  z_unlinkedobj; } ;
typedef  TYPE_2__ zfsvfs_t ;
typedef  int /*<<< orphan*/  zap_cursor_t ;
struct TYPE_14__ {int /*<<< orphan*/  za_first_integer; } ;
typedef  TYPE_3__ zap_attribute_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_15__ {scalar_t__ doi_type; } ;
typedef  TYPE_4__ dmu_object_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 scalar_t__ DMU_OT_DIRECTORY_CONTENTS ; 
 scalar_t__ DMU_OT_PLAIN_FILE_CONTENTS ; 
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 int /*<<< orphan*/  SA_ZPL_LINKS (TYPE_2__*) ; 
 int /*<<< orphan*/  TXG_WAIT ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZTOV (TYPE_1__*) ; 
 int dmu_object_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  dmu_tx_abort (int /*<<< orphan*/ *) ; 
 int dmu_tx_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmu_tx_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_hold_sa (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sa_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vn_lock (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zap_cursor_advance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zap_cursor_retrieve (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int zfs_zget (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__**) ; 

void
zfs_unlinked_drain(zfsvfs_t *zfsvfs)
{
	zap_cursor_t	zc;
	zap_attribute_t zap;
	dmu_object_info_t doi;
	znode_t		*zp;
	dmu_tx_t	*tx;
	int		error;

	/*
	 * Interate over the contents of the unlinked set.
	 */
	for (zap_cursor_init(&zc, zfsvfs->z_os, zfsvfs->z_unlinkedobj);
	    zap_cursor_retrieve(&zc, &zap) == 0;
	    zap_cursor_advance(&zc)) {

		/*
		 * See what kind of object we have in list
		 */

		error = dmu_object_info(zfsvfs->z_os,
		    zap.za_first_integer, &doi);
		if (error != 0)
			continue;

		ASSERT((doi.doi_type == DMU_OT_PLAIN_FILE_CONTENTS) ||
		    (doi.doi_type == DMU_OT_DIRECTORY_CONTENTS));
		/*
		 * We need to re-mark these list entries for deletion,
		 * so we pull them back into core and set zp->z_unlinked.
		 */
		error = zfs_zget(zfsvfs, zap.za_first_integer, &zp);

		/*
		 * We may pick up znodes that are already marked for deletion.
		 * This could happen during the purge of an extended attribute
		 * directory.  All we need to do is skip over them, since they
		 * are already in the system marked z_unlinked.
		 */
		if (error != 0)
			continue;

		vn_lock(ZTOV(zp), LK_EXCLUSIVE | LK_RETRY);
#if defined(__FreeBSD__)
		/*
		 * Due to changes in zfs_rmnode we need to make sure the
		 * link count is set to zero here.
		 */
		if (zp->z_links != 0) {
			tx = dmu_tx_create(zfsvfs->z_os);
			dmu_tx_hold_sa(tx, zp->z_sa_hdl, B_FALSE);
			error = dmu_tx_assign(tx, TXG_WAIT);
			if (error != 0) {
				dmu_tx_abort(tx);
				vput(ZTOV(zp));
				continue;
			}
			zp->z_links = 0;
			VERIFY0(sa_update(zp->z_sa_hdl, SA_ZPL_LINKS(zfsvfs),
			    &zp->z_links, sizeof (zp->z_links), tx));
			dmu_tx_commit(tx);
		}
#endif
		zp->z_unlinked = B_TRUE;
		vput(ZTOV(zp));
	}
	zap_cursor_fini(&zc);
}