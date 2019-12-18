#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_notify_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
struct TYPE_21__ {int /*<<< orphan*/  tunnel_baton; int /*<<< orphan*/  open_tunnel_func; int /*<<< orphan*/  check_tunnel_func; int /*<<< orphan*/  get_wc_contents; int /*<<< orphan*/  get_client_string; int /*<<< orphan*/ * cancel_func; TYPE_4__* progress_baton; int /*<<< orphan*/  progress_func; int /*<<< orphan*/  auth_baton; int /*<<< orphan*/ * invalidate_wc_props; int /*<<< orphan*/ * push_wc_prop; int /*<<< orphan*/ * set_wc_prop; int /*<<< orphan*/ * get_wc_prop; int /*<<< orphan*/  open_tmp_file; } ;
typedef  TYPE_1__ svn_ra_callbacks2_t ;
struct TYPE_22__ {scalar_t__ apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
struct TYPE_23__ {int /*<<< orphan*/  config; int /*<<< orphan*/  notify_baton2; int /*<<< orphan*/  (* notify_func2 ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  wc_ctx; int /*<<< orphan*/  tunnel_baton; int /*<<< orphan*/  open_tunnel_func; int /*<<< orphan*/  check_tunnel_func; scalar_t__ cancel_func; int /*<<< orphan*/  auth_baton; } ;
typedef  TYPE_3__ svn_client_ctx_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_24__ {int /*<<< orphan*/ * wcroot_abspath; int /*<<< orphan*/  base_dir_abspath; int /*<<< orphan*/  base_dir_isversioned; TYPE_3__* ctx; int /*<<< orphan*/  const* commit_items; } ;
typedef  TYPE_4__ callback_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int SVN_CLIENT__MAX_REDIRECT_ATTEMPTS ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_CLIENT_CYCLE_DETECTED ; 
 scalar_t__ SVN_ERR_WC_NOT_WORKING_COPY ; 
 scalar_t__ SVN_ERR_WC_PATH_NOT_FOUND ; 
 scalar_t__ SVN_ERR_WC_UPGRADE_REQUIRED ; 
 TYPE_2__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 TYPE_4__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * cancel_callback ; 
 int /*<<< orphan*/  get_client_string ; 
 int /*<<< orphan*/  get_wc_contents ; 
 int /*<<< orphan*/ * get_wc_prop ; 
 int /*<<< orphan*/ * invalidate_wc_props ; 
 int /*<<< orphan*/  open_tmp_file ; 
 int /*<<< orphan*/  progress_func ; 
 int /*<<< orphan*/ * push_wc_prop ; 
 int /*<<< orphan*/ * set_wc_prop ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_dirent_is_absolute (char const*) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 TYPE_2__* svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 TYPE_2__* svn_error_trace (TYPE_2__*) ; 
 scalar_t__ svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,void*) ; 
 TYPE_2__* svn_ra_create_callbacks (TYPE_1__**,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_ra_open4 (int /*<<< orphan*/ **,char const**,char const*,char const*,TYPE_1__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc__get_wcroot (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc__node_get_repos_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc_create_notify_url (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_url_redirect ; 

svn_error_t *
svn_client__open_ra_session_internal(svn_ra_session_t **ra_session,
                                     const char **corrected_url,
                                     const char *base_url,
                                     const char *base_dir_abspath,
                                     const apr_array_header_t *commit_items,
                                     svn_boolean_t write_dav_props,
                                     svn_boolean_t read_dav_props,
                                     svn_client_ctx_t *ctx,
                                     apr_pool_t *result_pool,
                                     apr_pool_t *scratch_pool)
{
  svn_ra_callbacks2_t *cbtable;
  callback_baton_t *cb = apr_pcalloc(result_pool, sizeof(*cb));
  const char *uuid = NULL;

  SVN_ERR_ASSERT(!write_dav_props || read_dav_props);
  SVN_ERR_ASSERT(!read_dav_props || base_dir_abspath != NULL);
  SVN_ERR_ASSERT(base_dir_abspath == NULL
                        || svn_dirent_is_absolute(base_dir_abspath));

  SVN_ERR(svn_ra_create_callbacks(&cbtable, result_pool));
  cbtable->open_tmp_file = open_tmp_file;
  cbtable->get_wc_prop = read_dav_props ? get_wc_prop : NULL;
  cbtable->set_wc_prop = (write_dav_props && read_dav_props)
                          ? set_wc_prop : NULL;
  cbtable->push_wc_prop = commit_items ? push_wc_prop : NULL;
  cbtable->invalidate_wc_props = (write_dav_props && read_dav_props)
                                  ? invalidate_wc_props : NULL;
  cbtable->auth_baton = ctx->auth_baton; /* new-style */
  cbtable->progress_func = progress_func;
  cbtable->progress_baton = cb;
  cbtable->cancel_func = ctx->cancel_func ? cancel_callback : NULL;
  cbtable->get_client_string = get_client_string;
  if (base_dir_abspath)
    cbtable->get_wc_contents = get_wc_contents;
  cbtable->check_tunnel_func = ctx->check_tunnel_func;
  cbtable->open_tunnel_func = ctx->open_tunnel_func;
  cbtable->tunnel_baton = ctx->tunnel_baton;

  cb->commit_items = commit_items;
  cb->ctx = ctx;

  if (base_dir_abspath && (read_dav_props || write_dav_props))
    {
      svn_error_t *err = svn_wc__node_get_repos_info(NULL, NULL, NULL, &uuid,
                                                     ctx->wc_ctx,
                                                     base_dir_abspath,
                                                     result_pool,
                                                     scratch_pool);

      if (err && (err->apr_err == SVN_ERR_WC_NOT_WORKING_COPY
                  || err->apr_err == SVN_ERR_WC_PATH_NOT_FOUND
                  || err->apr_err == SVN_ERR_WC_UPGRADE_REQUIRED))
        {
          svn_error_clear(err);
          uuid = NULL;
        }
      else
        {
          SVN_ERR(err);
          cb->base_dir_isversioned = TRUE;
        }
      cb->base_dir_abspath = apr_pstrdup(result_pool, base_dir_abspath);
    }

  if (base_dir_abspath)
    {
      svn_error_t *err = svn_wc__get_wcroot(&cb->wcroot_abspath,
                                            ctx->wc_ctx, base_dir_abspath,
                                            result_pool, scratch_pool);

      if (err)
        {
          if (err->apr_err != SVN_ERR_WC_NOT_WORKING_COPY
              && err->apr_err != SVN_ERR_WC_PATH_NOT_FOUND
              && err->apr_err != SVN_ERR_WC_UPGRADE_REQUIRED)
            return svn_error_trace(err);

          svn_error_clear(err);
          cb->wcroot_abspath = NULL;
        }
    }

  /* If the caller allows for auto-following redirections, and the
     RA->open() call above reveals a CORRECTED_URL, try the new URL.
     We'll do this in a loop up to some maximum number follow-and-retry
     attempts.  */
  if (corrected_url)
    {
      apr_hash_t *attempted = apr_hash_make(scratch_pool);
      int attempts_left = SVN_CLIENT__MAX_REDIRECT_ATTEMPTS;

      *corrected_url = NULL;
      while (attempts_left--)
        {
          const char *corrected = NULL;

          /* Try to open the RA session.  If this is our last attempt,
             don't accept corrected URLs from the RA provider. */
          SVN_ERR(svn_ra_open4(ra_session,
                               attempts_left == 0 ? NULL : &corrected,
                               base_url, uuid, cbtable, cb, ctx->config,
                               result_pool));

          /* No error and no corrected URL?  We're done here. */
          if (! corrected)
            break;

          /* Notify the user that a redirect is being followed. */
          if (ctx->notify_func2 != NULL)
            {
              svn_wc_notify_t *notify =
                svn_wc_create_notify_url(corrected,
                                         svn_wc_notify_url_redirect,
                                         scratch_pool);
              ctx->notify_func2(ctx->notify_baton2, notify, scratch_pool);
            }

          /* Our caller will want to know what our final corrected URL was. */
          *corrected_url = corrected;

          /* Make sure we've not attempted this URL before. */
          if (svn_hash_gets(attempted, corrected))
            return svn_error_createf(SVN_ERR_CLIENT_CYCLE_DETECTED, NULL,
                                     _("Redirect cycle detected for URL '%s'"),
                                     corrected);

          /* Remember this CORRECTED_URL so we don't wind up in a loop. */
          svn_hash_sets(attempted, corrected, (void *)1);
          base_url = corrected;
        }
    }
  else
    {
      SVN_ERR(svn_ra_open4(ra_session, NULL, base_url,
                           uuid, cbtable, cb, ctx->config, result_pool));
    }

  return SVN_NO_ERROR;
}