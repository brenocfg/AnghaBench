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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  (* svn_cancel_func_t ) (void*) ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  apr_psprintf (int /*<<< orphan*/ *,char*,int) ; 
 char* svn_dirent_join (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_remove_dir2 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (void*),void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_remove_file2 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__delete_revprops_shard(const char *shard_path,
                                 apr_int64_t shard,
                                 int max_files_per_dir,
                                 svn_cancel_func_t cancel_func,
                                 void *cancel_baton,
                                 apr_pool_t *scratch_pool)
{
  if (shard == 0)
    {
      apr_pool_t *iterpool = svn_pool_create(scratch_pool);
      int i;

      /* delete all files except the one for revision 0 */
      for (i = 1; i < max_files_per_dir; ++i)
        {
          const char *path;
          svn_pool_clear(iterpool);

          path = svn_dirent_join(shard_path,
                                 apr_psprintf(iterpool, "%d", i),
                                 iterpool);
          if (cancel_func)
            SVN_ERR(cancel_func(cancel_baton));

          SVN_ERR(svn_io_remove_file2(path, TRUE, iterpool));
        }

      svn_pool_destroy(iterpool);
    }
  else
    SVN_ERR(svn_io_remove_dir2(shard_path, TRUE,
                               cancel_func, cancel_baton, scratch_pool));

  return SVN_NO_ERROR;
}