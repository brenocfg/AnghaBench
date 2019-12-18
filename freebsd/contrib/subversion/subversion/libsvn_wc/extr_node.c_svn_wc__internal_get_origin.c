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
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  scalar_t__ svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_WC_PATH_UNEXPECTED_STATUS ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_skip_ancestor (char const*,char const*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* svn_relpath_join (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_base_get_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,char const**,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_info (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,char const**,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,char const**,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_scan_addition (scalar_t__*,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,char const**,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__db_status_added ; 
 scalar_t__ svn_wc__db_status_deleted ; 
 scalar_t__ svn_wc__db_status_incomplete ; 

svn_error_t *
svn_wc__internal_get_origin(svn_boolean_t *is_copy,
                            svn_revnum_t *revision,
                            const char **repos_relpath,
                            const char **repos_root_url,
                            const char **repos_uuid,
                            svn_depth_t *depth,
                            const char **copy_root_abspath,
                            svn_wc__db_t *db,
                            const char *local_abspath,
                            svn_boolean_t scan_deleted,
                            apr_pool_t *result_pool,
                            apr_pool_t *scratch_pool)
{
  const char *original_repos_relpath;
  const char *original_repos_root_url;
  const char *original_repos_uuid;
  svn_revnum_t original_revision;
  svn_wc__db_status_t status;
  svn_boolean_t have_more_work;
  svn_boolean_t op_root;

  const char *tmp_repos_relpath;

  if (copy_root_abspath)
    *copy_root_abspath = NULL;
  if (!repos_relpath)
    repos_relpath = &tmp_repos_relpath;

  SVN_ERR(svn_wc__db_read_info(&status, NULL, revision, repos_relpath,
                               repos_root_url, repos_uuid, NULL, NULL, NULL,
                               depth, NULL, NULL,
                               &original_repos_relpath,
                               &original_repos_root_url,
                               &original_repos_uuid, &original_revision,
                               NULL, NULL, NULL, NULL, NULL, &op_root, NULL,
                               NULL, NULL, &have_more_work, is_copy,
                               db, local_abspath, result_pool, scratch_pool));

  if (*repos_relpath)
    {
      return SVN_NO_ERROR; /* Returned BASE information */
    }

  if (status == svn_wc__db_status_deleted && !scan_deleted)
    {
      if (is_copy)
        *is_copy = FALSE; /* Deletes are stored in working; default to FALSE */

      return SVN_NO_ERROR; /* No info */
    }

  if (original_repos_relpath)
    {
      /* We an have a copy */
      *repos_relpath = original_repos_relpath;
      if (revision)
        *revision = original_revision;
      if (repos_root_url)
        *repos_root_url = original_repos_root_url;
      if (repos_uuid)
        *repos_uuid = original_repos_uuid;

      if (copy_root_abspath == NULL)
        return SVN_NO_ERROR;
      else if (op_root)
        {
          *copy_root_abspath = apr_pstrdup(result_pool, local_abspath);
          return SVN_NO_ERROR;
        }
    }

  {
    svn_boolean_t scan_working = FALSE;

    if (status == svn_wc__db_status_added
        || (status == svn_wc__db_status_deleted && have_more_work))
      scan_working = TRUE;

    if (scan_working)
      {
        const char *op_root_abspath;

        SVN_ERR(svn_wc__db_scan_addition(&status, &op_root_abspath, NULL,
                                         NULL, NULL, &original_repos_relpath,
                                         repos_root_url,
                                         repos_uuid, revision,
                                         db, local_abspath,
                                         result_pool, scratch_pool));

        if (status == svn_wc__db_status_added)
          {
            if (is_copy)
              *is_copy = FALSE;
            return SVN_NO_ERROR; /* Local addition */
          }

        /* We don't know how the following error condition can be fulfilled
         * but we have seen that happening in the wild.  Better to create
         * an error than a SEGFAULT. */
        if (status == svn_wc__db_status_incomplete && !original_repos_relpath)
          return svn_error_createf(SVN_ERR_WC_PATH_UNEXPECTED_STATUS, NULL,
                               _("Incomplete copy information on path '%s'."),
                                   svn_dirent_local_style(local_abspath,
                                                          scratch_pool));

        *repos_relpath = svn_relpath_join(
                                original_repos_relpath,
                                svn_dirent_skip_ancestor(op_root_abspath,
                                                         local_abspath),
                                result_pool);
        if (copy_root_abspath)
          *copy_root_abspath = op_root_abspath;
      }
    else /* Deleted, excluded, not-present, server-excluded, ... */
      {
        if (is_copy)
          *is_copy = FALSE;

        SVN_ERR(svn_wc__db_base_get_info(NULL, NULL, revision, repos_relpath,
                                         repos_root_url, repos_uuid, NULL,
                                         NULL, NULL, NULL, NULL, NULL, NULL,
                                         NULL, NULL, NULL,
                                         db, local_abspath,
                                         result_pool, scratch_pool));
      }

    return SVN_NO_ERROR;
  }
}