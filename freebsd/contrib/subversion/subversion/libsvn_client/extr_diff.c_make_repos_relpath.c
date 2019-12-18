#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_context_t ;
struct TYPE_8__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_WC_PATH_NOT_FOUND ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_dirent_get_absolute (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_join (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_path_is_url (char const*) ; 
 char* svn_relpath_join (char const*,char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc__node_get_repos_info (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
make_repos_relpath(const char **repos_relpath,
                   const char *diff_relpath,
                   const char *orig_target,
                   const char *session_relpath,
                   svn_wc_context_t *wc_ctx,
                   const char *anchor,
                   apr_pool_t *result_pool,
                   apr_pool_t *scratch_pool)
{
  const char *local_abspath;

  if (! session_relpath
      || (anchor && !svn_path_is_url(orig_target)))
    {
      svn_error_t *err;
      /* We're doing a WC-WC diff, so we can retrieve all information we
       * need from the working copy. */
      SVN_ERR(svn_dirent_get_absolute(&local_abspath,
                                      svn_dirent_join(anchor, diff_relpath,
                                                      scratch_pool),
                                      scratch_pool));

      err = svn_wc__node_get_repos_info(NULL, repos_relpath, NULL, NULL,
                                        wc_ctx, local_abspath,
                                        result_pool, scratch_pool);

      if (!session_relpath
          || ! err
          || (err && err->apr_err != SVN_ERR_WC_PATH_NOT_FOUND))
        {
           return svn_error_trace(err);
        }

      /* The path represents a local working copy path, but does not
         exist. Fall through to calculate an in-repository location
         based on the ra session */

      /* ### Maybe we should use the nearest existing ancestor instead? */
      svn_error_clear(err);
    }

  *repos_relpath = svn_relpath_join(session_relpath, diff_relpath,
                                    result_pool);

  return SVN_NO_ERROR;
}