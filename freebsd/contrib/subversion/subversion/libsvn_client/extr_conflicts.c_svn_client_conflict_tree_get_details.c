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
typedef  int /*<<< orphan*/  svn_wc_notify_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_11__ {int /*<<< orphan*/  notify_baton2; int /*<<< orphan*/  (* notify_func2 ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ svn_client_ctx_t ;
struct TYPE_12__ {int /*<<< orphan*/  (* tree_conflict_get_local_details_func ) (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* tree_conflict_get_incoming_details_func ) (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ svn_client_conflict_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  assert_tree_conflict (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ignore_authz_failures (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_conflict_get_local_abspath (TYPE_2__*) ; 
 int /*<<< orphan*/ * svn_wc_create_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_begin_search_tree_conflict_details ; 
 int /*<<< orphan*/  svn_wc_notify_end_search_tree_conflict_details ; 

svn_error_t *
svn_client_conflict_tree_get_details(svn_client_conflict_t *conflict,
                                     svn_client_ctx_t *ctx,
                                     apr_pool_t *scratch_pool)
{
  SVN_ERR(assert_tree_conflict(conflict, scratch_pool));

  if (ctx->notify_func2)
    {
      svn_wc_notify_t *notify;

      notify = svn_wc_create_notify(
                 svn_client_conflict_get_local_abspath(conflict),
                 svn_wc_notify_begin_search_tree_conflict_details,
                 scratch_pool),
      ctx->notify_func2(ctx->notify_baton2, notify,
                                  scratch_pool);
    }

  /* Collecting conflict details may fail due to insufficient access rights.
   * This is not a failure but simply restricts our future options. */
  if (conflict->tree_conflict_get_incoming_details_func)
    SVN_ERR(ignore_authz_failures(
      conflict->tree_conflict_get_incoming_details_func(conflict, ctx,
                                                        scratch_pool)));


  if (conflict->tree_conflict_get_local_details_func)
    SVN_ERR(ignore_authz_failures(
      conflict->tree_conflict_get_local_details_func(conflict, ctx,
                                                    scratch_pool)));

  if (ctx->notify_func2)
    {
      svn_wc_notify_t *notify;

      notify = svn_wc_create_notify(
                 svn_client_conflict_get_local_abspath(conflict),
                 svn_wc_notify_end_search_tree_conflict_details,
                 scratch_pool),
      ctx->notify_func2(ctx->notify_baton2, notify,
                                  scratch_pool);
    }

  return SVN_NO_ERROR;
}