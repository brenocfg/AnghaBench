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
typedef  int svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char const* apr_psprintf (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  hotcopy_remove_file (char*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_join (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
hotcopy_remove_files(svn_fs_t *dst_fs,
                     const char *dst_subdir,
                     svn_revnum_t start_rev,
                     svn_revnum_t end_rev,
                     int max_files_per_dir,
                     apr_pool_t *scratch_pool)
{
  const char *shard;
  const char *dst_subdir_shard;
  svn_revnum_t rev;
  apr_pool_t *iterpool;

  /* Pre-compute paths for initial shard. */
  shard = apr_psprintf(scratch_pool, "%ld", start_rev / max_files_per_dir);
  dst_subdir_shard = svn_dirent_join(dst_subdir, shard, scratch_pool);

  iterpool = svn_pool_create(scratch_pool);
  for (rev = start_rev; rev < end_rev; rev++)
    {
      svn_pool_clear(iterpool);

      /* If necessary, update paths for shard. */
      if (rev != start_rev && rev % max_files_per_dir == 0)
        {
          shard = apr_psprintf(iterpool, "%ld", rev / max_files_per_dir);
          dst_subdir_shard = svn_dirent_join(dst_subdir, shard, scratch_pool);
        }

      /* remove files for REV */
      SVN_ERR(hotcopy_remove_file(svn_dirent_join(dst_subdir_shard,
                                                  apr_psprintf(iterpool,
                                                               "%ld", rev),
                                                  iterpool),
                                  iterpool));
    }

  svn_pool_destroy(iterpool);

  return SVN_NO_ERROR;
}