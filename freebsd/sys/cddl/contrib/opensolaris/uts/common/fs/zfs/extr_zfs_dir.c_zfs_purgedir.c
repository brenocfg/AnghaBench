#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_11__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  z_sa_hdl; int /*<<< orphan*/  z_id; TYPE_2__* z_zfsvfs; } ;
typedef  TYPE_1__ znode_t ;
struct TYPE_17__ {int /*<<< orphan*/  z_unlinkedobj; int /*<<< orphan*/  z_os; } ;
typedef  TYPE_2__ zfsvfs_t ;
typedef  int /*<<< orphan*/  zap_cursor_t ;
struct TYPE_18__ {int /*<<< orphan*/ * za_name; int /*<<< orphan*/  za_first_integer; } ;
typedef  TYPE_3__ zap_attribute_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_15__ {scalar_t__ v_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int ENOENT ; 
 int /*<<< orphan*/  FALSE ; 
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 int /*<<< orphan*/  TXG_WAIT ; 
 scalar_t__ VLNK ; 
 scalar_t__ VREG ; 
 int /*<<< orphan*/  ZFS_DIRENT_OBJ (int /*<<< orphan*/ ) ; 
 TYPE_11__* ZTOV (TYPE_1__*) ; 
 int /*<<< orphan*/  dmu_tx_abort (int /*<<< orphan*/ *) ; 
 int dmu_tx_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmu_tx_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_hold_sa (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_hold_zap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_tx_mark_netfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vn_lock (TYPE_11__*,int) ; 
 int /*<<< orphan*/  vput (TYPE_11__*) ; 
 int /*<<< orphan*/  zap_cursor_advance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int zap_cursor_retrieve (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int zfs_link_destroy (TYPE_1__*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_sa_upgrade_txholds (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int zfs_zget (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__**) ; 

__attribute__((used)) static int
zfs_purgedir(znode_t *dzp)
{
	zap_cursor_t	zc;
	zap_attribute_t	zap;
	znode_t		*xzp;
	dmu_tx_t	*tx;
	zfsvfs_t	*zfsvfs = dzp->z_zfsvfs;
	int skipped = 0;
	int error;

	for (zap_cursor_init(&zc, zfsvfs->z_os, dzp->z_id);
	    (error = zap_cursor_retrieve(&zc, &zap)) == 0;
	    zap_cursor_advance(&zc)) {
		error = zfs_zget(zfsvfs,
		    ZFS_DIRENT_OBJ(zap.za_first_integer), &xzp);
		if (error) {
			skipped += 1;
			continue;
		}

		vn_lock(ZTOV(xzp), LK_EXCLUSIVE | LK_RETRY);
		ASSERT((ZTOV(xzp)->v_type == VREG) ||
		    (ZTOV(xzp)->v_type == VLNK));

		tx = dmu_tx_create(zfsvfs->z_os);
		dmu_tx_hold_sa(tx, dzp->z_sa_hdl, B_FALSE);
		dmu_tx_hold_zap(tx, dzp->z_id, FALSE, zap.za_name);
		dmu_tx_hold_sa(tx, xzp->z_sa_hdl, B_FALSE);
		dmu_tx_hold_zap(tx, zfsvfs->z_unlinkedobj, FALSE, NULL);
		/* Is this really needed ? */
		zfs_sa_upgrade_txholds(tx, xzp);
		dmu_tx_mark_netfree(tx);
		error = dmu_tx_assign(tx, TXG_WAIT);
		if (error) {
			dmu_tx_abort(tx);
			vput(ZTOV(xzp));
			skipped += 1;
			continue;
		}

		error = zfs_link_destroy(dzp, zap.za_name, xzp, tx, 0, NULL);
		if (error)
			skipped += 1;
		dmu_tx_commit(tx);

		vput(ZTOV(xzp));
	}
	zap_cursor_fini(&zc);
	if (error != ENOENT)
		skipped += 1;
	return (skipped);
}