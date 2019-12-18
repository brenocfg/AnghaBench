#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_wc_conflict_reason_t ;
typedef  scalar_t__ svn_wc_conflict_action_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
struct TYPE_10__ {struct conflict_tree_incoming_delete_details* tree_conflict_incoming_details; } ;
typedef  TYPE_1__ svn_client_conflict_t ;
struct conflict_tree_incoming_delete_details {int /*<<< orphan*/  wc_move_targets; int /*<<< orphan*/ * moves; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_resolution_option (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  describe_incoming_move_merge_conflict_option (char const**,TYPE_1__*,int /*<<< orphan*/ *,struct conflict_tree_incoming_delete_details*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resolve_incoming_move_dir_merge ; 
 scalar_t__ svn_client_conflict_get_incoming_change (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_client_conflict_get_incoming_new_repos_location (char const**,int /*<<< orphan*/ *,scalar_t__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_conflict_get_incoming_old_repos_location (char const**,int /*<<< orphan*/ *,scalar_t__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_client_conflict_get_local_change (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_client_conflict_option_incoming_move_dir_merge ; 
 scalar_t__ svn_client_conflict_tree_get_victim_node_kind (TYPE_1__*) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_none ; 
 scalar_t__ svn_wc_conflict_action_delete ; 
 scalar_t__ svn_wc_conflict_reason_edited ; 

__attribute__((used)) static svn_error_t *
configure_option_incoming_dir_merge(svn_client_conflict_t *conflict,
                                    svn_client_ctx_t *ctx,
                                    apr_array_header_t *options,
                                    apr_pool_t *scratch_pool)
{
  svn_node_kind_t victim_node_kind;
  svn_wc_conflict_action_t incoming_change;
  svn_wc_conflict_reason_t local_change;
  const char *incoming_old_repos_relpath;
  svn_revnum_t incoming_old_pegrev;
  svn_node_kind_t incoming_old_kind;
  const char *incoming_new_repos_relpath;
  svn_revnum_t incoming_new_pegrev;
  svn_node_kind_t incoming_new_kind;

  incoming_change = svn_client_conflict_get_incoming_change(conflict);
  local_change = svn_client_conflict_get_local_change(conflict);
  victim_node_kind = svn_client_conflict_tree_get_victim_node_kind(conflict);
  SVN_ERR(svn_client_conflict_get_incoming_old_repos_location(
            &incoming_old_repos_relpath, &incoming_old_pegrev,
            &incoming_old_kind, conflict, scratch_pool,
            scratch_pool));
  SVN_ERR(svn_client_conflict_get_incoming_new_repos_location(
            &incoming_new_repos_relpath, &incoming_new_pegrev,
            &incoming_new_kind, conflict, scratch_pool,
            scratch_pool));

  if (victim_node_kind == svn_node_dir &&
      incoming_old_kind == svn_node_dir &&
      incoming_new_kind == svn_node_none &&
      incoming_change == svn_wc_conflict_action_delete &&
      local_change == svn_wc_conflict_reason_edited)
    {
      struct conflict_tree_incoming_delete_details *details;
      const char *description;

      details = conflict->tree_conflict_incoming_details;
      if (details == NULL || details->moves == NULL)
        return SVN_NO_ERROR;

      if (apr_hash_count(details->wc_move_targets) == 0)
        return SVN_NO_ERROR;

      SVN_ERR(describe_incoming_move_merge_conflict_option(&description,
                                                           conflict, ctx,
                                                           details,
                                                           scratch_pool,
                                                           scratch_pool));
      add_resolution_option(options, conflict,
                            svn_client_conflict_option_incoming_move_dir_merge,
                            _("Move and merge"), description,
                            resolve_incoming_move_dir_merge);
    }

  return SVN_NO_ERROR;
}