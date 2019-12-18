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

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  DATASET_NAME ; 
 int /*<<< orphan*/  ENTITY_NAME ; 
 int /*<<< orphan*/  NO_NAME ; 
 int POOL_CHECK_NONE ; 
 int POOL_CHECK_READONLY ; 
 int POOL_CHECK_SUSPENDED ; 
 int /*<<< orphan*/  POOL_NAME ; 
 int /*<<< orphan*/  ZFS_IOC_BOOKMARK ; 
 int /*<<< orphan*/  ZFS_IOC_CHANNEL_PROGRAM ; 
 int /*<<< orphan*/  ZFS_IOC_CLEAR ; 
 int /*<<< orphan*/  ZFS_IOC_CLEAR_FAULT ; 
 int /*<<< orphan*/  ZFS_IOC_CLONE ; 
 int /*<<< orphan*/  ZFS_IOC_CREATE ; 
 int /*<<< orphan*/  ZFS_IOC_DATASET_LIST_NEXT ; 
 int /*<<< orphan*/  ZFS_IOC_DESTROY ; 
 int /*<<< orphan*/  ZFS_IOC_DESTROY_BOOKMARKS ; 
 int /*<<< orphan*/  ZFS_IOC_DESTROY_SNAPS ; 
 int /*<<< orphan*/  ZFS_IOC_DIFF ; 
 int /*<<< orphan*/  ZFS_IOC_DSOBJ_TO_DSNAME ; 
 int /*<<< orphan*/  ZFS_IOC_ERROR_LOG ; 
 int /*<<< orphan*/  ZFS_IOC_GET_BOOKMARKS ; 
 int /*<<< orphan*/  ZFS_IOC_GET_FSACL ; 
 int /*<<< orphan*/  ZFS_IOC_GET_HOLDS ; 
 int /*<<< orphan*/  ZFS_IOC_HOLD ; 
 int /*<<< orphan*/  ZFS_IOC_INHERIT_PROP ; 
 int /*<<< orphan*/  ZFS_IOC_INJECT_FAULT ; 
 int /*<<< orphan*/  ZFS_IOC_INJECT_LIST_NEXT ; 
 int /*<<< orphan*/  ZFS_IOC_JAIL ; 
 int /*<<< orphan*/  ZFS_IOC_LOG_HISTORY ; 
 int /*<<< orphan*/  ZFS_IOC_NEXTBOOT ; 
 int /*<<< orphan*/  ZFS_IOC_NEXT_OBJ ; 
 int /*<<< orphan*/  ZFS_IOC_OBJSET_RECVD_PROPS ; 
 int /*<<< orphan*/  ZFS_IOC_OBJSET_STATS ; 
 int /*<<< orphan*/  ZFS_IOC_OBJSET_ZPLPROPS ; 
 int /*<<< orphan*/  ZFS_IOC_OBJ_TO_PATH ; 
 int /*<<< orphan*/  ZFS_IOC_OBJ_TO_STATS ; 
 int /*<<< orphan*/  ZFS_IOC_POOL_CHECKPOINT ; 
 int /*<<< orphan*/  ZFS_IOC_POOL_CONFIGS ; 
 int /*<<< orphan*/  ZFS_IOC_POOL_CREATE ; 
 int /*<<< orphan*/  ZFS_IOC_POOL_DESTROY ; 
 int /*<<< orphan*/  ZFS_IOC_POOL_DISCARD_CHECKPOINT ; 
 int /*<<< orphan*/  ZFS_IOC_POOL_EXPORT ; 
 int /*<<< orphan*/  ZFS_IOC_POOL_FREEZE ; 
 int /*<<< orphan*/  ZFS_IOC_POOL_GET_HISTORY ; 
 int /*<<< orphan*/  ZFS_IOC_POOL_GET_PROPS ; 
 int /*<<< orphan*/  ZFS_IOC_POOL_IMPORT ; 
 int /*<<< orphan*/  ZFS_IOC_POOL_INITIALIZE ; 
 int /*<<< orphan*/  ZFS_IOC_POOL_REGUID ; 
 int /*<<< orphan*/  ZFS_IOC_POOL_REOPEN ; 
 int /*<<< orphan*/  ZFS_IOC_POOL_SCAN ; 
 int /*<<< orphan*/  ZFS_IOC_POOL_SET_PROPS ; 
 int /*<<< orphan*/  ZFS_IOC_POOL_STATS ; 
 int /*<<< orphan*/  ZFS_IOC_POOL_SYNC ; 
 int /*<<< orphan*/  ZFS_IOC_POOL_TRYIMPORT ; 
 int /*<<< orphan*/  ZFS_IOC_POOL_UPGRADE ; 
 int /*<<< orphan*/  ZFS_IOC_PROMOTE ; 
 int /*<<< orphan*/  ZFS_IOC_RECV ; 
 int /*<<< orphan*/  ZFS_IOC_RELEASE ; 
 int /*<<< orphan*/  ZFS_IOC_REMAP ; 
 int /*<<< orphan*/  ZFS_IOC_RENAME ; 
 int /*<<< orphan*/  ZFS_IOC_ROLLBACK ; 
 int /*<<< orphan*/  ZFS_IOC_SEND ; 
 int /*<<< orphan*/  ZFS_IOC_SEND_NEW ; 
 int /*<<< orphan*/  ZFS_IOC_SEND_PROGRESS ; 
 int /*<<< orphan*/  ZFS_IOC_SEND_SPACE ; 
 int /*<<< orphan*/  ZFS_IOC_SET_FSACL ; 
 int /*<<< orphan*/  ZFS_IOC_SET_PROP ; 
 int /*<<< orphan*/  ZFS_IOC_SHARE ; 
 int /*<<< orphan*/  ZFS_IOC_SMB_ACL ; 
 int /*<<< orphan*/  ZFS_IOC_SNAPSHOT ; 
 int /*<<< orphan*/  ZFS_IOC_SNAPSHOT_LIST_NEXT ; 
 int /*<<< orphan*/  ZFS_IOC_SPACE_SNAPS ; 
 int /*<<< orphan*/  ZFS_IOC_SPACE_WRITTEN ; 
 int /*<<< orphan*/  ZFS_IOC_TMP_SNAPSHOT ; 
 int /*<<< orphan*/  ZFS_IOC_UNJAIL ; 
 int /*<<< orphan*/  ZFS_IOC_USERSPACE_MANY ; 
 int /*<<< orphan*/  ZFS_IOC_USERSPACE_ONE ; 
 int /*<<< orphan*/  ZFS_IOC_USERSPACE_UPGRADE ; 
 int /*<<< orphan*/  ZFS_IOC_VDEV_ADD ; 
 int /*<<< orphan*/  ZFS_IOC_VDEV_ATTACH ; 
 int /*<<< orphan*/  ZFS_IOC_VDEV_DETACH ; 
 int /*<<< orphan*/  ZFS_IOC_VDEV_REMOVE ; 
 int /*<<< orphan*/  ZFS_IOC_VDEV_SETFRU ; 
 int /*<<< orphan*/  ZFS_IOC_VDEV_SETPATH ; 
 int /*<<< orphan*/  ZFS_IOC_VDEV_SET_STATE ; 
 int /*<<< orphan*/  ZFS_IOC_VDEV_SPLIT ; 
 int /*<<< orphan*/  zfs_ioc_bookmark ; 
 int /*<<< orphan*/  zfs_ioc_channel_program ; 
 int /*<<< orphan*/  zfs_ioc_clear ; 
 int /*<<< orphan*/  zfs_ioc_clear_fault ; 
 int /*<<< orphan*/  zfs_ioc_clone ; 
 int /*<<< orphan*/  zfs_ioc_create ; 
 int /*<<< orphan*/  zfs_ioc_dataset_list_next ; 
 int /*<<< orphan*/  zfs_ioc_destroy ; 
 int /*<<< orphan*/  zfs_ioc_destroy_bookmarks ; 
 int /*<<< orphan*/  zfs_ioc_destroy_snaps ; 
 int /*<<< orphan*/  zfs_ioc_diff ; 
 int /*<<< orphan*/  zfs_ioc_dsobj_to_dsname ; 
 int /*<<< orphan*/  zfs_ioc_error_log ; 
 int /*<<< orphan*/  zfs_ioc_get_bookmarks ; 
 int /*<<< orphan*/  zfs_ioc_get_fsacl ; 
 int /*<<< orphan*/  zfs_ioc_get_holds ; 
 int /*<<< orphan*/  zfs_ioc_hold ; 
 int /*<<< orphan*/  zfs_ioc_inherit_prop ; 
 int /*<<< orphan*/  zfs_ioc_inject_fault ; 
 int /*<<< orphan*/  zfs_ioc_inject_list_next ; 
 int /*<<< orphan*/  zfs_ioc_jail ; 
 int /*<<< orphan*/  zfs_ioc_log_history ; 
 int /*<<< orphan*/  zfs_ioc_next_obj ; 
 int /*<<< orphan*/  zfs_ioc_nextboot ; 
 int /*<<< orphan*/  zfs_ioc_obj_to_path ; 
 int /*<<< orphan*/  zfs_ioc_obj_to_stats ; 
 int /*<<< orphan*/  zfs_ioc_objset_recvd_props ; 
 int /*<<< orphan*/  zfs_ioc_objset_stats ; 
 int /*<<< orphan*/  zfs_ioc_objset_zplprops ; 
 int /*<<< orphan*/  zfs_ioc_pool_checkpoint ; 
 int /*<<< orphan*/  zfs_ioc_pool_configs ; 
 int /*<<< orphan*/  zfs_ioc_pool_create ; 
 int /*<<< orphan*/  zfs_ioc_pool_destroy ; 
 int /*<<< orphan*/  zfs_ioc_pool_discard_checkpoint ; 
 int /*<<< orphan*/  zfs_ioc_pool_export ; 
 int /*<<< orphan*/  zfs_ioc_pool_freeze ; 
 int /*<<< orphan*/  zfs_ioc_pool_get_history ; 
 int /*<<< orphan*/  zfs_ioc_pool_get_props ; 
 int /*<<< orphan*/  zfs_ioc_pool_import ; 
 int /*<<< orphan*/  zfs_ioc_pool_initialize ; 
 int /*<<< orphan*/  zfs_ioc_pool_reguid ; 
 int /*<<< orphan*/  zfs_ioc_pool_reopen ; 
 int /*<<< orphan*/  zfs_ioc_pool_scan ; 
 int /*<<< orphan*/  zfs_ioc_pool_set_props ; 
 int /*<<< orphan*/  zfs_ioc_pool_stats ; 
 int /*<<< orphan*/  zfs_ioc_pool_sync ; 
 int /*<<< orphan*/  zfs_ioc_pool_tryimport ; 
 int /*<<< orphan*/  zfs_ioc_pool_upgrade ; 
 int /*<<< orphan*/  zfs_ioc_promote ; 
 int /*<<< orphan*/  zfs_ioc_recv ; 
 int /*<<< orphan*/  zfs_ioc_release ; 
 int /*<<< orphan*/  zfs_ioc_remap ; 
 int /*<<< orphan*/  zfs_ioc_rename ; 
 int /*<<< orphan*/  zfs_ioc_rollback ; 
 int /*<<< orphan*/  zfs_ioc_send ; 
 int /*<<< orphan*/  zfs_ioc_send_new ; 
 int /*<<< orphan*/  zfs_ioc_send_progress ; 
 int /*<<< orphan*/  zfs_ioc_send_space ; 
 int /*<<< orphan*/  zfs_ioc_set_fsacl ; 
 int /*<<< orphan*/  zfs_ioc_set_prop ; 
 int /*<<< orphan*/  zfs_ioc_share ; 
 int /*<<< orphan*/  zfs_ioc_smb_acl ; 
 int /*<<< orphan*/  zfs_ioc_snapshot ; 
 int /*<<< orphan*/  zfs_ioc_snapshot_list_next ; 
 int /*<<< orphan*/  zfs_ioc_space_snaps ; 
 int /*<<< orphan*/  zfs_ioc_space_written ; 
 int /*<<< orphan*/  zfs_ioc_tmp_snapshot ; 
 int /*<<< orphan*/  zfs_ioc_unjail ; 
 int /*<<< orphan*/  zfs_ioc_userspace_many ; 
 int /*<<< orphan*/  zfs_ioc_userspace_one ; 
 int /*<<< orphan*/  zfs_ioc_userspace_upgrade ; 
 int /*<<< orphan*/  zfs_ioc_vdev_add ; 
 int /*<<< orphan*/  zfs_ioc_vdev_attach ; 
 int /*<<< orphan*/  zfs_ioc_vdev_detach ; 
 int /*<<< orphan*/  zfs_ioc_vdev_remove ; 
 int /*<<< orphan*/  zfs_ioc_vdev_set_state ; 
 int /*<<< orphan*/  zfs_ioc_vdev_setfru ; 
 int /*<<< orphan*/  zfs_ioc_vdev_setpath ; 
 int /*<<< orphan*/  zfs_ioc_vdev_split ; 
 int /*<<< orphan*/  zfs_ioctl_register (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_ioctl_register_dataset_modify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_ioctl_register_dataset_nolog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfs_ioctl_register_dataset_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_ioctl_register_dataset_read_secpolicy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_ioctl_register_legacy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfs_ioctl_register_pool (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfs_ioctl_register_pool_meta (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_ioctl_register_pool_modify (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_secpolicy_bookmark ; 
 int /*<<< orphan*/  zfs_secpolicy_config ; 
 int /*<<< orphan*/  zfs_secpolicy_create_clone ; 
 int /*<<< orphan*/  zfs_secpolicy_destroy ; 
 int /*<<< orphan*/  zfs_secpolicy_destroy_bookmarks ; 
 int /*<<< orphan*/  zfs_secpolicy_destroy_snaps ; 
 int /*<<< orphan*/  zfs_secpolicy_diff ; 
 int /*<<< orphan*/  zfs_secpolicy_hold ; 
 int /*<<< orphan*/  zfs_secpolicy_inherit_prop ; 
 int /*<<< orphan*/  zfs_secpolicy_inject ; 
 int /*<<< orphan*/  zfs_secpolicy_log_history ; 
 int /*<<< orphan*/  zfs_secpolicy_none ; 
 int /*<<< orphan*/  zfs_secpolicy_promote ; 
 int /*<<< orphan*/  zfs_secpolicy_read ; 
 int /*<<< orphan*/  zfs_secpolicy_recv ; 
 int /*<<< orphan*/  zfs_secpolicy_release ; 
 int /*<<< orphan*/  zfs_secpolicy_remap ; 
 int /*<<< orphan*/  zfs_secpolicy_rename ; 
 int /*<<< orphan*/  zfs_secpolicy_rollback ; 
 int /*<<< orphan*/  zfs_secpolicy_send ; 
 int /*<<< orphan*/  zfs_secpolicy_send_new ; 
 int /*<<< orphan*/  zfs_secpolicy_set_fsacl ; 
 int /*<<< orphan*/  zfs_secpolicy_share ; 
 int /*<<< orphan*/  zfs_secpolicy_smb_acl ; 
 int /*<<< orphan*/  zfs_secpolicy_snapshot ; 
 int /*<<< orphan*/  zfs_secpolicy_tmp_snapshot ; 
 int /*<<< orphan*/  zfs_secpolicy_userspace_many ; 
 int /*<<< orphan*/  zfs_secpolicy_userspace_one ; 
 int /*<<< orphan*/  zfs_secpolicy_userspace_upgrade ; 

__attribute__((used)) static void
zfs_ioctl_init(void)
{
	zfs_ioctl_register("snapshot", ZFS_IOC_SNAPSHOT,
	    zfs_ioc_snapshot, zfs_secpolicy_snapshot, POOL_NAME,
	    POOL_CHECK_SUSPENDED | POOL_CHECK_READONLY, B_TRUE, B_TRUE);

	zfs_ioctl_register("log_history", ZFS_IOC_LOG_HISTORY,
	    zfs_ioc_log_history, zfs_secpolicy_log_history, NO_NAME,
	    POOL_CHECK_SUSPENDED | POOL_CHECK_READONLY, B_FALSE, B_FALSE);

	zfs_ioctl_register("space_snaps", ZFS_IOC_SPACE_SNAPS,
	    zfs_ioc_space_snaps, zfs_secpolicy_read, DATASET_NAME,
	    POOL_CHECK_SUSPENDED, B_FALSE, B_FALSE);

	zfs_ioctl_register("send", ZFS_IOC_SEND_NEW,
	    zfs_ioc_send_new, zfs_secpolicy_send_new, DATASET_NAME,
	    POOL_CHECK_SUSPENDED, B_FALSE, B_FALSE);

	zfs_ioctl_register("send_space", ZFS_IOC_SEND_SPACE,
	    zfs_ioc_send_space, zfs_secpolicy_read, DATASET_NAME,
	    POOL_CHECK_SUSPENDED, B_FALSE, B_FALSE);

	zfs_ioctl_register("create", ZFS_IOC_CREATE,
	    zfs_ioc_create, zfs_secpolicy_create_clone, DATASET_NAME,
	    POOL_CHECK_SUSPENDED | POOL_CHECK_READONLY, B_TRUE, B_TRUE);

	zfs_ioctl_register("clone", ZFS_IOC_CLONE,
	    zfs_ioc_clone, zfs_secpolicy_create_clone, DATASET_NAME,
	    POOL_CHECK_SUSPENDED | POOL_CHECK_READONLY, B_TRUE, B_TRUE);

	zfs_ioctl_register("remap", ZFS_IOC_REMAP,
	    zfs_ioc_remap, zfs_secpolicy_remap, DATASET_NAME,
	    POOL_CHECK_SUSPENDED | POOL_CHECK_READONLY, B_FALSE, B_TRUE);

	zfs_ioctl_register("destroy_snaps", ZFS_IOC_DESTROY_SNAPS,
	    zfs_ioc_destroy_snaps, zfs_secpolicy_destroy_snaps, POOL_NAME,
	    POOL_CHECK_SUSPENDED | POOL_CHECK_READONLY, B_TRUE, B_TRUE);

	zfs_ioctl_register("hold", ZFS_IOC_HOLD,
	    zfs_ioc_hold, zfs_secpolicy_hold, POOL_NAME,
	    POOL_CHECK_SUSPENDED | POOL_CHECK_READONLY, B_TRUE, B_TRUE);
	zfs_ioctl_register("release", ZFS_IOC_RELEASE,
	    zfs_ioc_release, zfs_secpolicy_release, POOL_NAME,
	    POOL_CHECK_SUSPENDED | POOL_CHECK_READONLY, B_TRUE, B_TRUE);

	zfs_ioctl_register("get_holds", ZFS_IOC_GET_HOLDS,
	    zfs_ioc_get_holds, zfs_secpolicy_read, DATASET_NAME,
	    POOL_CHECK_SUSPENDED, B_FALSE, B_FALSE);

	zfs_ioctl_register("rollback", ZFS_IOC_ROLLBACK,
	    zfs_ioc_rollback, zfs_secpolicy_rollback, DATASET_NAME,
	    POOL_CHECK_SUSPENDED | POOL_CHECK_READONLY, B_FALSE, B_TRUE);

	zfs_ioctl_register("bookmark", ZFS_IOC_BOOKMARK,
	    zfs_ioc_bookmark, zfs_secpolicy_bookmark, POOL_NAME,
	    POOL_CHECK_SUSPENDED | POOL_CHECK_READONLY, B_TRUE, B_TRUE);

	zfs_ioctl_register("get_bookmarks", ZFS_IOC_GET_BOOKMARKS,
	    zfs_ioc_get_bookmarks, zfs_secpolicy_read, DATASET_NAME,
	    POOL_CHECK_SUSPENDED, B_FALSE, B_FALSE);

	zfs_ioctl_register("destroy_bookmarks", ZFS_IOC_DESTROY_BOOKMARKS,
	    zfs_ioc_destroy_bookmarks, zfs_secpolicy_destroy_bookmarks,
	    POOL_NAME,
	    POOL_CHECK_SUSPENDED | POOL_CHECK_READONLY, B_TRUE, B_TRUE);

	zfs_ioctl_register("channel_program", ZFS_IOC_CHANNEL_PROGRAM,
	    zfs_ioc_channel_program, zfs_secpolicy_config,
	    POOL_NAME, POOL_CHECK_SUSPENDED | POOL_CHECK_READONLY, B_TRUE,
	    B_TRUE);

	zfs_ioctl_register("zpool_checkpoint", ZFS_IOC_POOL_CHECKPOINT,
	    zfs_ioc_pool_checkpoint, zfs_secpolicy_config, POOL_NAME,
	    POOL_CHECK_SUSPENDED | POOL_CHECK_READONLY, B_TRUE, B_TRUE);

	zfs_ioctl_register("zpool_discard_checkpoint",
	    ZFS_IOC_POOL_DISCARD_CHECKPOINT, zfs_ioc_pool_discard_checkpoint,
	    zfs_secpolicy_config, POOL_NAME,
	    POOL_CHECK_SUSPENDED | POOL_CHECK_READONLY, B_TRUE, B_TRUE);

	zfs_ioctl_register("initialize", ZFS_IOC_POOL_INITIALIZE,
	    zfs_ioc_pool_initialize, zfs_secpolicy_config, POOL_NAME,
	    POOL_CHECK_SUSPENDED | POOL_CHECK_READONLY, B_TRUE, B_TRUE);

	zfs_ioctl_register("sync", ZFS_IOC_POOL_SYNC,
	    zfs_ioc_pool_sync, zfs_secpolicy_none, POOL_NAME,
	    POOL_CHECK_SUSPENDED | POOL_CHECK_READONLY, B_FALSE, B_FALSE);

	/* IOCTLS that use the legacy function signature */

	zfs_ioctl_register_legacy(ZFS_IOC_POOL_FREEZE, zfs_ioc_pool_freeze,
	    zfs_secpolicy_config, NO_NAME, B_FALSE, POOL_CHECK_READONLY);

	zfs_ioctl_register_pool(ZFS_IOC_POOL_CREATE, zfs_ioc_pool_create,
	    zfs_secpolicy_config, B_TRUE, POOL_CHECK_NONE);
	zfs_ioctl_register_pool_modify(ZFS_IOC_POOL_SCAN,
	    zfs_ioc_pool_scan);
	zfs_ioctl_register_pool_modify(ZFS_IOC_POOL_UPGRADE,
	    zfs_ioc_pool_upgrade);
	zfs_ioctl_register_pool_modify(ZFS_IOC_VDEV_ADD,
	    zfs_ioc_vdev_add);
	zfs_ioctl_register_pool_modify(ZFS_IOC_VDEV_REMOVE,
	    zfs_ioc_vdev_remove);
	zfs_ioctl_register_pool_modify(ZFS_IOC_VDEV_SET_STATE,
	    zfs_ioc_vdev_set_state);
	zfs_ioctl_register_pool_modify(ZFS_IOC_VDEV_ATTACH,
	    zfs_ioc_vdev_attach);
	zfs_ioctl_register_pool_modify(ZFS_IOC_VDEV_DETACH,
	    zfs_ioc_vdev_detach);
	zfs_ioctl_register_pool_modify(ZFS_IOC_VDEV_SETPATH,
	    zfs_ioc_vdev_setpath);
	zfs_ioctl_register_pool_modify(ZFS_IOC_VDEV_SETFRU,
	    zfs_ioc_vdev_setfru);
	zfs_ioctl_register_pool_modify(ZFS_IOC_POOL_SET_PROPS,
	    zfs_ioc_pool_set_props);
	zfs_ioctl_register_pool_modify(ZFS_IOC_VDEV_SPLIT,
	    zfs_ioc_vdev_split);
	zfs_ioctl_register_pool_modify(ZFS_IOC_POOL_REGUID,
	    zfs_ioc_pool_reguid);

	zfs_ioctl_register_pool_meta(ZFS_IOC_POOL_CONFIGS,
	    zfs_ioc_pool_configs, zfs_secpolicy_none);
	zfs_ioctl_register_pool_meta(ZFS_IOC_POOL_TRYIMPORT,
	    zfs_ioc_pool_tryimport, zfs_secpolicy_config);
	zfs_ioctl_register_pool_meta(ZFS_IOC_INJECT_FAULT,
	    zfs_ioc_inject_fault, zfs_secpolicy_inject);
	zfs_ioctl_register_pool_meta(ZFS_IOC_CLEAR_FAULT,
	    zfs_ioc_clear_fault, zfs_secpolicy_inject);
	zfs_ioctl_register_pool_meta(ZFS_IOC_INJECT_LIST_NEXT,
	    zfs_ioc_inject_list_next, zfs_secpolicy_inject);

	/*
	 * pool destroy, and export don't log the history as part of
	 * zfsdev_ioctl, but rather zfs_ioc_pool_export
	 * does the logging of those commands.
	 */
	zfs_ioctl_register_pool(ZFS_IOC_POOL_DESTROY, zfs_ioc_pool_destroy,
	    zfs_secpolicy_config, B_FALSE, POOL_CHECK_NONE);
	zfs_ioctl_register_pool(ZFS_IOC_POOL_EXPORT, zfs_ioc_pool_export,
	    zfs_secpolicy_config, B_FALSE, POOL_CHECK_NONE);

	zfs_ioctl_register_pool(ZFS_IOC_POOL_STATS, zfs_ioc_pool_stats,
	    zfs_secpolicy_read, B_FALSE, POOL_CHECK_NONE);
	zfs_ioctl_register_pool(ZFS_IOC_POOL_GET_PROPS, zfs_ioc_pool_get_props,
	    zfs_secpolicy_read, B_FALSE, POOL_CHECK_NONE);

	zfs_ioctl_register_pool(ZFS_IOC_ERROR_LOG, zfs_ioc_error_log,
	    zfs_secpolicy_inject, B_FALSE, POOL_CHECK_NONE);
	zfs_ioctl_register_pool(ZFS_IOC_DSOBJ_TO_DSNAME,
	    zfs_ioc_dsobj_to_dsname,
	    zfs_secpolicy_diff, B_FALSE, POOL_CHECK_NONE);
	zfs_ioctl_register_pool(ZFS_IOC_POOL_GET_HISTORY,
	    zfs_ioc_pool_get_history,
	    zfs_secpolicy_config, B_FALSE, POOL_CHECK_SUSPENDED);

	zfs_ioctl_register_pool(ZFS_IOC_POOL_IMPORT, zfs_ioc_pool_import,
	    zfs_secpolicy_config, B_TRUE, POOL_CHECK_NONE);

	zfs_ioctl_register_pool(ZFS_IOC_CLEAR, zfs_ioc_clear,
	    zfs_secpolicy_config, B_TRUE, POOL_CHECK_READONLY);
	zfs_ioctl_register_pool(ZFS_IOC_POOL_REOPEN, zfs_ioc_pool_reopen,
	    zfs_secpolicy_config, B_TRUE, POOL_CHECK_SUSPENDED);

	zfs_ioctl_register_dataset_read(ZFS_IOC_SPACE_WRITTEN,
	    zfs_ioc_space_written);
	zfs_ioctl_register_dataset_read(ZFS_IOC_OBJSET_RECVD_PROPS,
	    zfs_ioc_objset_recvd_props);
	zfs_ioctl_register_dataset_read(ZFS_IOC_NEXT_OBJ,
	    zfs_ioc_next_obj);
	zfs_ioctl_register_dataset_read(ZFS_IOC_GET_FSACL,
	    zfs_ioc_get_fsacl);
	zfs_ioctl_register_dataset_read(ZFS_IOC_OBJSET_STATS,
	    zfs_ioc_objset_stats);
	zfs_ioctl_register_dataset_read(ZFS_IOC_OBJSET_ZPLPROPS,
	    zfs_ioc_objset_zplprops);
	zfs_ioctl_register_dataset_read(ZFS_IOC_DATASET_LIST_NEXT,
	    zfs_ioc_dataset_list_next);
	zfs_ioctl_register_dataset_read(ZFS_IOC_SNAPSHOT_LIST_NEXT,
	    zfs_ioc_snapshot_list_next);
	zfs_ioctl_register_dataset_read(ZFS_IOC_SEND_PROGRESS,
	    zfs_ioc_send_progress);

	zfs_ioctl_register_dataset_read_secpolicy(ZFS_IOC_DIFF,
	    zfs_ioc_diff, zfs_secpolicy_diff);
	zfs_ioctl_register_dataset_read_secpolicy(ZFS_IOC_OBJ_TO_STATS,
	    zfs_ioc_obj_to_stats, zfs_secpolicy_diff);
	zfs_ioctl_register_dataset_read_secpolicy(ZFS_IOC_OBJ_TO_PATH,
	    zfs_ioc_obj_to_path, zfs_secpolicy_diff);
	zfs_ioctl_register_dataset_read_secpolicy(ZFS_IOC_USERSPACE_ONE,
	    zfs_ioc_userspace_one, zfs_secpolicy_userspace_one);
	zfs_ioctl_register_dataset_read_secpolicy(ZFS_IOC_USERSPACE_MANY,
	    zfs_ioc_userspace_many, zfs_secpolicy_userspace_many);
	zfs_ioctl_register_dataset_read_secpolicy(ZFS_IOC_SEND,
	    zfs_ioc_send, zfs_secpolicy_send);

	zfs_ioctl_register_dataset_modify(ZFS_IOC_SET_PROP, zfs_ioc_set_prop,
	    zfs_secpolicy_none);
	zfs_ioctl_register_dataset_modify(ZFS_IOC_DESTROY, zfs_ioc_destroy,
	    zfs_secpolicy_destroy);
	zfs_ioctl_register_dataset_modify(ZFS_IOC_RECV, zfs_ioc_recv,
	    zfs_secpolicy_recv);
	zfs_ioctl_register_dataset_modify(ZFS_IOC_PROMOTE, zfs_ioc_promote,
	    zfs_secpolicy_promote);
	zfs_ioctl_register_dataset_modify(ZFS_IOC_INHERIT_PROP,
	    zfs_ioc_inherit_prop, zfs_secpolicy_inherit_prop);
	zfs_ioctl_register_dataset_modify(ZFS_IOC_SET_FSACL, zfs_ioc_set_fsacl,
	    zfs_secpolicy_set_fsacl);

	/*
	 * Not using zfs_ioctl_register_dataset_modify as DATASET_NAME check
	 * won't allow a bookmark name.
	 */
	zfs_ioctl_register_legacy(ZFS_IOC_RENAME, zfs_ioc_rename,
	    zfs_secpolicy_rename, ENTITY_NAME, B_TRUE,
	    POOL_CHECK_SUSPENDED | POOL_CHECK_READONLY);

	zfs_ioctl_register_dataset_nolog(ZFS_IOC_SHARE, zfs_ioc_share,
	    zfs_secpolicy_share, POOL_CHECK_NONE);
	zfs_ioctl_register_dataset_nolog(ZFS_IOC_SMB_ACL, zfs_ioc_smb_acl,
	    zfs_secpolicy_smb_acl, POOL_CHECK_NONE);
	zfs_ioctl_register_dataset_nolog(ZFS_IOC_USERSPACE_UPGRADE,
	    zfs_ioc_userspace_upgrade, zfs_secpolicy_userspace_upgrade,
	    POOL_CHECK_SUSPENDED | POOL_CHECK_READONLY);
	zfs_ioctl_register_dataset_nolog(ZFS_IOC_TMP_SNAPSHOT,
	    zfs_ioc_tmp_snapshot, zfs_secpolicy_tmp_snapshot,
	    POOL_CHECK_SUSPENDED | POOL_CHECK_READONLY);

#ifdef __FreeBSD__
	zfs_ioctl_register_dataset_nolog(ZFS_IOC_JAIL, zfs_ioc_jail,
	    zfs_secpolicy_config, POOL_CHECK_NONE);
	zfs_ioctl_register_dataset_nolog(ZFS_IOC_UNJAIL, zfs_ioc_unjail,
	    zfs_secpolicy_config, POOL_CHECK_NONE);
	zfs_ioctl_register("fbsd_nextboot", ZFS_IOC_NEXTBOOT,
	    zfs_ioc_nextboot, zfs_secpolicy_config, NO_NAME,
	    POOL_CHECK_NONE, B_FALSE, B_FALSE);
#endif
}