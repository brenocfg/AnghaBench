#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {int /*<<< orphan*/  wc_ctx; int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; int /*<<< orphan*/  config; int /*<<< orphan*/  notify_baton2; int /*<<< orphan*/  notify_func2; } ;
typedef  TYPE_1__ svn_client_ctx_t ;
typedef  void* svn_boolean_t ;
struct cleanup_status_walk_baton {TYPE_1__* ctx; void* include_externals; void* remove_ignored_items; void* remove_unversioned_items; void* vacuum_pristines; void* clear_dav_cache; void* fix_timestamps; void* break_locks; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_WC__CALL_WITH_WRITE_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cleanup_status_walk ; 
 int /*<<< orphan*/  svn_depth_infinity ; 
 int /*<<< orphan*/  svn_io_sleep_for_timestamps (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_cleanup4 (int /*<<< orphan*/ ,char const*,void*,void*,void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_get_default_ignores (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_walk_status (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct cleanup_status_walk_baton*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
do_cleanup(const char *local_abspath,
           svn_boolean_t break_locks,
           svn_boolean_t fix_timestamps,
           svn_boolean_t clear_dav_cache,
           svn_boolean_t vacuum_pristines,
           svn_boolean_t remove_unversioned_items,
           svn_boolean_t remove_ignored_items,
           svn_boolean_t include_externals,
           svn_client_ctx_t *ctx,
           apr_pool_t *scratch_pool)
{
  SVN_ERR(svn_wc_cleanup4(ctx->wc_ctx,
                          local_abspath,
                          break_locks,
                          fix_timestamps,
                          clear_dav_cache,
                          vacuum_pristines,
                          ctx->cancel_func, ctx->cancel_baton,
                          ctx->notify_func2, ctx->notify_baton2,
                          scratch_pool));

  if (fix_timestamps)
    svn_io_sleep_for_timestamps(local_abspath, scratch_pool);

  if (remove_unversioned_items || remove_ignored_items || include_externals)
    {
      struct cleanup_status_walk_baton b;
      apr_array_header_t *ignores;

      b.break_locks = break_locks;
      b.fix_timestamps = fix_timestamps;
      b.clear_dav_cache = clear_dav_cache;
      b.vacuum_pristines = vacuum_pristines;
      b.remove_unversioned_items = remove_unversioned_items;
      b.remove_ignored_items = remove_ignored_items;
      b.include_externals = include_externals;
      b.ctx = ctx;

      SVN_ERR(svn_wc_get_default_ignores(&ignores, ctx->config, scratch_pool));

      SVN_WC__CALL_WITH_WRITE_LOCK(
              svn_wc_walk_status(ctx->wc_ctx, local_abspath,
                                 svn_depth_infinity,
                                 TRUE,  /* get all */
                                 remove_ignored_items,
                                 TRUE,  /* ignore textmods */
                                 ignores,
                                 cleanup_status_walk, &b,
                                 ctx->cancel_func,
                                 ctx->cancel_baton,
                                 scratch_pool),
              ctx->wc_ctx,
              local_abspath,
              FALSE /* lock_anchor */,
              scratch_pool);
    }

  return SVN_NO_ERROR;
}