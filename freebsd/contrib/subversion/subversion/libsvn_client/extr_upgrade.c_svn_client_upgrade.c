#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * err; } ;
typedef  TYPE_1__ svn_wc_notify_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_9__ {int /*<<< orphan*/  notify_baton2; int /*<<< orphan*/  (* notify_func2 ) (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  wc_ctx; int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; } ;
typedef  TYPE_2__ svn_client_ctx_t ;
struct repos_info_baton {int /*<<< orphan*/ * last_uuid; int /*<<< orphan*/ * last_repos; TYPE_2__* ctx; int /*<<< orphan*/ * state_pool; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ILLEGAL_TARGET ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fetch_repos_info ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_path_is_url (char const*) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__externals_defined_below (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__read_external_info (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc_create_notify (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_failed_external ; 
 int /*<<< orphan*/  svn_wc_upgrade (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,struct repos_info_baton*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *),int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  upgrade_externals_from_properties (TYPE_2__*,char const*,struct repos_info_baton*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client_upgrade(const char *path,
                   svn_client_ctx_t *ctx,
                   apr_pool_t *scratch_pool)
{
  const char *local_abspath;
  apr_hash_t *externals;
  struct repos_info_baton info_baton;

  info_baton.state_pool = scratch_pool;
  info_baton.ctx = ctx;
  info_baton.last_repos = NULL;
  info_baton.last_uuid = NULL;

  if (svn_path_is_url(path))
    return svn_error_createf(SVN_ERR_ILLEGAL_TARGET, NULL,
                             _("'%s' is not a local path"), path);

  SVN_ERR(svn_dirent_get_absolute(&local_abspath, path, scratch_pool));
  SVN_ERR(svn_wc_upgrade(ctx->wc_ctx, local_abspath,
                         fetch_repos_info, &info_baton,
                         ctx->cancel_func, ctx->cancel_baton,
                         ctx->notify_func2, ctx->notify_baton2,
                         scratch_pool));

  SVN_ERR(svn_wc__externals_defined_below(&externals,
                                          ctx->wc_ctx, local_abspath,
                                          scratch_pool, scratch_pool));

  if (apr_hash_count(externals) > 0)
    {
      apr_pool_t *iterpool = svn_pool_create(scratch_pool);
      apr_hash_index_t *hi;

      /* We are upgrading from >= 1.7. No need to upgrade from
         svn:externals properties. And by that avoiding the removal
         of recorded externals information (issue #4519)

         Only directory externals need an explicit upgrade */
      for (hi = apr_hash_first(scratch_pool, externals);
           hi;
           hi = apr_hash_next(hi))
        {
          const char *ext_abspath;
          svn_node_kind_t kind;

          svn_pool_clear(iterpool);

          ext_abspath = apr_hash_this_key(hi);

          SVN_ERR(svn_wc__read_external_info(&kind, NULL, NULL, NULL, NULL,
                                             ctx->wc_ctx, local_abspath,
                                             ext_abspath, FALSE,
                                             iterpool, iterpool));

          if (kind == svn_node_dir)
            {
              svn_error_t *err = svn_client_upgrade(ext_abspath, ctx, iterpool);

              if (err)
                {
                  svn_wc_notify_t *notify =
                            svn_wc_create_notify(ext_abspath,
                                                 svn_wc_notify_failed_external,
                                                 iterpool);
                  notify->err = err;
                  ctx->notify_func2(ctx->notify_baton2,
                                    notify, iterpool);
                  svn_error_clear(err);
                  /* Next external node, please... */
                }
            }
        }

      svn_pool_destroy(iterpool);
    }
  else
    {
      /* Upgrading from <= 1.6, or no svn:properties defined.
         (There is no way to detect the difference from libsvn_client :( ) */

      SVN_ERR(upgrade_externals_from_properties(ctx, local_abspath,
                                                &info_baton, scratch_pool));
    }
  return SVN_NO_ERROR;
}