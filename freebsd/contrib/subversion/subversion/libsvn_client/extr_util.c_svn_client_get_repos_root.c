#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_ra_session_t ;
struct TYPE_11__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
struct TYPE_12__ {int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_2__ svn_client_ctx_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_WC_NOT_WORKING_COPY ; 
 scalar_t__ SVN_ERR_WC_PATH_NOT_FOUND ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_client_open_ra_session2 (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_path_is_url (char const*) ; 
 int /*<<< orphan*/  svn_ra_get_repos_root2 (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_get_uuid2 (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc__node_get_repos_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,char const**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client_get_repos_root(const char **repos_root,
                          const char **repos_uuid,
                          const char *abspath_or_url,
                          svn_client_ctx_t *ctx,
                          apr_pool_t *result_pool,
                          apr_pool_t *scratch_pool)
{
  svn_ra_session_t *ra_session;

  /* If PATH_OR_URL is a local path we can fetch the repos root locally. */
  if (!svn_path_is_url(abspath_or_url))
    {
      svn_error_t *err;
      err = svn_wc__node_get_repos_info(NULL, NULL, repos_root, repos_uuid,
                                        ctx->wc_ctx, abspath_or_url,
                                        result_pool, scratch_pool);

      if (err)
        {
          if (err->apr_err != SVN_ERR_WC_PATH_NOT_FOUND
              && err->apr_err != SVN_ERR_WC_NOT_WORKING_COPY)
            return svn_error_trace(err);

          svn_error_clear(err);
          if (repos_root)
            *repos_root = NULL;
          if (repos_uuid)
            *repos_uuid = NULL;
        }
      return SVN_NO_ERROR;
    }

  /* If PATH_OR_URL was a URL, we use the RA layer to look it up. */
  SVN_ERR(svn_client_open_ra_session2(&ra_session,  abspath_or_url, NULL,
                                      ctx, scratch_pool, scratch_pool));

  if (repos_root)
    SVN_ERR(svn_ra_get_repos_root2(ra_session, repos_root, result_pool));
  if (repos_uuid)
    SVN_ERR(svn_ra_get_uuid2(ra_session, repos_uuid, result_pool));

  return SVN_NO_ERROR;
}