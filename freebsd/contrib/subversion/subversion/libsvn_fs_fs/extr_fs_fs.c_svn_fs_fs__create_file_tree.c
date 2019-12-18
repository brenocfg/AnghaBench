#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  path; TYPE_2__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_20__ {int format; int max_files_per_dir; scalar_t__ youngest_rev_cache; int /*<<< orphan*/  use_log_addressing; } ;
typedef  TYPE_2__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PATH_REVPROPS_DIR ; 
 int /*<<< orphan*/  PATH_REVS_DIR ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int SVN_FS_FS__MIN_CONFIG_FILE ; 
 int SVN_FS_FS__MIN_LAYOUT_FORMAT_OPTION_FORMAT ; 
 int SVN_FS_FS__MIN_LOG_ADDRESSING_FORMAT ; 
 int SVN_FS_FS__MIN_PACKED_FORMAT ; 
 int SVN_FS_FS__MIN_PROTOREVS_DIR_FORMAT ; 
 int SVN_FS_FS__MIN_TXN_CURRENT_FORMAT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  read_config (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_global_config (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_dirent_join (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__path_current (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__path_lock (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__path_min_unpacked_rev (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__path_rev_shard (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__path_revprops_shard (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__path_txn_current (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__path_txn_current_lock (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__path_txn_proto_revs (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__path_txns_dir (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__set_uuid (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__write_current (TYPE_1__*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_create (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_create_empty (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_make_dir_recursively (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_config (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_revision_zero (TYPE_1__*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__create_file_tree(svn_fs_t *fs,
                            const char *path,
                            int format,
                            int shard_size,
                            svn_boolean_t use_log_addressing,
                            apr_pool_t *pool)
{
  fs_fs_data_t *ffd = fs->fsap_data;

  fs->path = apr_pstrdup(fs->pool, path);
  ffd->format = format;

  /* Use an appropriate sharding mode if supported by the format. */
  if (format >= SVN_FS_FS__MIN_LAYOUT_FORMAT_OPTION_FORMAT)
    ffd->max_files_per_dir = shard_size;
  else
    ffd->max_files_per_dir = 0;

  /* Select the addressing mode depending on the format. */
  if (format >= SVN_FS_FS__MIN_LOG_ADDRESSING_FORMAT)
    ffd->use_log_addressing = use_log_addressing;
  else
    ffd->use_log_addressing = FALSE;

  /* Create the revision data directories. */
  if (ffd->max_files_per_dir)
    SVN_ERR(svn_io_make_dir_recursively(svn_fs_fs__path_rev_shard(fs, 0,
                                                                  pool),
                                        pool));
  else
    SVN_ERR(svn_io_make_dir_recursively(svn_dirent_join(path, PATH_REVS_DIR,
                                                        pool),
                                        pool));

  /* Create the revprops directory. */
  if (ffd->max_files_per_dir)
    SVN_ERR(svn_io_make_dir_recursively(svn_fs_fs__path_revprops_shard(fs, 0,
                                                                       pool),
                                        pool));
  else
    SVN_ERR(svn_io_make_dir_recursively(svn_dirent_join(path,
                                                        PATH_REVPROPS_DIR,
                                                        pool),
                                        pool));

  /* Create the transaction directory. */
  SVN_ERR(svn_io_make_dir_recursively(svn_fs_fs__path_txns_dir(fs, pool),
                                      pool));

  /* Create the protorevs directory. */
  if (format >= SVN_FS_FS__MIN_PROTOREVS_DIR_FORMAT)
    SVN_ERR(svn_io_make_dir_recursively(svn_fs_fs__path_txn_proto_revs(fs,
                                                                       pool),
                                        pool));

  /* Create the 'current' file. */
  SVN_ERR(svn_io_file_create_empty(svn_fs_fs__path_current(fs, pool), pool));
  SVN_ERR(svn_fs_fs__write_current(fs, 0, 1, 1, pool));

  /* Create the 'uuid' file. */
  SVN_ERR(svn_io_file_create_empty(svn_fs_fs__path_lock(fs, pool), pool));
  SVN_ERR(svn_fs_fs__set_uuid(fs, NULL, NULL, pool));

  /* Create the fsfs.conf file if supported.  Older server versions would
     simply ignore the file but that might result in a different behavior
     than with the later releases.  Also, hotcopy would ignore, i.e. not
     copy, a fsfs.conf with old formats. */
  if (ffd->format >= SVN_FS_FS__MIN_CONFIG_FILE)
    SVN_ERR(write_config(fs, pool));

  SVN_ERR(read_config(ffd, fs->path, fs->pool, pool));

  /* Global configuration options. */
  SVN_ERR(read_global_config(fs));

  /* Add revision 0. */
  SVN_ERR(write_revision_zero(fs, pool));

  /* Create the min unpacked rev file. */
  if (ffd->format >= SVN_FS_FS__MIN_PACKED_FORMAT)
    SVN_ERR(svn_io_file_create(svn_fs_fs__path_min_unpacked_rev(fs, pool),
                               "0\n", pool));

  /* Create the txn-current file if the repository supports
     the transaction sequence file. */
  if (format >= SVN_FS_FS__MIN_TXN_CURRENT_FORMAT)
    {
      SVN_ERR(svn_io_file_create(svn_fs_fs__path_txn_current(fs, pool),
                                 "0\n", pool));
      SVN_ERR(svn_io_file_create_empty(
                                 svn_fs_fs__path_txn_current_lock(fs, pool),
                                 pool));
    }

  ffd->youngest_rev_cache = 0;
  return SVN_NO_ERROR;
}