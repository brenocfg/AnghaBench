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
typedef  scalar_t__ svn_wc_operation_t ;
typedef  int /*<<< orphan*/  (* svn_wc_notify_func2_t ) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;
struct TYPE_3__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ svn_wc_context_t ;
typedef  scalar_t__ svn_wc_conflict_reason_t ;
typedef  scalar_t__ svn_wc_conflict_action_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  action_map ; 
 int /*<<< orphan*/  operation_map ; 
 int /*<<< orphan*/  reason_map ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_token__to_word (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  svn_wc__conflict_read_info (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__conflict_read_tree_conflict (scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_op_raise_moved_away (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  (*) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *),void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__read_conflicts (int /*<<< orphan*/  const**,int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc_conflict_action_edit ; 
 scalar_t__ svn_wc_conflict_reason_deleted ; 
 scalar_t__ svn_wc_conflict_reason_replaced ; 
 int /*<<< orphan*/  svn_wc_create_notify (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_resolved_tree ; 
 scalar_t__ svn_wc_operation_switch ; 
 scalar_t__ svn_wc_operation_update ; 

svn_error_t *
svn_wc__conflict_tree_update_raise_moved_away(svn_wc_context_t *wc_ctx,
                                              const char *local_abspath,
                                              svn_cancel_func_t cancel_func,
                                              void *cancel_baton,
                                              svn_wc_notify_func2_t notify_func,
                                              void *notify_baton,
                                              apr_pool_t *scratch_pool)
{
  svn_wc_conflict_reason_t reason;
  svn_wc_conflict_action_t action;
  svn_wc_operation_t operation;
  svn_boolean_t tree_conflicted;
  const apr_array_header_t *conflicts;
  svn_skel_t *conflict_skel;

  SVN_ERR(svn_wc__read_conflicts(&conflicts, &conflict_skel,
                                 wc_ctx->db, local_abspath,
                                 FALSE, /* no tempfiles */
                                 FALSE, /* only tree conflicts */
                                 scratch_pool, scratch_pool));

  SVN_ERR(svn_wc__conflict_read_info(&operation, NULL, NULL, NULL,
                                     &tree_conflicted, wc_ctx->db,
                                     local_abspath, conflict_skel,
                                     scratch_pool, scratch_pool));
  if (!tree_conflicted)
    return SVN_NO_ERROR;

  SVN_ERR(svn_wc__conflict_read_tree_conflict(&reason, &action, NULL,
                                              wc_ctx->db, local_abspath,
                                              conflict_skel,
                                              scratch_pool, scratch_pool));

  /* Make sure the expected conflict is recorded. */
  if (operation != svn_wc_operation_update &&
      operation != svn_wc_operation_switch)
    return svn_error_createf(SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE, NULL,
                             _("Unexpected conflict operation '%s' on '%s'"),
                             svn_token__to_word(operation_map, operation),
                             svn_dirent_local_style(local_abspath,
                                                    scratch_pool));
  if (reason != svn_wc_conflict_reason_deleted &&
      reason != svn_wc_conflict_reason_replaced)
    return svn_error_createf(SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE, NULL,
                             _("Unexpected conflict reason '%s' on '%s'"),
                             svn_token__to_word(reason_map, reason),
                             svn_dirent_local_style(local_abspath,
                                                    scratch_pool));
  if (action != svn_wc_conflict_action_edit)
    return svn_error_createf(SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE, NULL,
                             _("Unexpected conflict action '%s' on '%s'"),
                             svn_token__to_word(action_map, action),
                             svn_dirent_local_style(local_abspath,
                                                    scratch_pool));

  /* Raise local moved-away vs. incoming edit conflicts on any children
   * moved out of this directory, and leave this directory as-is.
   * The user may choose to update newly conflicted moved-away children
   * when resolving them. If this function raises an error, the conflict
   * cannot be resolved yet because other conflicts or obstructions
   * prevent us from propagating the conflict to moved-away children. */
  SVN_ERR(svn_wc__db_op_raise_moved_away(wc_ctx->db, local_abspath,
                                         notify_func, notify_baton,
                                         scratch_pool));

  /* The conflict was marked resolved by svn_wc__db_op_raise_moved_away(). */
  if (notify_func)
    notify_func(notify_baton,
                svn_wc_create_notify(local_abspath,
                                     svn_wc_notify_resolved_tree,
                                     scratch_pool),
                scratch_pool);

  return SVN_NO_ERROR;
}