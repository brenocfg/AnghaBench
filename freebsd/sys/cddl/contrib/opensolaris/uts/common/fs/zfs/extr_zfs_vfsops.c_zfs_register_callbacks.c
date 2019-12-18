#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int /*<<< orphan*/ * z_os; struct TYPE_21__* vfs_data; } ;
typedef  TYPE_1__ zfsvfs_t ;
typedef  TYPE_1__ vfs_t ;
typedef  void* uint64_t ;
struct dsl_dataset {int dummy; } ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  void* boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_1__*) ; 
 void* B_FALSE ; 
 void* B_TRUE ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  MNTOPT_ATIME ; 
 int /*<<< orphan*/  MNTOPT_EXEC ; 
 int /*<<< orphan*/  MNTOPT_NBMAND ; 
 int /*<<< orphan*/  MNTOPT_NOATIME ; 
 int /*<<< orphan*/  MNTOPT_NOEXEC ; 
 int /*<<< orphan*/  MNTOPT_NONBMAND ; 
 int /*<<< orphan*/  MNTOPT_NOSETUID ; 
 int /*<<< orphan*/  MNTOPT_NOSUID ; 
 int /*<<< orphan*/  MNTOPT_NOXATTR ; 
 int /*<<< orphan*/  MNTOPT_RO ; 
 int /*<<< orphan*/  MNTOPT_RW ; 
 int /*<<< orphan*/  MNTOPT_SETUID ; 
 int /*<<< orphan*/  MNTOPT_XATTR ; 
 int /*<<< orphan*/  ZFS_PROP_ACLINHERIT ; 
 int /*<<< orphan*/  ZFS_PROP_ACLMODE ; 
 int /*<<< orphan*/  ZFS_PROP_ATIME ; 
 int /*<<< orphan*/  ZFS_PROP_DEVICES ; 
 int /*<<< orphan*/  ZFS_PROP_EXEC ; 
 int /*<<< orphan*/  ZFS_PROP_READONLY ; 
 int /*<<< orphan*/  ZFS_PROP_RECORDSIZE ; 
 int /*<<< orphan*/  ZFS_PROP_SETUID ; 
 int /*<<< orphan*/  ZFS_PROP_SNAPDIR ; 
 int /*<<< orphan*/  ZFS_PROP_VSCAN ; 
 int /*<<< orphan*/  ZFS_PROP_XATTR ; 
 int /*<<< orphan*/  acl_inherit_changed_cb (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  acl_mode_changed_cb (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  atime_changed_cb (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  blksz_changed_cb (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  devices_changed_cb (TYPE_1__*,void*) ; 
 struct dsl_dataset* dmu_objset_ds (int /*<<< orphan*/ *) ; 
 scalar_t__ dmu_objset_is_snapshot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_objset_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_objset_spa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_pool_config_enter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_pool_config_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dsl_prop_get_int_ds (struct dsl_dataset*,char*,void**) ; 
 int dsl_prop_register (struct dsl_dataset*,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (TYPE_1__*,void*),TYPE_1__*) ; 
 int /*<<< orphan*/  dsl_prop_unregister_all (struct dsl_dataset*,TYPE_1__*) ; 
 int /*<<< orphan*/  exec_changed_cb (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  nbmand_changed_cb (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  readonly_changed_cb (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  setuid_changed_cb (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  snapdir_changed_cb (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  spa_writeable (int /*<<< orphan*/ ) ; 
 scalar_t__ vfs_optionisset (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vscan_changed_cb (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  xattr_changed_cb (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  zfs_prop_to_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_register_callbacks(vfs_t *vfsp)
{
	struct dsl_dataset *ds = NULL;
	objset_t *os = NULL;
	zfsvfs_t *zfsvfs = NULL;
	uint64_t nbmand;
	boolean_t readonly = B_FALSE;
	boolean_t do_readonly = B_FALSE;
	boolean_t setuid = B_FALSE;
	boolean_t do_setuid = B_FALSE;
	boolean_t exec = B_FALSE;
	boolean_t do_exec = B_FALSE;
#ifdef illumos
	boolean_t devices = B_FALSE;
	boolean_t do_devices = B_FALSE;
#endif
	boolean_t xattr = B_FALSE;
	boolean_t do_xattr = B_FALSE;
	boolean_t atime = B_FALSE;
	boolean_t do_atime = B_FALSE;
	int error = 0;

	ASSERT(vfsp);
	zfsvfs = vfsp->vfs_data;
	ASSERT(zfsvfs);
	os = zfsvfs->z_os;

	/*
	 * This function can be called for a snapshot when we update snapshot's
	 * mount point, which isn't really supported.
	 */
	if (dmu_objset_is_snapshot(os))
		return (EOPNOTSUPP);

	/*
	 * The act of registering our callbacks will destroy any mount
	 * options we may have.  In order to enable temporary overrides
	 * of mount options, we stash away the current values and
	 * restore them after we register the callbacks.
	 */
	if (vfs_optionisset(vfsp, MNTOPT_RO, NULL) ||
	    !spa_writeable(dmu_objset_spa(os))) {
		readonly = B_TRUE;
		do_readonly = B_TRUE;
	} else if (vfs_optionisset(vfsp, MNTOPT_RW, NULL)) {
		readonly = B_FALSE;
		do_readonly = B_TRUE;
	}
	if (vfs_optionisset(vfsp, MNTOPT_NOSUID, NULL)) {
		setuid = B_FALSE;
		do_setuid = B_TRUE;
	} else {
		if (vfs_optionisset(vfsp, MNTOPT_NOSETUID, NULL)) {
			setuid = B_FALSE;
			do_setuid = B_TRUE;
		} else if (vfs_optionisset(vfsp, MNTOPT_SETUID, NULL)) {
			setuid = B_TRUE;
			do_setuid = B_TRUE;
		}
	}
	if (vfs_optionisset(vfsp, MNTOPT_NOEXEC, NULL)) {
		exec = B_FALSE;
		do_exec = B_TRUE;
	} else if (vfs_optionisset(vfsp, MNTOPT_EXEC, NULL)) {
		exec = B_TRUE;
		do_exec = B_TRUE;
	}
	if (vfs_optionisset(vfsp, MNTOPT_NOXATTR, NULL)) {
		xattr = B_FALSE;
		do_xattr = B_TRUE;
	} else if (vfs_optionisset(vfsp, MNTOPT_XATTR, NULL)) {
		xattr = B_TRUE;
		do_xattr = B_TRUE;
	}
	if (vfs_optionisset(vfsp, MNTOPT_NOATIME, NULL)) {
		atime = B_FALSE;
		do_atime = B_TRUE;
	} else if (vfs_optionisset(vfsp, MNTOPT_ATIME, NULL)) {
		atime = B_TRUE;
		do_atime = B_TRUE;
	}

	/*
	 * We need to enter pool configuration here, so that we can use
	 * dsl_prop_get_int_ds() to handle the special nbmand property below.
	 * dsl_prop_get_integer() can not be used, because it has to acquire
	 * spa_namespace_lock and we can not do that because we already hold
	 * z_teardown_lock.  The problem is that spa_write_cachefile() is called
	 * with spa_namespace_lock held and the function calls ZFS vnode
	 * operations to write the cache file and thus z_teardown_lock is
	 * acquired after spa_namespace_lock.
	 */
	ds = dmu_objset_ds(os);
	dsl_pool_config_enter(dmu_objset_pool(os), FTAG);

	/*
	 * nbmand is a special property.  It can only be changed at
	 * mount time.
	 *
	 * This is weird, but it is documented to only be changeable
	 * at mount time.
	 */
	if (vfs_optionisset(vfsp, MNTOPT_NONBMAND, NULL)) {
		nbmand = B_FALSE;
	} else if (vfs_optionisset(vfsp, MNTOPT_NBMAND, NULL)) {
		nbmand = B_TRUE;
	} else if (error = dsl_prop_get_int_ds(ds, "nbmand", &nbmand) != 0) {
		dsl_pool_config_exit(dmu_objset_pool(os), FTAG);
		return (error);
	}

	/*
	 * Register property callbacks.
	 *
	 * It would probably be fine to just check for i/o error from
	 * the first prop_register(), but I guess I like to go
	 * overboard...
	 */
	error = dsl_prop_register(ds,
	    zfs_prop_to_name(ZFS_PROP_ATIME), atime_changed_cb, zfsvfs);
	error = error ? error : dsl_prop_register(ds,
	    zfs_prop_to_name(ZFS_PROP_XATTR), xattr_changed_cb, zfsvfs);
	error = error ? error : dsl_prop_register(ds,
	    zfs_prop_to_name(ZFS_PROP_RECORDSIZE), blksz_changed_cb, zfsvfs);
	error = error ? error : dsl_prop_register(ds,
	    zfs_prop_to_name(ZFS_PROP_READONLY), readonly_changed_cb, zfsvfs);
#ifdef illumos
	error = error ? error : dsl_prop_register(ds,
	    zfs_prop_to_name(ZFS_PROP_DEVICES), devices_changed_cb, zfsvfs);
#endif
	error = error ? error : dsl_prop_register(ds,
	    zfs_prop_to_name(ZFS_PROP_SETUID), setuid_changed_cb, zfsvfs);
	error = error ? error : dsl_prop_register(ds,
	    zfs_prop_to_name(ZFS_PROP_EXEC), exec_changed_cb, zfsvfs);
	error = error ? error : dsl_prop_register(ds,
	    zfs_prop_to_name(ZFS_PROP_SNAPDIR), snapdir_changed_cb, zfsvfs);
	error = error ? error : dsl_prop_register(ds,
	    zfs_prop_to_name(ZFS_PROP_ACLMODE), acl_mode_changed_cb, zfsvfs);
	error = error ? error : dsl_prop_register(ds,
	    zfs_prop_to_name(ZFS_PROP_ACLINHERIT), acl_inherit_changed_cb,
	    zfsvfs);
	error = error ? error : dsl_prop_register(ds,
	    zfs_prop_to_name(ZFS_PROP_VSCAN), vscan_changed_cb, zfsvfs);
	dsl_pool_config_exit(dmu_objset_pool(os), FTAG);
	if (error)
		goto unregister;

	/*
	 * Invoke our callbacks to restore temporary mount options.
	 */
	if (do_readonly)
		readonly_changed_cb(zfsvfs, readonly);
	if (do_setuid)
		setuid_changed_cb(zfsvfs, setuid);
	if (do_exec)
		exec_changed_cb(zfsvfs, exec);
	if (do_xattr)
		xattr_changed_cb(zfsvfs, xattr);
	if (do_atime)
		atime_changed_cb(zfsvfs, atime);

	nbmand_changed_cb(zfsvfs, nbmand);

	return (0);

unregister:
	dsl_prop_unregister_all(ds, zfsvfs);
	return (error);
}