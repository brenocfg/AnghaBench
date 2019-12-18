#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_44__   TYPE_5__ ;
typedef  struct TYPE_43__   TYPE_4__ ;
typedef  struct TYPE_42__   TYPE_3__ ;
typedef  struct TYPE_41__   TYPE_2__ ;
typedef  struct TYPE_40__   TYPE_1__ ;

/* Type definitions */
typedef  void* svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_prop_inherited_item_t ;
struct TYPE_40__ {void* number; } ;
struct TYPE_41__ {scalar_t__ kind; TYPE_1__ value; } ;
typedef  TYPE_2__ svn_opt_revision_t ;
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_42__ {scalar_t__ apr_err; } ;
typedef  TYPE_3__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
struct TYPE_43__ {int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_4__ svn_client_ctx_t ;
struct TYPE_44__ {void* rev; int /*<<< orphan*/  url; } ;
typedef  TYPE_5__ svn_client__pathrev_t ;
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SVN_CLIENT__REVKIND_IS_LOCAL_TO_WC (scalar_t__) ; 
 scalar_t__ SVN_CLIENT__REVKIND_NEEDS_WC (scalar_t__) ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_3__*) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_CLIENT_BAD_REVISION ; 
 int /*<<< orphan*/  SVN_ERR_CLIENT_VERSIONED_PATH_REQUIRED ; 
 int /*<<< orphan*/  SVN_ERR_UNVERSIONED_RESOURCE ; 
 void* SVN_INVALID_REVNUM ; 
 TYPE_3__* SVN_NO_ERROR ; 
 int TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_array_make (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 TYPE_3__* error_if_wcprop_name (char const*) ; 
 TYPE_3__* get_prop_from_wc (int /*<<< orphan*/ **,char const*,char const*,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_cl__rev_default_to_head_or_working (TYPE_2__ const*,char const*) ; 
 TYPE_2__* svn_cl__rev_default_to_peg (TYPE_2__ const*,TYPE_2__ const*) ; 
 TYPE_3__* svn_client__get_revision_number (void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_client__iprop_relpaths_to_urls (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_client__ra_session_from_path2 (int /*<<< orphan*/ **,TYPE_5__**,char const*,int /*<<< orphan*/ *,TYPE_2__ const*,TYPE_2__ const*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_client__remote_propget (int /*<<< orphan*/ *,int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,char*,scalar_t__,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_client_get_repos_root (char const**,int /*<<< orphan*/ *,char const*,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_3__*) ; 
 TYPE_3__* svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* svn_error_trace (TYPE_3__*) ; 
 scalar_t__ svn_node_none ; 
 scalar_t__ svn_node_unknown ; 
 scalar_t__ svn_opt_revision_base ; 
 scalar_t__ svn_opt_revision_committed ; 
 void* svn_opt_revision_number ; 
 scalar_t__ svn_opt_revision_unspecified ; 
 scalar_t__ svn_opt_revision_working ; 
 scalar_t__ svn_path_is_url (char const*) ; 
 char* svn_path_url_add_component2 (char const*,char const*,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_ra_check_path (int /*<<< orphan*/ *,char*,void*,scalar_t__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_wc__get_iprops (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_wc__node_get_origin (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_wc_read_kind2 (scalar_t__*,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client_propget5(apr_hash_t **props,
                    apr_array_header_t **inherited_props,
                    const char *propname,
                    const char *target,
                    const svn_opt_revision_t *peg_revision,
                    const svn_opt_revision_t *revision,
                    svn_revnum_t *actual_revnum,
                    svn_depth_t depth,
                    const apr_array_header_t *changelists,
                    svn_client_ctx_t *ctx,
                    apr_pool_t *result_pool,
                    apr_pool_t *scratch_pool)
{
  svn_revnum_t revnum;
  svn_boolean_t local_explicit_props;
  svn_boolean_t local_iprops;

  SVN_ERR(error_if_wcprop_name(propname));
  if (!svn_path_is_url(target))
    SVN_ERR_ASSERT(svn_dirent_is_absolute(target));

  peg_revision = svn_cl__rev_default_to_head_or_working(peg_revision,
                                                        target);
  revision = svn_cl__rev_default_to_peg(revision, peg_revision);

  local_explicit_props =
    (! svn_path_is_url(target)
     && SVN_CLIENT__REVKIND_IS_LOCAL_TO_WC(peg_revision->kind)
     && SVN_CLIENT__REVKIND_IS_LOCAL_TO_WC(revision->kind));

  local_iprops =
    (local_explicit_props
     && (peg_revision->kind == svn_opt_revision_working
         || peg_revision->kind == svn_opt_revision_unspecified )
     && (revision->kind == svn_opt_revision_working
         || revision->kind == svn_opt_revision_unspecified ));

  if (local_explicit_props)
    {
      svn_node_kind_t kind;
      svn_boolean_t pristine;
      svn_error_t *err;

      /* If FALSE, we want the working revision. */
      pristine = (revision->kind == svn_opt_revision_committed
                  || revision->kind == svn_opt_revision_base);

      SVN_ERR(svn_wc_read_kind2(&kind, ctx->wc_ctx, target,
                                pristine, FALSE,
                                scratch_pool));

      if (kind == svn_node_unknown || kind == svn_node_none)
        {
          /* svn uses SVN_ERR_UNVERSIONED_RESOURCE as warning only
             for this function. */
          return svn_error_createf(SVN_ERR_UNVERSIONED_RESOURCE, NULL,
                                   _("'%s' is not under version control"),
                                   svn_dirent_local_style(target,
                                                          scratch_pool));
        }

      err = svn_client__get_revision_number(&revnum, NULL, ctx->wc_ctx,
                                            target, NULL, revision,
                                            scratch_pool);
      if (err && err->apr_err == SVN_ERR_CLIENT_BAD_REVISION)
        {
          svn_error_clear(err);
          revnum = SVN_INVALID_REVNUM;
        }
      else if (err)
        return svn_error_trace(err);

      if (inherited_props && local_iprops)
        {
          const char *repos_root_url;

          SVN_ERR(svn_wc__get_iprops(inherited_props, ctx->wc_ctx,
                                     target, propname,
                                     result_pool, scratch_pool));
          SVN_ERR(svn_client_get_repos_root(&repos_root_url, NULL,
                                            target, ctx, scratch_pool,
                                            scratch_pool));
          SVN_ERR(svn_client__iprop_relpaths_to_urls(*inherited_props,
                                                     repos_root_url,
                                                     result_pool,
                                                     scratch_pool));
        }

      SVN_ERR(get_prop_from_wc(props, propname, target,
                               pristine, kind,
                               depth, changelists, ctx, result_pool,
                               scratch_pool));
    }

  if ((inherited_props && !local_iprops)
      || !local_explicit_props)
    {
      svn_ra_session_t *ra_session;
      svn_node_kind_t kind;
      svn_opt_revision_t new_operative_rev;
      svn_opt_revision_t new_peg_rev;

      /* Peg or operative revisions may be WC specific for
         TARGET's explicit props, but still require us to
         contact the repository for the inherited properties. */
      if (SVN_CLIENT__REVKIND_NEEDS_WC(peg_revision->kind)
          || SVN_CLIENT__REVKIND_NEEDS_WC(revision->kind))
        {
          const char *repos_relpath;
          const char *repos_root_url;
          const char *local_abspath;

          /* Avoid assertion on the next line when somebody accidentally asks for
             a working copy revision on a URL */
          if (svn_path_is_url(target))
            return svn_error_create(SVN_ERR_CLIENT_VERSIONED_PATH_REQUIRED,
                                    NULL, NULL);

          SVN_ERR_ASSERT(svn_dirent_is_absolute(target));
          local_abspath = target;

          if (SVN_CLIENT__REVKIND_NEEDS_WC(peg_revision->kind))
            {
              SVN_ERR(svn_wc__node_get_origin(NULL, NULL,
                                              &repos_relpath,
                                              &repos_root_url,
                                              NULL, NULL, NULL,
                                              ctx->wc_ctx,
                                              local_abspath,
                                              FALSE, /* scan_deleted */
                                              result_pool,
                                              scratch_pool));
              if (repos_relpath)
                {
                  target = svn_path_url_add_component2(repos_root_url,
                                                       repos_relpath,
                                                       scratch_pool);
                  if (SVN_CLIENT__REVKIND_NEEDS_WC(peg_revision->kind))
                    {
                      svn_revnum_t resolved_peg_rev;

                      SVN_ERR(svn_client__get_revision_number(
                        &resolved_peg_rev, NULL, ctx->wc_ctx,
                        local_abspath, NULL, peg_revision, scratch_pool));
                      new_peg_rev.kind = svn_opt_revision_number;
                      new_peg_rev.value.number = resolved_peg_rev;
                      peg_revision = &new_peg_rev;
                    }

                  if (SVN_CLIENT__REVKIND_NEEDS_WC(revision->kind))
                    {
                      svn_revnum_t resolved_operative_rev;

                      SVN_ERR(svn_client__get_revision_number(
                        &resolved_operative_rev, NULL, ctx->wc_ctx,
                        local_abspath, NULL, revision, scratch_pool));
                      new_operative_rev.kind = svn_opt_revision_number;
                      new_operative_rev.value.number = resolved_operative_rev;
                      revision = &new_operative_rev;
                    }
                }
              else
                {
                  /* TARGET doesn't exist in the repository, so there are
                     obviously not inherited props to be found there. */
                  local_iprops = TRUE;
                  *inherited_props = apr_array_make(
                    result_pool, 0, sizeof(svn_prop_inherited_item_t *));
                }
            }
        }

      /* Do we still have anything to ask the repository about? */
      if (!local_explicit_props || !local_iprops)
        {
          svn_client__pathrev_t *loc;

          /* Get an RA plugin for this filesystem object. */
          SVN_ERR(svn_client__ra_session_from_path2(&ra_session, &loc,
                                                    target, NULL,
                                                    peg_revision,
                                                    revision, ctx,
                                                    scratch_pool));

          SVN_ERR(svn_ra_check_path(ra_session, "", loc->rev, &kind,
                                    scratch_pool));

          if (!local_explicit_props)
            *props = apr_hash_make(result_pool);

          SVN_ERR(svn_client__remote_propget(
                                 !local_explicit_props ? *props : NULL,
                                 !local_iprops ? inherited_props : NULL,
                                 propname, loc->url, "",
                                 kind, loc->rev, ra_session,
                                 depth, result_pool, scratch_pool));
          revnum = loc->rev;
        }
    }

  if (actual_revnum)
    *actual_revnum = revnum;
  return SVN_NO_ERROR;
}