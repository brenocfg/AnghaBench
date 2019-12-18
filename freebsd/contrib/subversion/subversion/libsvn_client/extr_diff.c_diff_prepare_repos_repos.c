#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
struct TYPE_31__ {int kind; } ;
typedef  TYPE_1__ svn_opt_revision_t ;
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_32__ {scalar_t__ apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
struct TYPE_33__ {int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_3__ svn_client_ctx_t ;
struct TYPE_34__ {char* url; int /*<<< orphan*/  rev; } ;
typedef  TYPE_4__ svn_client__pathrev_t ;
typedef  enum svn_opt_revision_kind { ____Placeholder_svn_opt_revision_kind } svn_opt_revision_kind ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (TYPE_2__*) ; 
 scalar_t__ SVN_ERR_CLIENT_UNRELATED_RESOURCES ; 
 scalar_t__ SVN_ERR_FS_NOT_FOUND ; 
 scalar_t__ SVN_ERR_RA_DAV_FORBIDDEN ; 
 scalar_t__ SVN_ERR_RA_NOT_AUTHORIZED ; 
 TYPE_2__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 TYPE_2__* check_diff_target_exists (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 TYPE_2__* svn_client__get_revision_number (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_client__resolve_rev_and_url (TYPE_4__**,int /*<<< orphan*/ *,char const*,TYPE_1__ const*,TYPE_1__ const*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_client_open_ra_session2 (int /*<<< orphan*/ **,char const*,char const*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 TYPE_2__* svn_error_createf (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,...) ; 
 TYPE_2__* svn_error_trace (TYPE_2__*) ; 
 scalar_t__ svn_node_none ; 
 int svn_opt_revision_unspecified ; 
 int /*<<< orphan*/  svn_path_is_url (char const*) ; 
 char* svn_path_url_add_component2 (char const*,char const*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_ra_check_path (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_ra_get_repos_root2 (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_ra_reparent (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_uri_split (char const**,char const**,char const*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc__node_get_url (char const**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
diff_prepare_repos_repos(const char **url1,
                         const char **url2,
                         svn_revnum_t *rev1,
                         svn_revnum_t *rev2,
                         const char **anchor1,
                         const char **anchor2,
                         const char **target1,
                         const char **target2,
                         svn_node_kind_t *kind1,
                         svn_node_kind_t *kind2,
                         svn_ra_session_t **ra_session,
                         svn_client_ctx_t *ctx,
                         const char *path_or_url1,
                         const char *path_or_url2,
                         const svn_opt_revision_t *revision1,
                         const svn_opt_revision_t *revision2,
                         const svn_opt_revision_t *peg_revision,
                         apr_pool_t *pool)
{
  const char *local_abspath1 = NULL;
  const char *local_abspath2 = NULL;
  const char *repos_root_url;
  const char *wri_abspath = NULL;
  svn_client__pathrev_t *resolved1;
  svn_client__pathrev_t *resolved2 = NULL;
  enum svn_opt_revision_kind peg_kind = peg_revision->kind;

  if (!svn_path_is_url(path_or_url2))
    {
      SVN_ERR(svn_dirent_get_absolute(&local_abspath2, path_or_url2, pool));
      SVN_ERR(svn_wc__node_get_url(url2, ctx->wc_ctx, local_abspath2,
                                   pool, pool));
      wri_abspath = local_abspath2;
    }
  else
    *url2 = apr_pstrdup(pool, path_or_url2);

  if (!svn_path_is_url(path_or_url1))
    {
      SVN_ERR(svn_dirent_get_absolute(&local_abspath1, path_or_url1, pool));
      wri_abspath = local_abspath1;
    }

  SVN_ERR(svn_client_open_ra_session2(ra_session, *url2, wri_abspath,
                                      ctx, pool, pool));

  /* If we are performing a pegged diff, we need to find out what our
     actual URLs will be. */
  if (peg_kind != svn_opt_revision_unspecified
      || path_or_url1 == path_or_url2
      || local_abspath2)
    {
      svn_error_t *err;

      err = svn_client__resolve_rev_and_url(&resolved2,
                                            *ra_session, path_or_url2,
                                            peg_revision, revision2,
                                            ctx, pool);
      if (err)
        {
          if (err->apr_err != SVN_ERR_CLIENT_UNRELATED_RESOURCES
              && err->apr_err != SVN_ERR_FS_NOT_FOUND)
            return svn_error_trace(err);

          svn_error_clear(err);
          resolved2 = NULL;
        }
    }
  else
    resolved2 = NULL;

  if (peg_kind != svn_opt_revision_unspecified
      || path_or_url1 == path_or_url2
      || local_abspath1)
    {
      svn_error_t *err;

      err = svn_client__resolve_rev_and_url(&resolved1,
                                            *ra_session, path_or_url1,
                                            peg_revision, revision1,
                                            ctx, pool);
      if (err)
        {
          if (err->apr_err != SVN_ERR_CLIENT_UNRELATED_RESOURCES
              && err->apr_err != SVN_ERR_FS_NOT_FOUND)
            return svn_error_trace(err);

          svn_error_clear(err);
          resolved1 = NULL;
        }
    }
  else
    resolved1 = NULL;

  if (resolved1)
    {
      *url1 = resolved1->url;
      *rev1 = resolved1->rev;
    }
  else
    {
      /* It would be nice if we could just return an error when resolving a
         location fails... But in many such cases we prefer diffing against
         an not existing location to show adds od removes (see issue #4153) */

      if (resolved2
          && (peg_kind != svn_opt_revision_unspecified
              || path_or_url1 == path_or_url2))
        *url1 = resolved2->url;
      else if (! local_abspath1)
        *url1 = path_or_url1;
      else
        SVN_ERR(svn_wc__node_get_url(url1, ctx->wc_ctx, local_abspath1,
                                     pool, pool));

      SVN_ERR(svn_client__get_revision_number(rev1, NULL, ctx->wc_ctx,
                                              local_abspath1 /* may be NULL */,
                                              *ra_session, revision1, pool));
    }

  if (resolved2)
    {
      *url2 = resolved2->url;
      *rev2 = resolved2->rev;
    }
  else
    {
      /* It would be nice if we could just return an error when resolving a
         location fails... But in many such cases we prefer diffing against
         an not existing location to show adds od removes (see issue #4153) */

      if (resolved1
          && (peg_kind != svn_opt_revision_unspecified
              || path_or_url1 == path_or_url2))
        *url2 = resolved1->url;
      /* else keep url2 */

      SVN_ERR(svn_client__get_revision_number(rev2, NULL, ctx->wc_ctx,
                                              local_abspath2 /* may be NULL */,
                                              *ra_session, revision2, pool));
    }

  /* Resolve revision and get path kind for the second target. */
  SVN_ERR(svn_ra_reparent(*ra_session, *url2, pool));
  SVN_ERR(svn_ra_check_path(*ra_session, "", *rev2, kind2, pool));

  /* Do the same for the first target. */
  SVN_ERR(svn_ra_reparent(*ra_session, *url1, pool));
  SVN_ERR(svn_ra_check_path(*ra_session, "", *rev1, kind1, pool));

  /* Either both URLs must exist at their respective revisions,
   * or one of them may be missing from one side of the diff. */
  if (*kind1 == svn_node_none && *kind2 == svn_node_none)
    {
      if (strcmp(*url1, *url2) == 0)
        return svn_error_createf(SVN_ERR_FS_NOT_FOUND, NULL,
                                 _("Diff target '%s' was not found in the "
                                   "repository at revisions '%ld' and '%ld'"),
                                 *url1, *rev1, *rev2);
      else
        return svn_error_createf(SVN_ERR_FS_NOT_FOUND, NULL,
                                 _("Diff targets '%s' and '%s' were not found "
                                   "in the repository at revisions '%ld' and "
                                   "'%ld'"),
                                 *url1, *url2, *rev1, *rev2);
    }
  else if (*kind1 == svn_node_none)
    SVN_ERR(check_diff_target_exists(*url1, *rev2, *rev1, *ra_session, pool));
  else if (*kind2 == svn_node_none)
    SVN_ERR(check_diff_target_exists(*url2, *rev1, *rev2, *ra_session, pool));

  SVN_ERR(svn_ra_get_repos_root2(*ra_session, &repos_root_url, pool));

  /* Choose useful anchors and targets for our two URLs. */
  *anchor1 = *url1;
  *anchor2 = *url2;
  *target1 = "";
  *target2 = "";

  /* If none of the targets is the repository root open the parent directory
     to allow describing replacement of the target itself */
  if (strcmp(*url1, repos_root_url) != 0
      && strcmp(*url2, repos_root_url) != 0)
    {
      svn_node_kind_t ignored_kind;
      svn_error_t *err;

      svn_uri_split(anchor1, target1, *url1, pool);
      svn_uri_split(anchor2, target2, *url2, pool);

      SVN_ERR(svn_ra_reparent(*ra_session, *anchor1, pool));

      /* We might not have the necessary rights to read the root now.
         (It is ok to pass a revision here where the node doesn't exist) */
      err = svn_ra_check_path(*ra_session, "", *rev1, &ignored_kind, pool);

      if (err && (err->apr_err == SVN_ERR_RA_DAV_FORBIDDEN
                  || err->apr_err == SVN_ERR_RA_NOT_AUTHORIZED))
        {
          svn_error_clear(err);

          /* Ok, lets undo the reparent...

             We can't report replacements this way, but at least we can
             report changes on the descendants */

          *anchor1 = svn_path_url_add_component2(*anchor1, *target1, pool);
          *anchor2 = svn_path_url_add_component2(*anchor2, *target2, pool);
          *target1 = "";
          *target2 = "";

          SVN_ERR(svn_ra_reparent(*ra_session, *anchor1, pool));
        }
      else
        SVN_ERR(err);
    }

  return SVN_NO_ERROR;
}