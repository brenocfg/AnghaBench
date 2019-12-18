#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_17__ ;

/* Type definitions */
struct TYPE_25__ {int z_pflags; int /*<<< orphan*/  z_id; int /*<<< orphan*/  z_sa_hdl; int /*<<< orphan*/  z_uid; TYPE_2__* z_zfsvfs; } ;
typedef  TYPE_1__ znode_t ;
typedef  int /*<<< orphan*/  zilog_t ;
struct TYPE_26__ {scalar_t__ z_shares_dir; TYPE_17__* z_os; scalar_t__ z_utf8; int /*<<< orphan*/ * z_log; } ;
typedef  TYPE_2__ zfsvfs_t ;
struct TYPE_27__ {scalar_t__ v_type; } ;
typedef  TYPE_3__ vnode_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uid_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int /*<<< orphan*/  cred_t ;
typedef  int /*<<< orphan*/  caller_context_t ;
struct TYPE_24__ {scalar_t__ os_sync; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACE_ADD_FILE ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  EILSEQ ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EPERM ; 
 int /*<<< orphan*/  SA_ZPL_PARENT (TYPE_2__*) ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TXG_WAIT ; 
 scalar_t__ TX_LINK ; 
 int /*<<< orphan*/  U8_VALIDATE_ENTIRE ; 
 scalar_t__ VDIR ; 
 TYPE_1__* VTOZ (TYPE_3__*) ; 
 int ZFS_APPENDONLY ; 
 int /*<<< orphan*/  ZFS_ENTER (TYPE_2__*) ; 
 int /*<<< orphan*/  ZFS_EXIT (TYPE_2__*) ; 
 int ZFS_IMMUTABLE ; 
 int /*<<< orphan*/  ZFS_OWNER ; 
 int ZFS_READONLY ; 
 scalar_t__ ZFS_SYNC_ALWAYS ; 
 int /*<<< orphan*/  ZFS_VERIFY_ZP (TYPE_1__*) ; 
 int ZFS_XATTR ; 
 int /*<<< orphan*/  ZNEW ; 
 scalar_t__ crgetuid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_tx_abort (int /*<<< orphan*/ *) ; 
 int dmu_tx_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmu_tx_create (TYPE_17__*) ; 
 int /*<<< orphan*/  dmu_tx_hold_sa (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_hold_zap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int sa_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 scalar_t__ secpolicy_basic_link (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ u8_validate (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  vnevent_link (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int zfs_dirent_lookup (TYPE_1__*,char*,TYPE_1__**,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_fuid_map_id (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int zfs_link_create (TYPE_1__*,char*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_log_link (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,TYPE_1__*,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  zfs_sa_upgrade_txholds (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int zfs_zaccess (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zil_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_link(vnode_t *tdvp, vnode_t *svp, char *name, cred_t *cr,
    caller_context_t *ct, int flags)
{
	znode_t		*dzp = VTOZ(tdvp);
	znode_t		*tzp, *szp;
	zfsvfs_t	*zfsvfs = dzp->z_zfsvfs;
	zilog_t		*zilog;
	dmu_tx_t	*tx;
	int		error;
	uint64_t	parent;
	uid_t		owner;

	ASSERT(tdvp->v_type == VDIR);

	ZFS_ENTER(zfsvfs);
	ZFS_VERIFY_ZP(dzp);
	zilog = zfsvfs->z_log;

	/*
	 * POSIX dictates that we return EPERM here.
	 * Better choices include ENOTSUP or EISDIR.
	 */
	if (svp->v_type == VDIR) {
		ZFS_EXIT(zfsvfs);
		return (SET_ERROR(EPERM));
	}

	szp = VTOZ(svp);
	ZFS_VERIFY_ZP(szp);

	if (szp->z_pflags & (ZFS_APPENDONLY | ZFS_IMMUTABLE | ZFS_READONLY)) {
		ZFS_EXIT(zfsvfs);
		return (SET_ERROR(EPERM));
	}

	/* Prevent links to .zfs/shares files */

	if ((error = sa_lookup(szp->z_sa_hdl, SA_ZPL_PARENT(zfsvfs),
	    &parent, sizeof (uint64_t))) != 0) {
		ZFS_EXIT(zfsvfs);
		return (error);
	}
	if (parent == zfsvfs->z_shares_dir) {
		ZFS_EXIT(zfsvfs);
		return (SET_ERROR(EPERM));
	}

	if (zfsvfs->z_utf8 && u8_validate(name,
	    strlen(name), NULL, U8_VALIDATE_ENTIRE, &error) < 0) {
		ZFS_EXIT(zfsvfs);
		return (SET_ERROR(EILSEQ));
	}

	/*
	 * We do not support links between attributes and non-attributes
	 * because of the potential security risk of creating links
	 * into "normal" file space in order to circumvent restrictions
	 * imposed in attribute space.
	 */
	if ((szp->z_pflags & ZFS_XATTR) != (dzp->z_pflags & ZFS_XATTR)) {
		ZFS_EXIT(zfsvfs);
		return (SET_ERROR(EINVAL));
	}


	owner = zfs_fuid_map_id(zfsvfs, szp->z_uid, cr, ZFS_OWNER);
	if (owner != crgetuid(cr) && secpolicy_basic_link(svp, cr) != 0) {
		ZFS_EXIT(zfsvfs);
		return (SET_ERROR(EPERM));
	}

	if (error = zfs_zaccess(dzp, ACE_ADD_FILE, 0, B_FALSE, cr)) {
		ZFS_EXIT(zfsvfs);
		return (error);
	}

	/*
	 * Attempt to lock directory; fail if entry already exists.
	 */
	error = zfs_dirent_lookup(dzp, name, &tzp, ZNEW);
	if (error) {
		ZFS_EXIT(zfsvfs);
		return (error);
	}

	tx = dmu_tx_create(zfsvfs->z_os);
	dmu_tx_hold_sa(tx, szp->z_sa_hdl, B_FALSE);
	dmu_tx_hold_zap(tx, dzp->z_id, TRUE, name);
	zfs_sa_upgrade_txholds(tx, szp);
	zfs_sa_upgrade_txholds(tx, dzp);
	error = dmu_tx_assign(tx, TXG_WAIT);
	if (error) {
		dmu_tx_abort(tx);
		ZFS_EXIT(zfsvfs);
		return (error);
	}

	error = zfs_link_create(dzp, name, szp, tx, 0);

	if (error == 0) {
		uint64_t txtype = TX_LINK;
		zfs_log_link(zilog, tx, txtype, dzp, szp, name);
	}

	dmu_tx_commit(tx);

	if (error == 0) {
		vnevent_link(svp, ct);
	}

	if (zfsvfs->z_os->os_sync == ZFS_SYNC_ALWAYS)
		zil_commit(zilog, 0);

	ZFS_EXIT(zfsvfs);
	return (error);
}