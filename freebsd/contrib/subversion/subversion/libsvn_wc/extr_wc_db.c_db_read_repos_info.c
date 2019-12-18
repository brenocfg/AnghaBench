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
typedef  int /*<<< orphan*/  svn_wc__db_wcroot_t ;
typedef  scalar_t__ svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_int64_t ;

/* Variables and functions */
 scalar_t__ INVALID_REPOS_ID ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_MALFUNCTION () ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  read_info (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scan_addition (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scan_deletion (char const**,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char const* svn_dirent_skip_ancestor (char const*,char const*) ; 
 char* svn_relpath_dirname (char const*,int /*<<< orphan*/ *) ; 
 char* svn_relpath_join (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_relpath_split (char const**,char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_base_get_info_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__db_status_added ; 
 scalar_t__ svn_wc__db_status_deleted ; 
 scalar_t__ svn_wc__db_status_excluded ; 

__attribute__((used)) static svn_error_t *
db_read_repos_info(svn_revnum_t *revision,
                   const char **repos_relpath,
                   apr_int64_t *repos_id,
                   svn_wc__db_wcroot_t *wcroot,
                   const char *local_relpath,
                   apr_pool_t *result_pool,
                   apr_pool_t *scratch_pool)
{
  svn_wc__db_status_t status;

  SVN_ERR(read_info(&status, NULL, revision, repos_relpath, repos_id, NULL,
                    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                    NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                    NULL, NULL, NULL,
                    wcroot, local_relpath, result_pool, scratch_pool));

  if ((repos_relpath && !*repos_relpath)
      || (repos_id && *repos_id == INVALID_REPOS_ID))
    {
      if (status == svn_wc__db_status_added)
        {
          SVN_ERR(scan_addition(NULL, NULL, repos_relpath, repos_id, NULL,
                                NULL, NULL, NULL, NULL, NULL,
                                wcroot, local_relpath,
                                result_pool, scratch_pool));
        }
      else if (status == svn_wc__db_status_deleted)
        {
          const char *base_del_relpath;
          const char *work_del_relpath;

          SVN_ERR(scan_deletion(&base_del_relpath, NULL,
                                &work_del_relpath,
                                NULL, wcroot,
                                local_relpath,
                                scratch_pool,
                                scratch_pool));

          if (work_del_relpath)
            {
              /* The parent of the WORKING delete, must be an addition */
              const char *work_relpath = NULL;

              /* work_del_relpath should not be NULL. However, we have
               * observed instances where that assumption was not met.
               * Bail out in that case instead of crashing with a segfault.
               */
              SVN_ERR_ASSERT(work_del_relpath != NULL);
              work_relpath = svn_relpath_dirname(work_del_relpath,
                                                 scratch_pool);

              SVN_ERR(scan_addition(NULL, NULL, repos_relpath, repos_id,
                                    NULL, NULL, NULL, NULL, NULL, NULL,
                                    wcroot, work_relpath,
                                    scratch_pool, scratch_pool));

              if (repos_relpath)
                *repos_relpath = svn_relpath_join(
                                    *repos_relpath,
                                    svn_dirent_skip_ancestor(work_relpath,
                                                             local_relpath),
                                    result_pool);
            }
          else if (base_del_relpath)
            {
              SVN_ERR(svn_wc__db_base_get_info_internal(NULL, NULL, revision,
                                                        repos_relpath,
                                                        repos_id,
                                                        NULL, NULL, NULL,
                                                        NULL, NULL, NULL,
                                                        NULL, NULL, NULL, NULL,
                                                        wcroot,
                                                        base_del_relpath,
                                                        scratch_pool,
                                                        scratch_pool));

              if (repos_relpath)
                *repos_relpath = svn_relpath_join(
                                    *repos_relpath,
                                    svn_dirent_skip_ancestor(base_del_relpath,
                                                             local_relpath),
                                    result_pool);
            }
          else
            SVN_ERR_MALFUNCTION();
        }
      else if (status == svn_wc__db_status_excluded)
        {
          const char *parent_relpath;
          const char *name;

          /* A BASE excluded would have had repository information, so
             we have a working exclude, which must be below an addition */

          svn_relpath_split(&parent_relpath, &name, local_relpath,
                            scratch_pool);
          SVN_ERR(scan_addition(NULL, NULL, repos_relpath, repos_id, NULL,
                                NULL, NULL, NULL, NULL, NULL,
                                wcroot, parent_relpath,
                                scratch_pool, scratch_pool));

          if (repos_relpath)
            *repos_relpath = svn_relpath_join(*repos_relpath, name,
                                              result_pool);

          return SVN_NO_ERROR;
        }
      else
        {
          /* All working statee are explicitly handled and all base statee
             have a repos_relpath */
          SVN_ERR_MALFUNCTION();
        }
    }

  return SVN_NO_ERROR;
}