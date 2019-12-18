#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_44__   TYPE_4__ ;
typedef  struct TYPE_43__   TYPE_3__ ;
typedef  struct TYPE_42__   TYPE_2__ ;
typedef  struct TYPE_41__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
struct TYPE_41__ {int /*<<< orphan*/  number; } ;
struct TYPE_42__ {scalar_t__ kind; TYPE_1__ value; } ;
typedef  TYPE_2__ svn_opt_revision_t ;
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_43__ {scalar_t__ apr_err; } ;
typedef  TYPE_3__ svn_error_t ;
struct TYPE_44__ {int /*<<< orphan*/  wc_ctx; int /*<<< orphan*/  notify_baton2; int /*<<< orphan*/  notify_func2; int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; } ;
typedef  TYPE_4__ svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_3__*) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_CLIENT_INVALID_RELOCATION ; 
 scalar_t__ SVN_ERR_WC_INVALID_RELOCATION ; 
 scalar_t__ SVN_ERR_WC_NOT_WORKING_COPY ; 
 scalar_t__ SVN_ERR_WC_PATH_NOT_FOUND ; 
 int /*<<< orphan*/  SVN_ERR_WC_PATH_UNEXPECTED_STATUS ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 TYPE_3__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_EXTERNALS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_3__* relegate_dir_external (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 TYPE_3__* svn_client__checkout_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*,TYPE_2__ const*,TYPE_2__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_client__switch_internal (int /*<<< orphan*/ *,char const*,char const*,TYPE_2__ const*,TYPE_2__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_client__update_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,TYPE_2__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_client_get_repos_root (char const**,int /*<<< orphan*/ *,char const*,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_client_relocate2 (char const*,char const*,char const*,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_depth_infinity ; 
 int /*<<< orphan*/  svn_depth_unknown ; 
 char* svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_3__*) ; 
 TYPE_3__* svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* svn_error_trace (TYPE_3__*) ; 
 TYPE_3__* svn_io_check_path (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_io_make_dir_recursively (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_unknown ; 
 scalar_t__ svn_opt_revision_number ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_uri__is_ancestor (char const*,char const*) ; 
 int /*<<< orphan*/  svn_uri_skip_ancestor (char const*,char const*,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_wc__close_db (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_wc__external_register (int /*<<< orphan*/ ,char const*,char const*,scalar_t__,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_wc__external_remove (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_wc__get_wcroot (char const**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_wc__is_wcroot (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_wc__node_get_base (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_wc__node_get_repos_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,char const**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_wc__node_get_url (char const**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
switch_dir_external(const char *local_abspath,
                    const char *url,
                    const char *url_from_externals_definition,
                    const svn_opt_revision_t *peg_revision,
                    const svn_opt_revision_t *revision,
                    const char *defining_abspath,
                    svn_boolean_t *timestamp_sleep,
                    svn_ra_session_t *ra_session,
                    svn_client_ctx_t *ctx,
                    apr_pool_t *pool)
{
  svn_node_kind_t kind;
  svn_error_t *err;
  svn_revnum_t external_peg_rev = SVN_INVALID_REVNUM;
  svn_revnum_t external_rev = SVN_INVALID_REVNUM;
  apr_pool_t *subpool = svn_pool_create(pool);
  const char *repos_root_url;
  const char *repos_uuid;

  SVN_ERR_ASSERT(svn_dirent_is_absolute(local_abspath));

  if (peg_revision->kind == svn_opt_revision_number)
    external_peg_rev = peg_revision->value.number;

  if (revision->kind == svn_opt_revision_number)
    external_rev = revision->value.number;

  /*
   * The code below assumes existing versioned paths are *not* part of
   * the external's defining working copy.
   * The working copy library does not support registering externals
   * on top of existing BASE nodes and will error out if we try.
   * So if the external target is part of the defining working copy's
   * BASE tree, don't attempt to create the external. Doing so would
   * leave behind a switched path instead of an external (since the
   * switch succeeds but registration of the external in the DB fails).
   * The working copy then cannot be updated until the path is switched back.
   * See issue #4085.
   */
  SVN_ERR(svn_wc__node_get_base(&kind, NULL, NULL,
                                &repos_root_url, &repos_uuid,
                                NULL, ctx->wc_ctx, local_abspath,
                                TRUE, /* ignore_enoent */
                                pool, pool));
  if (kind != svn_node_unknown)
    {
      const char *wcroot_abspath;
      const char *defining_wcroot_abspath;

      SVN_ERR(svn_wc__get_wcroot(&wcroot_abspath, ctx->wc_ctx,
                                 local_abspath, pool, pool));
      SVN_ERR(svn_wc__get_wcroot(&defining_wcroot_abspath, ctx->wc_ctx,
                                 defining_abspath, pool, pool));
      if (strcmp(wcroot_abspath, defining_wcroot_abspath) == 0)
        return svn_error_createf(SVN_ERR_WC_PATH_UNEXPECTED_STATUS, NULL,
                                 _("The external '%s' defined in %s at '%s' "
                                   "cannot be checked out because '%s' is "
                                   "already a versioned path."),
                                   url_from_externals_definition,
                                   SVN_PROP_EXTERNALS,
                                   svn_dirent_local_style(defining_abspath,
                                                          pool),
                                   svn_dirent_local_style(local_abspath,
                                                          pool));
    }

  /* If path is a directory, try to update/switch to the correct URL
     and revision. */
  SVN_ERR(svn_io_check_path(local_abspath, &kind, pool));
  if (kind == svn_node_dir)
    {
      const char *node_url;

      /* Doubles as an "is versioned" check. */
      err = svn_wc__node_get_url(&node_url, ctx->wc_ctx, local_abspath,
                                 pool, subpool);
      if (err && err->apr_err == SVN_ERR_WC_PATH_NOT_FOUND)
        {
          svn_error_clear(err);
          err = SVN_NO_ERROR;
          goto relegate;
        }
      else if (err)
        return svn_error_trace(err);

      if (node_url)
        {
          svn_boolean_t is_wcroot;

          SVN_ERR(svn_wc__is_wcroot(&is_wcroot, ctx->wc_ctx, local_abspath,
                                    pool));

          if (! is_wcroot)
          {
            /* This can't be a directory external! */

            err = svn_wc__external_remove(ctx->wc_ctx, defining_abspath,
                                          local_abspath,
                                          TRUE /* declaration_only */,
                                          ctx->cancel_func, ctx->cancel_baton,
                                          pool);

            if (err && err->apr_err == SVN_ERR_WC_PATH_NOT_FOUND)
              {
                /* New external... No problem that we can't remove it */
                svn_error_clear(err);
                err = NULL;
              }
            else if (err)
              return svn_error_trace(err);

            return svn_error_createf(SVN_ERR_WC_PATH_UNEXPECTED_STATUS, NULL,
                                     _("The external '%s' defined in %s at '%s' "
                                       "cannot be checked out because '%s' is "
                                       "already a versioned path."),
                                     url_from_externals_definition,
                                     SVN_PROP_EXTERNALS,
                                     svn_dirent_local_style(defining_abspath,
                                                            pool),
                                     svn_dirent_local_style(local_abspath,
                                                            pool));
          }

          /* If we have what appears to be a version controlled
             subdir, and its top-level URL matches that of our
             externals definition, perform an update. */
          if (strcmp(node_url, url) == 0)
            {
              SVN_ERR(svn_client__update_internal(NULL, timestamp_sleep,
                                                  local_abspath,
                                                  revision, svn_depth_unknown,
                                                  FALSE, FALSE, FALSE, TRUE,
                                                  FALSE, TRUE,
                                                  ra_session, ctx, subpool));

              /* We just decided that this existing directory is an external,
                 so update the external registry with this information, like
                 when checking out an external */
              SVN_ERR(svn_wc__external_register(ctx->wc_ctx,
                                    defining_abspath,
                                    local_abspath, svn_node_dir,
                                    repos_root_url, repos_uuid,
                                    svn_uri_skip_ancestor(repos_root_url,
                                                          url, pool),
                                    external_peg_rev,
                                    external_rev,
                                    pool));

              svn_pool_destroy(subpool);
              goto cleanup;
            }

          /* We'd really prefer not to have to do a brute-force
             relegation -- blowing away the current external working
             copy and checking it out anew -- so we'll first see if we
             can get away with a generally cheaper relocation (if
             required) and switch-style update.

             To do so, we need to know the repository root URL of the
             external working copy as it currently sits. */
          err = svn_wc__node_get_repos_info(NULL, NULL,
                                            &repos_root_url, &repos_uuid,
                                            ctx->wc_ctx, local_abspath,
                                            pool, subpool);
          if (err)
            {
              if (err->apr_err != SVN_ERR_WC_PATH_NOT_FOUND
                  && err->apr_err != SVN_ERR_WC_NOT_WORKING_COPY)
                return svn_error_trace(err);

              svn_error_clear(err);
              repos_root_url = NULL;
              repos_uuid = NULL;
            }

          if (repos_root_url)
            {
              /* If the new external target URL is not obviously a
                 child of the external working copy's current
                 repository root URL... */
              if (! svn_uri__is_ancestor(repos_root_url, url))
                {
                  const char *repos_root;

                  /* ... then figure out precisely which repository
                      root URL that target URL *is* a child of ... */
                  SVN_ERR(svn_client_get_repos_root(&repos_root, NULL, url,
                                                    ctx, subpool, subpool));

                  /* ... and use that to try to relocate the external
                     working copy to the target location.  */
                  err = svn_client_relocate2(local_abspath, repos_root_url,
                                             repos_root, FALSE, ctx, subpool);

                  /* If the relocation failed because the new URL
                     points to a totally different repository, we've
                     no choice but to relegate and check out a new WC. */
                  if (err
                      && (err->apr_err == SVN_ERR_WC_INVALID_RELOCATION
                          || (err->apr_err
                              == SVN_ERR_CLIENT_INVALID_RELOCATION)))
                    {
                      svn_error_clear(err);
                      goto relegate;
                    }
                  else if (err)
                    return svn_error_trace(err);

                  /* If the relocation went without a hitch, we should
                     have a new repository root URL. */
                  repos_root_url = repos_root;
                }

              SVN_ERR(svn_client__switch_internal(NULL, local_abspath, url,
                                                  peg_revision, revision,
                                                  svn_depth_infinity,
                                                  TRUE, FALSE, FALSE,
                                                  TRUE /* ignore_ancestry */,
                                                  timestamp_sleep,
                                                  ctx, subpool));

              SVN_ERR(svn_wc__external_register(ctx->wc_ctx,
                                                defining_abspath,
                                                local_abspath, svn_node_dir,
                                                repos_root_url, repos_uuid,
                                                svn_uri_skip_ancestor(
                                                            repos_root_url,
                                                            url, subpool),
                                                external_peg_rev,
                                                external_rev,
                                                subpool));

              svn_pool_destroy(subpool);
              goto cleanup;
            }
        }
    }

 relegate:

  /* Fall back on removing the WC and checking out a new one. */

  /* Ensure that we don't have any RA sessions or WC locks from failed
     operations above. */
  svn_pool_destroy(subpool);

  if (kind == svn_node_dir)
    {
      /* Buh-bye, old and busted ... */
      SVN_ERR(relegate_dir_external(ctx->wc_ctx, defining_abspath,
                                    local_abspath,
                                    ctx->cancel_func, ctx->cancel_baton,
                                    ctx->notify_func2, ctx->notify_baton2,
                                    pool));
    }
  else
    {
      /* The target dir might have multiple components.  Guarantee
         the path leading down to the last component. */
      const char *parent = svn_dirent_dirname(local_abspath, pool);
      SVN_ERR(svn_io_make_dir_recursively(parent, pool));
    }

  /* ... Hello, new hotness. */
  SVN_ERR(svn_client__checkout_internal(NULL, timestamp_sleep,
                                        url, local_abspath, peg_revision,
                                        revision, svn_depth_infinity,
                                        FALSE, FALSE,
                                        ra_session,
                                        ctx, pool));

  SVN_ERR(svn_wc__node_get_repos_info(NULL, NULL,
                                      &repos_root_url,
                                      &repos_uuid,
                                      ctx->wc_ctx, local_abspath,
                                      pool, pool));

  SVN_ERR(svn_wc__external_register(ctx->wc_ctx,
                                    defining_abspath,
                                    local_abspath, svn_node_dir,
                                    repos_root_url, repos_uuid,
                                    svn_uri_skip_ancestor(repos_root_url,
                                                          url, pool),
                                    external_peg_rev,
                                    external_rev,
                                    pool));

 cleanup:
  /* Issues #4123 and #4130: We don't need to keep the newly checked
     out external's DB open. */
  SVN_ERR(svn_wc__close_db(local_abspath, ctx->wc_ctx, pool));

  return SVN_NO_ERROR;
}