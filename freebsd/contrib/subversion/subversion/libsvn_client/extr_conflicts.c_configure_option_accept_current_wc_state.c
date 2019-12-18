#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ svn_wc_operation_t ;
typedef  scalar_t__ svn_wc_conflict_reason_t ;
typedef  scalar_t__ svn_wc_conflict_action_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_conflict_t ;
typedef  int /*<<< orphan*/  conflict_option_resolve_func_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_resolution_option (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resolve_accept_current_wc_state ; 
 int /*<<< orphan*/  resolve_update_break_moved_away ; 
 scalar_t__ svn_client_conflict_get_incoming_change (int /*<<< orphan*/ *) ; 
 scalar_t__ svn_client_conflict_get_local_change (int /*<<< orphan*/ *) ; 
 scalar_t__ svn_client_conflict_get_operation (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_conflict_option_accept_current_wc_state ; 
 scalar_t__ svn_wc_conflict_action_edit ; 
 scalar_t__ svn_wc_conflict_reason_deleted ; 
 scalar_t__ svn_wc_conflict_reason_moved_away ; 
 scalar_t__ svn_wc_conflict_reason_replaced ; 
 scalar_t__ svn_wc_operation_switch ; 
 scalar_t__ svn_wc_operation_update ; 

__attribute__((used)) static svn_error_t *
configure_option_accept_current_wc_state(svn_client_conflict_t *conflict,
                                         apr_array_header_t *options)
{
  svn_wc_operation_t operation;
  svn_wc_conflict_action_t incoming_change;
  svn_wc_conflict_reason_t local_change;
  conflict_option_resolve_func_t do_resolve_func;

  operation = svn_client_conflict_get_operation(conflict);
  incoming_change = svn_client_conflict_get_incoming_change(conflict);
  local_change = svn_client_conflict_get_local_change(conflict);

  if ((operation == svn_wc_operation_update ||
       operation == svn_wc_operation_switch) &&
      (local_change == svn_wc_conflict_reason_moved_away ||
       local_change == svn_wc_conflict_reason_deleted ||
       local_change == svn_wc_conflict_reason_replaced) &&
      incoming_change == svn_wc_conflict_action_edit)
    {
      /* We must break moves if the user accepts the current working copy
       * state instead of updating a moved-away node or updating children
       * moved outside of deleted or replaced directory nodes.
       * Else such moves would be left in an invalid state. */
      do_resolve_func = resolve_update_break_moved_away;
    }
  else
    do_resolve_func = resolve_accept_current_wc_state;

  add_resolution_option(options, conflict,
                        svn_client_conflict_option_accept_current_wc_state,
                        _("Mark as resolved"),
                        _("accept current working copy state"),
                        do_resolve_func);

  return SVN_NO_ERROR;
}