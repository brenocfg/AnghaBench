#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  void* svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_proplist_receiver2_t ;
struct TYPE_13__ {void* number; } ;
struct TYPE_14__ {TYPE_1__ value; void* kind; } ;
typedef  TYPE_2__ svn_opt_revision_t ;
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
struct TYPE_15__ {int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_3__ svn_client_ctx_t ;
struct TYPE_16__ {int /*<<< orphan*/  rev; int /*<<< orphan*/  url; } ;
typedef  TYPE_4__ svn_client__pathrev_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SVN_CLIENT__REVKIND_NEEDS_WC (void*) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_CLIENT_VERSIONED_PATH_REQUIRED ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  remote_proplist (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client__get_revision_number (void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client__ra_session_from_path2 (int /*<<< orphan*/ **,TYPE_4__**,char const*,int /*<<< orphan*/ *,TYPE_2__ const*,TYPE_2__ const*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* svn_opt_revision_number ; 
 scalar_t__ svn_path_is_url (char const*) ; 
 char* svn_path_url_add_component2 (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_check_path (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__node_get_origin (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_remote_props(const char *path_or_url,
                 const svn_opt_revision_t *peg_revision,
                 const svn_opt_revision_t *revision,
                 svn_depth_t depth,
                 svn_boolean_t get_explicit_props,
                 svn_boolean_t get_target_inherited_props,
                 svn_proplist_receiver2_t receiver,
                 void *receiver_baton,
                 svn_client_ctx_t *ctx,
                 apr_pool_t *scratch_pool)
{
  svn_ra_session_t *ra_session;
  svn_node_kind_t kind;
  svn_opt_revision_t new_operative_rev;
  svn_opt_revision_t new_peg_rev;
  svn_client__pathrev_t *loc;

  /* Peg or operative revisions may be WC specific for
     PATH_OR_URL's explicit props, but still require us to
     contact the repository for the inherited properties. */
  if (SVN_CLIENT__REVKIND_NEEDS_WC(peg_revision->kind)
      || SVN_CLIENT__REVKIND_NEEDS_WC(revision->kind))
    {
      const char *repos_relpath;
      const char *repos_root_url;
      const char *local_abspath;
      svn_boolean_t is_copy;

      /* Avoid assertion on the next line when somebody accidentally asks for
         a working copy revision on a URL */
      if (svn_path_is_url(path_or_url))
        return svn_error_create(SVN_ERR_CLIENT_VERSIONED_PATH_REQUIRED,
                                NULL, NULL);

      SVN_ERR(svn_dirent_get_absolute(&local_abspath, path_or_url,
                                      scratch_pool));

      if (SVN_CLIENT__REVKIND_NEEDS_WC(peg_revision->kind))
        {
          SVN_ERR(svn_wc__node_get_origin(&is_copy,
                                          NULL,
                                          &repos_relpath,
                                          &repos_root_url,
                                          NULL, NULL, NULL,
                                          ctx->wc_ctx,
                                          local_abspath,
                                          FALSE, /* scan_deleted */
                                          scratch_pool,
                                          scratch_pool));
          if (repos_relpath)
            {
              path_or_url =
                svn_path_url_add_component2(repos_root_url,
                                            repos_relpath,
                                            scratch_pool);
              if (SVN_CLIENT__REVKIND_NEEDS_WC(peg_revision->kind))
                {
                  svn_revnum_t resolved_peg_rev;

                  SVN_ERR(svn_client__get_revision_number(&resolved_peg_rev,
                                                          NULL, ctx->wc_ctx,
                                                          local_abspath, NULL,
                                                          peg_revision,
                                                          scratch_pool));
                  new_peg_rev.kind = svn_opt_revision_number;
                  new_peg_rev.value.number = resolved_peg_rev;
                  peg_revision = &new_peg_rev;
                }

              if (SVN_CLIENT__REVKIND_NEEDS_WC(revision->kind))
                {
                  svn_revnum_t resolved_operative_rev;

                  SVN_ERR(svn_client__get_revision_number(
                    &resolved_operative_rev,
                    NULL, ctx->wc_ctx,
                    local_abspath, NULL,
                    revision,
                    scratch_pool));
                  new_operative_rev.kind = svn_opt_revision_number;
                  new_operative_rev.value.number = resolved_operative_rev;
                  revision = &new_operative_rev;
                }
            }
          else
            {
                  /* PATH_OR_URL doesn't exist in the repository, so there are
                     obviously not inherited props to be found there. If we
                     aren't looking for explicit props then we're done. */
                  if (!get_explicit_props)
                    return SVN_NO_ERROR;
            }
        }
    }

  /* Get an RA session for this URL. */
  SVN_ERR(svn_client__ra_session_from_path2(&ra_session, &loc,
                                            path_or_url, NULL,
                                            peg_revision,
                                            revision, ctx,
                                            scratch_pool));

  SVN_ERR(svn_ra_check_path(ra_session, "", loc->rev, &kind,
                            scratch_pool));

  SVN_ERR(remote_proplist(loc->url, "", kind, loc->rev, ra_session,
                          get_explicit_props,
                          get_target_inherited_props,
                          depth, receiver, receiver_baton,
                          ctx->cancel_func, ctx->cancel_baton,
                          scratch_pool));
  return SVN_NO_ERROR;
}