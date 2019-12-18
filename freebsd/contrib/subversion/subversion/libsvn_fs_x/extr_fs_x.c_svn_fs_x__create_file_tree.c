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
struct TYPE_19__ {int format; int max_files_per_dir; scalar_t__ youngest_rev_cache; } ;
typedef  TYPE_1__ svn_fs_x__data_t ;
struct TYPE_20__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  path; TYPE_1__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  read_config (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_global_config (TYPE_2__*) ; 
 int /*<<< orphan*/  svn_fs_x__path_current (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__path_lock (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__path_min_unpacked_rev (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__path_revprop_generation (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__path_shard (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__path_txn_current (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__path_txn_current_lock (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__path_txn_proto_revs (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__path_txns_dir (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__reset_revprop_generation_file (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__set_uuid (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_create (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_create_empty (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_make_dir_recursively (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_config (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_revision_zero (TYPE_2__*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__create_file_tree(svn_fs_t *fs,
                           const char *path,
                           int format,
                           int shard_size,
                           apr_pool_t *scratch_pool)
{
  svn_fs_x__data_t *ffd = fs->fsap_data;

  fs->path = apr_pstrdup(fs->pool, path);
  ffd->format = format;

  /* Use an appropriate sharding mode if supported by the format. */
  ffd->max_files_per_dir = shard_size;

  /* Create the revision data directories. */
  SVN_ERR(svn_io_make_dir_recursively(
                              svn_fs_x__path_shard(fs, 0, scratch_pool),
                              scratch_pool));

  /* Create the transaction directory. */
  SVN_ERR(svn_io_make_dir_recursively(
                                  svn_fs_x__path_txns_dir(fs, scratch_pool),
                                  scratch_pool));

  /* Create the protorevs directory. */
  SVN_ERR(svn_io_make_dir_recursively(
                            svn_fs_x__path_txn_proto_revs(fs, scratch_pool),
                            scratch_pool));

  /* Create the 'current' file. */
  SVN_ERR(svn_io_file_create(svn_fs_x__path_current(fs, scratch_pool),
                             "0\n", scratch_pool));

  /* Create the 'uuid' file. */
  SVN_ERR(svn_io_file_create_empty(svn_fs_x__path_lock(fs, scratch_pool),
                                   scratch_pool));
  SVN_ERR(svn_fs_x__set_uuid(fs, NULL, NULL, FALSE, scratch_pool));

  /* Create the fsfs.conf file. */
  SVN_ERR(write_config(fs, scratch_pool));
  SVN_ERR(read_config(ffd, fs->path, fs->pool, scratch_pool));

  /* Global configuration options. */
  SVN_ERR(read_global_config(fs));

  /* Add revision 0. */
  SVN_ERR(write_revision_zero(fs, scratch_pool));

  /* Create the min unpacked rev file. */
  SVN_ERR(svn_io_file_create(
                          svn_fs_x__path_min_unpacked_rev(fs, scratch_pool),
                          "0\n", scratch_pool));

  /* Create the txn-current file if the repository supports
     the transaction sequence file. */
  SVN_ERR(svn_io_file_create(svn_fs_x__path_txn_current(fs, scratch_pool),
                             "0\n", scratch_pool));
  SVN_ERR(svn_io_file_create_empty(
                          svn_fs_x__path_txn_current_lock(fs, scratch_pool),
                          scratch_pool));

  /* Initialize the revprop caching info. */
  SVN_ERR(svn_io_file_create_empty(
                        svn_fs_x__path_revprop_generation(fs, scratch_pool),
                        scratch_pool));
  SVN_ERR(svn_fs_x__reset_revprop_generation_file(fs, scratch_pool));

  ffd->youngest_rev_cache = 0;
  return SVN_NO_ERROR;
}