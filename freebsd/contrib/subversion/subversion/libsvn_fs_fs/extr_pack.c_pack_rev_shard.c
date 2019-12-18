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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int apr_int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PATH_PACKED ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  pack_log_addressed (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pack_phys_addressed (char const*,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_join (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_fs__use_log_addressing (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_copy_perms (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_dir_make (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_remove_dir2 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_set_file_read_only (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
pack_rev_shard(svn_fs_t *fs,
               const char *pack_file_dir,
               const char *shard_path,
               apr_int64_t shard,
               int max_files_per_dir,
               apr_size_t max_mem,
               svn_boolean_t flush_to_disk,
               svn_cancel_func_t cancel_func,
               void *cancel_baton,
               apr_pool_t *pool)
{
  const char *pack_file_path;
  svn_revnum_t shard_rev = (svn_revnum_t) (shard * max_files_per_dir);

  /* Some useful paths. */
  pack_file_path = svn_dirent_join(pack_file_dir, PATH_PACKED, pool);

  /* Remove any existing pack file for this shard, since it is incomplete. */
  SVN_ERR(svn_io_remove_dir2(pack_file_dir, TRUE, cancel_func, cancel_baton,
                             pool));

  /* Create the new directory and pack file. */
  SVN_ERR(svn_io_dir_make(pack_file_dir, APR_OS_DEFAULT, pool));

  /* Index information files */
  if (svn_fs_fs__use_log_addressing(fs))
    SVN_ERR(pack_log_addressed(fs, pack_file_dir, shard_path,
                               shard_rev, max_mem, flush_to_disk,
                               cancel_func, cancel_baton, pool));
  else
    SVN_ERR(pack_phys_addressed(pack_file_dir, shard_path, shard_rev,
                                max_files_per_dir, flush_to_disk,
                                cancel_func, cancel_baton, pool));

  SVN_ERR(svn_io_copy_perms(shard_path, pack_file_dir, pool));
  SVN_ERR(svn_io_set_file_read_only(pack_file_path, FALSE, pool));

  return SVN_NO_ERROR;
}