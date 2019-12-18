#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int svn_node_kind_t ;
struct TYPE_14__ {int /*<<< orphan*/  uuid; int /*<<< orphan*/  path; TYPE_2__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct upgrade_baton_t {int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; int /*<<< orphan*/  notify_baton; int /*<<< orphan*/  (* notify_func ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;TYPE_1__* fs; } ;
struct TYPE_15__ {int format; int max_files_per_dir; scalar_t__ use_log_addressing; } ;
typedef  TYPE_2__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  PATH_CONFIG ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_GENERAL ; 
 int SVN_FS_FS__FORMAT_NUMBER ; 
 int SVN_FS_FS__MIN_PACKED_FORMAT ; 
 int SVN_FS_FS__MIN_PACKED_REVPROP_FORMAT ; 
 int SVN_FS_FS__MIN_PROTOREVS_DIR_FORMAT ; 
 int SVN_FS_FS__MIN_TXN_CURRENT_FORMAT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  create_file_ignore_eexist (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 char* path_format (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_format (int*,int*,scalar_t__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_uuid (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_join (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_fs__path_min_unpacked_rev (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__path_txn_current (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__path_txn_current_lock (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__path_txn_proto_revs (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__set_uuid (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__upgrade_cleanup_pack_revprops (TYPE_1__*,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *),int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__upgrade_pack_revprops (TYPE_1__*,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *),int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__write_format (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_upgrade_format_bumped ; 
 int /*<<< orphan*/  svn_io_check_path (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_create (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_make_dir_recursively (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
#define  svn_node_file 129 
#define  svn_node_none 128 
 int /*<<< orphan*/  write_config (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
upgrade_body(void *baton, apr_pool_t *pool)
{
  struct upgrade_baton_t *upgrade_baton = baton;
  svn_fs_t *fs = upgrade_baton->fs;
  fs_fs_data_t *ffd = fs->fsap_data;
  int format, max_files_per_dir;
  svn_boolean_t use_log_addressing;
  const char *format_path = path_format(fs, pool);
  svn_node_kind_t kind;
  svn_boolean_t needs_revprop_shard_cleanup = FALSE;

  /* Read the FS format number and max-files-per-dir setting. */
  SVN_ERR(read_format(&format, &max_files_per_dir, &use_log_addressing,
                      format_path, pool));

  /* If the config file does not exist, create one. */
  SVN_ERR(svn_io_check_path(svn_dirent_join(fs->path, PATH_CONFIG, pool),
                            &kind, pool));
  switch (kind)
    {
    case svn_node_none:
      SVN_ERR(write_config(fs, pool));
      break;
    case svn_node_file:
      break;
    default:
      return svn_error_createf(SVN_ERR_FS_GENERAL, NULL,
                               _("'%s' is not a regular file."
                                 " Please move it out of "
                                 "the way and try again"),
                               svn_dirent_join(fs->path, PATH_CONFIG, pool));
    }

  /* If we're already up-to-date, there's nothing else to be done here. */
  if (format == SVN_FS_FS__FORMAT_NUMBER)
    return SVN_NO_ERROR;

  /* If our filesystem predates the existence of the 'txn-current
     file', make that file and its corresponding lock file. */
  if (format < SVN_FS_FS__MIN_TXN_CURRENT_FORMAT)
    {
      SVN_ERR(create_file_ignore_eexist(
                           svn_fs_fs__path_txn_current(fs, pool), "0\n",
                           pool));
      SVN_ERR(create_file_ignore_eexist(
                           svn_fs_fs__path_txn_current_lock(fs, pool), "",
                           pool));
    }

  /* If our filesystem predates the existence of the 'txn-protorevs'
     dir, make that directory.  */
  if (format < SVN_FS_FS__MIN_PROTOREVS_DIR_FORMAT)
    {
      SVN_ERR(svn_io_make_dir_recursively(
          svn_fs_fs__path_txn_proto_revs(fs, pool), pool));
    }

  /* If our filesystem is new enough, write the min unpacked rev file. */
  if (format < SVN_FS_FS__MIN_PACKED_FORMAT)
    SVN_ERR(svn_io_file_create(svn_fs_fs__path_min_unpacked_rev(fs, pool),
                               "0\n", pool));

  /* If the file system supports revision packing but not revprop packing
     *and* the FS has been sharded, pack the revprops up to the point that
     revision data has been packed.  However, keep the non-packed revprop
     files around until after the format bump */
  if (   format >= SVN_FS_FS__MIN_PACKED_FORMAT
      && format < SVN_FS_FS__MIN_PACKED_REVPROP_FORMAT
      && max_files_per_dir > 0)
    {
      needs_revprop_shard_cleanup = TRUE;
      SVN_ERR(svn_fs_fs__upgrade_pack_revprops(fs,
                                               upgrade_baton->notify_func,
                                               upgrade_baton->notify_baton,
                                               upgrade_baton->cancel_func,
                                               upgrade_baton->cancel_baton,
                                               pool));
    }

  /* We will need the UUID info shortly ...
     Read it before the format bump as the UUID file still uses the old
     format. */
  SVN_ERR(read_uuid(fs, pool));

  /* Update the format info in the FS struct.  Upgrade steps further
     down will use the format from FS to create missing info. */
  ffd->format = SVN_FS_FS__FORMAT_NUMBER;
  ffd->max_files_per_dir = max_files_per_dir;
  ffd->use_log_addressing = use_log_addressing;

  /* Always add / bump the instance ID such that no form of caching
     accidentally uses outdated information.  Keep the UUID. */
  SVN_ERR(svn_fs_fs__set_uuid(fs, fs->uuid, NULL, pool));

  /* Bump the format file. */
  SVN_ERR(svn_fs_fs__write_format(fs, TRUE, pool));

  if (upgrade_baton->notify_func)
    SVN_ERR(upgrade_baton->notify_func(upgrade_baton->notify_baton,
                                       SVN_FS_FS__FORMAT_NUMBER,
                                       svn_fs_upgrade_format_bumped,
                                       pool));

  /* Now, it is safe to remove the redundant revprop files. */
  if (needs_revprop_shard_cleanup)
    SVN_ERR(svn_fs_fs__upgrade_cleanup_pack_revprops(fs,
                                               upgrade_baton->notify_func,
                                               upgrade_baton->notify_baton,
                                               upgrade_baton->cancel_func,
                                               upgrade_baton->cancel_baton,
                                               pool));

  /* Done */
  return SVN_NO_ERROR;
}