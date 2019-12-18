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
typedef  int /*<<< orphan*/  svn_wc_notify_func2_t ;
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
 int /*<<< orphan*/  svn_wc__db_update_local_add (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__read_conflicts (int /*<<< orphan*/  const**,int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__wq_run (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc_conflict_action_add ; 
 scalar_t__ svn_wc_conflict_reason_added ; 
 scalar_t__ svn_wc_operation_update ; 

svn_error_t *
svn_wc__conflict_tree_update_local_add(svn_wc_context_t *wc_ctx,
                                       const char *local_abspath,
                                       svn_cancel_func_t cancel_func,
                                       void *cancel_baton,
                                       svn_wc_notify_func2_t notify_func,
                                       void *notify_baton,
                                       apr_pool_t *scratch_pool)
{
  svn_wc_conflict_reason_t local_change;
  svn_wc_conflict_action_t incoming_change;
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

  SVN_ERR(svn_wc__conflict_read_tree_conflict(&local_change, &incoming_change,
                                              NULL, wc_ctx->db, local_abspath,
                                              conflict_skel,
                                              scratch_pool, scratch_pool));

  /* Make sure the expected conflict is recorded. */
  if (operation != svn_wc_operation_update)
    return svn_error_createf(SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE, NULL,
                             _("Unexpected conflict operation '%s' on '%s'"),
                             svn_token__to_word(operation_map, operation),
                             svn_dirent_local_style(local_abspath,
                                                    scratch_pool));
  if (local_change != svn_wc_conflict_reason_added)
    return svn_error_createf(SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE, NULL,
                             _("Unexpected conflict reason '%s' on '%s'"),
                             svn_token__to_word(reason_map, local_change),
                             svn_dirent_local_style(local_abspath,
                                                    scratch_pool));
  if (incoming_change != svn_wc_conflict_action_add)
    return svn_error_createf(SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE, NULL,
                             _("Unexpected conflict action '%s' on '%s'"),
                             svn_token__to_word(action_map, incoming_change),
                             svn_dirent_local_style(local_abspath,
                                                    scratch_pool));

  SVN_ERR(svn_wc__db_update_local_add(wc_ctx->db, local_abspath,
                                      cancel_func, cancel_baton,
                                      notify_func, notify_baton,
                                      scratch_pool));

  SVN_ERR(svn_wc__wq_run(wc_ctx->db, local_abspath, cancel_func, cancel_baton,
                         scratch_pool));

  return SVN_NO_ERROR;
}