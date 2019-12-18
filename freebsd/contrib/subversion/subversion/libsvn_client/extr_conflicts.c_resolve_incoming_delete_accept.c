#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
struct TYPE_20__ {int /*<<< orphan*/  wc_ctx; int /*<<< orphan*/  notify_baton2; int /*<<< orphan*/  (* notify_func2 ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ svn_client_ctx_t ;
struct TYPE_21__ {int /*<<< orphan*/  resolution_tree; } ;
typedef  TYPE_3__ svn_client_conflict_t ;
typedef  int /*<<< orphan*/  svn_client_conflict_option_t ;
typedef  int /*<<< orphan*/  svn_client_conflict_option_id_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_1__*) ; 
 scalar_t__ SVN_ERR_WC_PATH_NOT_FOUND ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* svn_client_conflict_get_local_abspath (TYPE_3__*) ; 
 int /*<<< orphan*/  svn_client_conflict_option_get_id (int /*<<< orphan*/ *) ; 
 char* svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_compose_create (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_wc__acquire_write_lock_for_resolve (char const**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc__del_tree_conflict (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__release_write_lock (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_create_notify (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc_delete4 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *),int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_resolved_tree ; 
 TYPE_1__* verify_local_state_for_incoming_delete (TYPE_3__*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
resolve_incoming_delete_accept(svn_client_conflict_option_t *option,
                               svn_client_conflict_t *conflict,
                               svn_client_ctx_t *ctx,
                               apr_pool_t *scratch_pool)
{
  svn_client_conflict_option_id_t option_id;
  const char *local_abspath;
  const char *parent_abspath;
  const char *lock_abspath;
  svn_error_t *err;

  option_id = svn_client_conflict_option_get_id(option);
  local_abspath = svn_client_conflict_get_local_abspath(conflict);

  /* Deleting a node requires a lock on the node's parent. */
  parent_abspath = svn_dirent_dirname(local_abspath, scratch_pool);
  SVN_ERR(svn_wc__acquire_write_lock_for_resolve(&lock_abspath, ctx->wc_ctx,
                                                 parent_abspath,
                                                 scratch_pool, scratch_pool));

  err = verify_local_state_for_incoming_delete(conflict, option, ctx,
                                               scratch_pool);
  if (err)
    goto unlock_wc;

  /* Delete the tree conflict victim. Marks the conflict resolved. */
  err = svn_wc_delete4(ctx->wc_ctx, local_abspath, FALSE, FALSE,
                       NULL, NULL, /* don't allow user to cancel here */
                       ctx->notify_func2, ctx->notify_baton2,
                       scratch_pool);
  if (err)
    {
      if (err->apr_err == SVN_ERR_WC_PATH_NOT_FOUND)
        {
          /* Not a versioned path. This can happen if the victim has already
           * been deleted in our branche's history, for example. Either way,
           * the item is gone, which is what we want, so don't treat this as
           * a fatal error. */
          svn_error_clear(err);

          /* Resolve to current working copy state. */
          err = svn_wc__del_tree_conflict(ctx->wc_ctx, local_abspath,
                                          scratch_pool);
        }

      if (err)
        goto unlock_wc;
    }

  if (ctx->notify_func2)
    ctx->notify_func2(ctx->notify_baton2,
                      svn_wc_create_notify(local_abspath,
                                           svn_wc_notify_resolved_tree,
                                           scratch_pool),
                      scratch_pool);

unlock_wc:
  err = svn_error_compose_create(err, svn_wc__release_write_lock(ctx->wc_ctx,
                                                                 lock_abspath,
                                                                 scratch_pool));
  SVN_ERR(err);

  conflict->resolution_tree = option_id;

  return SVN_NO_ERROR;
}