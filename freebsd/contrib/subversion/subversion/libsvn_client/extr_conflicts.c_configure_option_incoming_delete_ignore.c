#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_wc_operation_t ;
typedef  scalar_t__ svn_wc_conflict_reason_t ;
typedef  scalar_t__ svn_wc_conflict_action_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
struct TYPE_8__ {struct conflict_tree_local_missing_details* tree_conflict_local_details; struct conflict_tree_incoming_delete_details* tree_conflict_incoming_details; } ;
typedef  TYPE_1__ svn_client_conflict_t ;
typedef  int svn_boolean_t ;
struct conflict_tree_local_missing_details {int /*<<< orphan*/ * moves; } ;
struct conflict_tree_incoming_delete_details {int /*<<< orphan*/ * moves; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_resolution_option (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 char* apr_psprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resolve_incoming_delete_ignore ; 
 scalar_t__ svn_client_conflict_get_incoming_change (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_client_conflict_get_incoming_new_repos_location (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_client_conflict_get_local_change (TYPE_1__*) ; 
 scalar_t__ svn_client_conflict_get_operation (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_client_conflict_option_incoming_delete_ignore ; 
 scalar_t__ svn_wc_conflict_action_delete ; 
 scalar_t__ svn_wc_conflict_reason_deleted ; 
 scalar_t__ svn_wc_conflict_reason_edited ; 
 scalar_t__ svn_wc_conflict_reason_missing ; 
 scalar_t__ svn_wc_conflict_reason_moved_away ; 
 scalar_t__ svn_wc_operation_merge ; 

__attribute__((used)) static svn_error_t *
configure_option_incoming_delete_ignore(svn_client_conflict_t *conflict,
                                        svn_client_ctx_t *ctx,
                                        apr_array_header_t *options,
                                        apr_pool_t *scratch_pool)
{
  svn_wc_operation_t operation;
  svn_wc_conflict_action_t incoming_change;
  svn_wc_conflict_reason_t local_change;
  const char *incoming_new_repos_relpath;
  svn_revnum_t incoming_new_pegrev;

  operation = svn_client_conflict_get_operation(conflict);
  incoming_change = svn_client_conflict_get_incoming_change(conflict);
  local_change = svn_client_conflict_get_local_change(conflict);
  SVN_ERR(svn_client_conflict_get_incoming_new_repos_location(
            &incoming_new_repos_relpath, &incoming_new_pegrev,
            NULL, conflict, scratch_pool,
            scratch_pool));

  if (incoming_change == svn_wc_conflict_action_delete)
    {
      const char *description;
      struct conflict_tree_incoming_delete_details *incoming_details;
      svn_boolean_t is_incoming_move;

      incoming_details = conflict->tree_conflict_incoming_details;
      is_incoming_move = (incoming_details != NULL &&
                          incoming_details->moves != NULL);
      if (local_change == svn_wc_conflict_reason_moved_away ||
          local_change == svn_wc_conflict_reason_edited)
        {
          /* An option which ignores the incoming deletion makes no sense
           * if we know there was a local move and/or an incoming move. */
          if (is_incoming_move)
            return SVN_NO_ERROR;
        }
      else if (local_change == svn_wc_conflict_reason_deleted)
        {
          /* If the local item was deleted and conflict details were fetched
           * and indicate that there was no move, then this is an actual
           * 'delete vs delete' situation. An option which ignores the incoming
           * deletion makes no sense in that case because there is no local
           * node to preserve. */
          if (!is_incoming_move)
            return SVN_NO_ERROR;
        }
      else if (local_change == svn_wc_conflict_reason_missing &&
               operation == svn_wc_operation_merge)
        {
          struct conflict_tree_local_missing_details *local_details;
          svn_boolean_t is_local_move; /* "local" to branch history */

          local_details = conflict->tree_conflict_local_details;
          is_local_move = (local_details != NULL &&
                           local_details->moves != NULL);

          if (!is_incoming_move && !is_local_move)
            return SVN_NO_ERROR;
        }

      description =
        apr_psprintf(scratch_pool, _("ignore the deletion of '^/%s@%ld'"),
          incoming_new_repos_relpath, incoming_new_pegrev);

      add_resolution_option(options, conflict,
                            svn_client_conflict_option_incoming_delete_ignore,
                            _("Ignore incoming deletion"), description,
                            resolve_incoming_delete_ignore);
    }

  return SVN_NO_ERROR;
}