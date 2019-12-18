#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_opt_revision_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
struct TYPE_4__ {int /*<<< orphan*/  url; } ;
typedef  TYPE_1__ svn_client__pathrev_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ENTRY_MISSING_URL ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  svn_client__open_ra_session_internal (int /*<<< orphan*/ **,char const**,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client__resolve_rev_and_url (TYPE_1__**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_url_from_path2 (char const**,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ svn_path_is_url (char const*) ; 
 int /*<<< orphan*/  svn_ra_reparent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client__ra_session_from_path2(svn_ra_session_t **ra_session_p,
                                  svn_client__pathrev_t **resolved_loc_p,
                                  const char *path_or_url,
                                  const char *base_dir_abspath,
                                  const svn_opt_revision_t *peg_revision,
                                  const svn_opt_revision_t *revision,
                                  svn_client_ctx_t *ctx,
                                  apr_pool_t *pool)
{
  svn_ra_session_t *ra_session;
  const char *initial_url;
  const char *corrected_url;
  svn_client__pathrev_t *resolved_loc;
  const char *wri_abspath;

  SVN_ERR(svn_client_url_from_path2(&initial_url, path_or_url, ctx, pool,
                                    pool));
  if (! initial_url)
    return svn_error_createf(SVN_ERR_ENTRY_MISSING_URL, NULL,
                             _("'%s' has no URL"), path_or_url);

  if (base_dir_abspath)
    wri_abspath = base_dir_abspath;
  else if (!svn_path_is_url(path_or_url))
    SVN_ERR(svn_dirent_get_absolute(&wri_abspath, path_or_url, pool));
  else
    wri_abspath = NULL;

  SVN_ERR(svn_client__open_ra_session_internal(&ra_session, &corrected_url,
                                               initial_url,
                                               wri_abspath,
                                               NULL /* commit_items */,
                                               base_dir_abspath != NULL,
                                               base_dir_abspath != NULL,
                                               ctx, pool, pool));

  /* If we got a CORRECTED_URL, we'll want to refer to that as the
     URL-ized form of PATH_OR_URL from now on. */
  if (corrected_url && svn_path_is_url(path_or_url))
    path_or_url = corrected_url;

  SVN_ERR(svn_client__resolve_rev_and_url(&resolved_loc, ra_session,
                                          path_or_url, peg_revision, revision,
                                          ctx, pool));

  /* Make the session point to the real URL. */
  SVN_ERR(svn_ra_reparent(ra_session, resolved_loc->url, pool));

  *ra_session_p = ra_session;
  if (resolved_loc_p)
    *resolved_loc_p = resolved_loc;

  return SVN_NO_ERROR;
}