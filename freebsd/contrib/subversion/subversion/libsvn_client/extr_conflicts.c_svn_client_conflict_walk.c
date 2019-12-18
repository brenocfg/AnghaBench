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
typedef  int /*<<< orphan*/  svn_wc_status3_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_depth_t ;
struct TYPE_3__ {struct conflict_status_walker_baton* notify_baton2; int /*<<< orphan*/  (* notify_func2 ) (struct conflict_status_walker_baton*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  wc_ctx; int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/ * (* cancel_func ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_client_conflict_walk_func_t ;
struct conflict_status_walker_baton {struct conflict_status_walker_baton* notify_baton; int /*<<< orphan*/  (* notify_func ) (struct conflict_status_walker_baton*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * unresolved_tree_conflicts; void* resolved_a_tree_conflict; TYPE_1__* ctx; void* conflict_walk_func_baton; int /*<<< orphan*/  conflict_walk_func; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * conflict_status_walker (struct conflict_status_walker_baton*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct conflict_status_walker_baton*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct conflict_status_walker_baton*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_depth_infinity ; 
 scalar_t__ svn_depth_unknown ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_create_notify (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_conflict_resolver_done ; 
 int /*<<< orphan*/  svn_wc_notify_conflict_resolver_starting ; 
 int /*<<< orphan*/ * svn_wc_status3 (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc_walk_status (int /*<<< orphan*/ ,char const*,scalar_t__,void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ * (*) (struct conflict_status_walker_baton*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *),struct conflict_status_walker_baton*,int /*<<< orphan*/ * (*) (int /*<<< orphan*/ ),int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tree_conflict_collector (struct conflict_status_walker_baton*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client_conflict_walk(const char *local_abspath,
                         svn_depth_t depth,
                         svn_client_conflict_walk_func_t conflict_walk_func,
                         void *conflict_walk_func_baton,
                         svn_client_ctx_t *ctx,
                         apr_pool_t *scratch_pool)
{
  struct conflict_status_walker_baton cswb;
  apr_pool_t *iterpool = NULL;
  svn_error_t *err = SVN_NO_ERROR;

  if (depth == svn_depth_unknown)
    depth = svn_depth_infinity;

  cswb.conflict_walk_func = conflict_walk_func;
  cswb.conflict_walk_func_baton = conflict_walk_func_baton;
  cswb.ctx = ctx;
  cswb.resolved_a_tree_conflict = FALSE;
  cswb.unresolved_tree_conflicts = apr_hash_make(scratch_pool);

  if (ctx->notify_func2)
    ctx->notify_func2(ctx->notify_baton2,
                      svn_wc_create_notify(
                        local_abspath,
                        svn_wc_notify_conflict_resolver_starting,
                        scratch_pool),
                      scratch_pool);

  /* Swap in our notify_func wrapper. We must revert this before returning! */
  cswb.notify_func = ctx->notify_func2;
  cswb.notify_baton = ctx->notify_baton2;
  ctx->notify_func2 = tree_conflict_collector;
  ctx->notify_baton2 = &cswb;

  err = svn_wc_walk_status(ctx->wc_ctx,
                           local_abspath,
                           depth,
                           FALSE /* get_all */,
                           FALSE /* no_ignore */,
                           TRUE /* ignore_text_mods */,
                           NULL /* ignore_patterns */,
                           conflict_status_walker, &cswb,
                           ctx->cancel_func, ctx->cancel_baton,
                           scratch_pool);

  /* If we got new tree conflicts (or delayed conflicts) during the initial
     walk, we now walk them one by one as closure. */
  while (!err && cswb.unresolved_tree_conflicts &&
         apr_hash_count(cswb.unresolved_tree_conflicts))
    {
      apr_hash_index_t *hi;
      svn_wc_status3_t *status = NULL;
      const char *tc_abspath = NULL;

      if (iterpool)
        svn_pool_clear(iterpool);
      else
        iterpool = svn_pool_create(scratch_pool);

      hi = apr_hash_first(scratch_pool, cswb.unresolved_tree_conflicts);
      cswb.unresolved_tree_conflicts = apr_hash_make(scratch_pool);
      cswb.resolved_a_tree_conflict = FALSE;

      for (; hi && !err; hi = apr_hash_next(hi))
        {
          svn_pool_clear(iterpool);

          tc_abspath = apr_hash_this_key(hi);

          if (ctx->cancel_func)
            {
              err = ctx->cancel_func(ctx->cancel_baton);
              if (err)
                break;
            }

          err = svn_error_trace(svn_wc_status3(&status, ctx->wc_ctx,
                                               tc_abspath,
                                               iterpool, iterpool));
          if (err)
            break;

          err = svn_error_trace(conflict_status_walker(&cswb, tc_abspath,
                                                       status, scratch_pool));
          if (err)
            break;
        }
  
      if (!err && !cswb.resolved_a_tree_conflict && tc_abspath &&
          apr_hash_count(cswb.unresolved_tree_conflicts))
        {
          /* None of the remaining conflicts got resolved, without any error.
           * Disable the 'unresolved_tree_conflicts' cache and try again. */
          cswb.unresolved_tree_conflicts = NULL;

          /* Run the most recent resolve operation again.
           * We still have status and tc_abspath for that one.
           * This should uncover the error which prevents resolution. */
          err = svn_error_trace(conflict_status_walker(&cswb, tc_abspath,
                                                       status, scratch_pool));
          SVN_ERR_ASSERT(err != NULL);

          err = svn_error_createf(
                    SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE, err,
                    _("Unable to resolve pending conflict on '%s'"),
                    svn_dirent_local_style(tc_abspath, scratch_pool));
          break;
        }
    }

  if (iterpool)
    svn_pool_destroy(iterpool);

  ctx->notify_func2 = cswb.notify_func;
  ctx->notify_baton2 = cswb.notify_baton;

  if (!err && ctx->notify_func2)
    ctx->notify_func2(ctx->notify_baton2,
                      svn_wc_create_notify(local_abspath,
                                          svn_wc_notify_conflict_resolver_done,
                                          scratch_pool),
                      scratch_pool);

  return svn_error_trace(err);
}