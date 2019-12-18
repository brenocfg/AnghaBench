#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_17__ ;

/* Type definitions */
struct TYPE_26__ {int /*<<< orphan*/  z_sa_hdl; scalar_t__ z_id; TYPE_2__* z_zfsvfs; } ;
typedef  TYPE_1__ znode_t ;
typedef  int /*<<< orphan*/  zilog_t ;
struct TYPE_27__ {TYPE_17__* z_os; scalar_t__ z_unlinkedobj; int /*<<< orphan*/ * z_log; } ;
typedef  TYPE_2__ zfsvfs_t ;
typedef  int /*<<< orphan*/  xattr_obj ;
struct TYPE_28__ {scalar_t__ v_type; int /*<<< orphan*/  v_vflag; } ;
typedef  TYPE_3__ vnode_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int /*<<< orphan*/  cred_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_25__ {scalar_t__ os_sync; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT0 (int) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  EPERM ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SA_ZPL_XATTR (TYPE_2__*) ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TXG_WAIT ; 
 scalar_t__ TX_REMOVE ; 
 scalar_t__ VDIR ; 
 TYPE_1__* VTOZ (TYPE_3__*) ; 
 int /*<<< orphan*/  VV_NOSYNC ; 
 int /*<<< orphan*/  ZEXISTS ; 
 int /*<<< orphan*/  ZFS_ENTER (TYPE_2__*) ; 
 int /*<<< orphan*/  ZFS_EXIT (TYPE_2__*) ; 
 scalar_t__ ZFS_SYNC_ALWAYS ; 
 int /*<<< orphan*/  ZFS_VERIFY_ZP (TYPE_1__*) ; 
 int /*<<< orphan*/  ZTOV (TYPE_1__*) ; 
 int /*<<< orphan*/  ct ; 
 int /*<<< orphan*/  dmu_tx_abort (int /*<<< orphan*/ *) ; 
 int dmu_tx_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmu_tx_create (TYPE_17__*) ; 
 int /*<<< orphan*/  dmu_tx_hold_sa (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_hold_zap (int /*<<< orphan*/ *,scalar_t__,scalar_t__,char*) ; 
 int /*<<< orphan*/  dmu_tx_mark_netfree (int /*<<< orphan*/ *) ; 
 int sa_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  vnevent_remove (TYPE_3__*,TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vrele (int /*<<< orphan*/ ) ; 
 int zfs_link_destroy (TYPE_1__*,char*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  zfs_log_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,TYPE_1__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  zfs_sa_upgrade_txholds (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  zfs_unlinked_add (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int zfs_zaccess_delete (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int zfs_zget (TYPE_2__*,scalar_t__,TYPE_1__**) ; 
 int /*<<< orphan*/  zil_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_remove(vnode_t *dvp, vnode_t *vp, char *name, cred_t *cr)
{
	znode_t		*dzp = VTOZ(dvp);
	znode_t		*zp = VTOZ(vp);
	znode_t		*xzp;
	zfsvfs_t	*zfsvfs = dzp->z_zfsvfs;
	zilog_t		*zilog;
	uint64_t	acl_obj, xattr_obj;
	uint64_t	obj = 0;
	dmu_tx_t	*tx;
	boolean_t	unlinked, toobig = FALSE;
	uint64_t	txtype;
	int		error;

	ZFS_ENTER(zfsvfs);
	ZFS_VERIFY_ZP(dzp);
	ZFS_VERIFY_ZP(zp);
	zilog = zfsvfs->z_log;
	zp = VTOZ(vp);

	xattr_obj = 0;
	xzp = NULL;

	if (error = zfs_zaccess_delete(dzp, zp, cr)) {
		goto out;
	}

	/*
	 * Need to use rmdir for removing directories.
	 */
	if (vp->v_type == VDIR) {
		error = SET_ERROR(EPERM);
		goto out;
	}

	vnevent_remove(vp, dvp, name, ct);

	obj = zp->z_id;

	/* are there any extended attributes? */
	error = sa_lookup(zp->z_sa_hdl, SA_ZPL_XATTR(zfsvfs),
	    &xattr_obj, sizeof (xattr_obj));
	if (error == 0 && xattr_obj) {
		error = zfs_zget(zfsvfs, xattr_obj, &xzp);
		ASSERT0(error);
	}

	/*
	 * We may delete the znode now, or we may put it in the unlinked set;
	 * it depends on whether we're the last link, and on whether there are
	 * other holds on the vnode.  So we dmu_tx_hold() the right things to
	 * allow for either case.
	 */
	tx = dmu_tx_create(zfsvfs->z_os);
	dmu_tx_hold_zap(tx, dzp->z_id, FALSE, name);
	dmu_tx_hold_sa(tx, zp->z_sa_hdl, B_FALSE);
	zfs_sa_upgrade_txholds(tx, zp);
	zfs_sa_upgrade_txholds(tx, dzp);

	if (xzp) {
		dmu_tx_hold_sa(tx, zp->z_sa_hdl, B_TRUE);
		dmu_tx_hold_sa(tx, xzp->z_sa_hdl, B_FALSE);
	}

	/* charge as an update -- would be nice not to charge at all */
	dmu_tx_hold_zap(tx, zfsvfs->z_unlinkedobj, FALSE, NULL);

	/*
	 * Mark this transaction as typically resulting in a net free of space
	 */
	dmu_tx_mark_netfree(tx);

	error = dmu_tx_assign(tx, TXG_WAIT);
	if (error) {
		dmu_tx_abort(tx);
		ZFS_EXIT(zfsvfs);
		return (error);
	}

	/*
	 * Remove the directory entry.
	 */
	error = zfs_link_destroy(dzp, name, zp, tx, ZEXISTS, &unlinked);

	if (error) {
		dmu_tx_commit(tx);
		goto out;
	}

	if (unlinked) {
		zfs_unlinked_add(zp, tx);
		vp->v_vflag |= VV_NOSYNC;
	}

	txtype = TX_REMOVE;
	zfs_log_remove(zilog, tx, txtype, dzp, name, obj);

	dmu_tx_commit(tx);
out:

	if (xzp)
		vrele(ZTOV(xzp));

	if (zfsvfs->z_os->os_sync == ZFS_SYNC_ALWAYS)
		zil_commit(zilog, 0);

	ZFS_EXIT(zfsvfs);
	return (error);
}