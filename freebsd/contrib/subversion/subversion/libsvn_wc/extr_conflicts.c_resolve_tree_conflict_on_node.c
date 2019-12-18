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
typedef  int /*<<< orphan*/  svn_wc_notify_func2_t ;
typedef  scalar_t__ svn_wc_conflict_reason_t ;
typedef  scalar_t__ svn_wc_conflict_choice_t ;
typedef  scalar_t__ svn_wc_conflict_action_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  const svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  handle_tree_conflict_resolution_failure (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__conflict_read_info (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__conflict_read_tree_conflict (scalar_t__*,scalar_t__*,char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_op_break_moved_away (int /*<<< orphan*/ *,char const*,char const*,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_op_mark_resolved (int /*<<< orphan*/ *,char const*,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__db_op_raise_moved_away (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_conflict (int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__db_update_moved_away_conflict_victim (int /*<<< orphan*/ *,char const*,char const*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__wq_run (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc_conflict_action_delete ; 
 scalar_t__ svn_wc_conflict_action_edit ; 
 scalar_t__ svn_wc_conflict_action_replace ; 
 scalar_t__ svn_wc_conflict_choose_merged ; 
 scalar_t__ svn_wc_conflict_choose_mine_conflict ; 
 scalar_t__ svn_wc_conflict_reason_deleted ; 
 scalar_t__ svn_wc_conflict_reason_moved_away ; 
 scalar_t__ svn_wc_conflict_reason_replaced ; 
 scalar_t__ svn_wc_operation_switch ; 
 scalar_t__ svn_wc_operation_update ; 

__attribute__((used)) static svn_error_t *
resolve_tree_conflict_on_node(svn_boolean_t *did_resolve,
                              svn_wc__db_t *db,
                              const char *local_abspath,
                              const svn_skel_t *conflicts,
                              svn_wc_conflict_choice_t conflict_choice,
                              apr_hash_t *resolve_later,
                              svn_wc_notify_func2_t notify_func,
                              void *notify_baton,
                              svn_cancel_func_t cancel_func,
                              void *cancel_baton,
                              apr_pool_t *scratch_pool)
{
  svn_wc_conflict_reason_t reason;
  svn_wc_conflict_action_t action;
  svn_wc_operation_t operation;
  svn_boolean_t tree_conflicted;
  const char *src_op_root_abspath;

  *did_resolve = FALSE;

  SVN_ERR(svn_wc__conflict_read_info(&operation, NULL, NULL, NULL,
                                     &tree_conflicted, db, local_abspath,
                                     conflicts, scratch_pool, scratch_pool));
  if (!tree_conflicted)
    return SVN_NO_ERROR;

  SVN_ERR(svn_wc__conflict_read_tree_conflict(&reason, &action,
                                              &src_op_root_abspath,
                                              db, local_abspath,
                                              conflicts,
                                              scratch_pool, scratch_pool));

  if (operation == svn_wc_operation_update
      || operation == svn_wc_operation_switch)
    {
      svn_error_t *err;
      if (reason == svn_wc_conflict_reason_deleted ||
          reason == svn_wc_conflict_reason_replaced)
        {
          if (conflict_choice == svn_wc_conflict_choose_merged)
            {
              /* Break moves for any children moved out of this directory,
               * and leave this directory deleted. */

              if (action != svn_wc_conflict_action_delete)
                {
                  SVN_ERR(svn_wc__db_op_break_moved_away(
                                  db, local_abspath, src_op_root_abspath, TRUE,
                                  notify_func, notify_baton,
                                  scratch_pool));
                  *did_resolve = TRUE;
                  return SVN_NO_ERROR; /* Marked resolved by function*/
                }
              /* else # The move is/moves are already broken */


              *did_resolve = TRUE;
            }
          else if (conflict_choice == svn_wc_conflict_choose_mine_conflict)
            {
              svn_skel_t *new_conflicts;

              /* Raise local moved-away vs. incoming edit conflicts on
               * any children moved out of this directory, and leave
               * this directory as-is.
               *
               * The newly conflicted moved-away children will be updated
               * if they are resolved with 'mine_conflict' as well. */
              err = svn_wc__db_op_raise_moved_away(
                        db, local_abspath, notify_func, notify_baton,
                        scratch_pool);

              if (err)
                SVN_ERR(handle_tree_conflict_resolution_failure(
                          local_abspath, err, resolve_later));

              /* We might now have a moved-away on *this* path, let's
                 try to resolve that directly if that is the case */
              SVN_ERR(svn_wc__db_read_conflict(&new_conflicts, NULL, NULL,
                                               db, local_abspath,
                                               scratch_pool, scratch_pool));

              if (new_conflicts)
                SVN_ERR(svn_wc__conflict_read_info(NULL, NULL, NULL, NULL,
                                                   &tree_conflicted,
                                                   db, local_abspath,
                                                   new_conflicts,
                                                   scratch_pool,
                                                   scratch_pool));

              if (!new_conflicts || !tree_conflicted)
                {
                  /* TC is marked resolved by calling
                     svn_wc__db_op_raise_moved_away */
                  *did_resolve = TRUE;
                  return SVN_NO_ERROR;
                }

              SVN_ERR(svn_wc__conflict_read_tree_conflict(&reason, &action,
                                                          &src_op_root_abspath,
                                                          db, local_abspath,
                                                          new_conflicts,
                                                          scratch_pool,
                                                          scratch_pool));

              if (reason != svn_wc_conflict_reason_moved_away)
                {
                  *did_resolve = TRUE;
                  return SVN_NO_ERROR; /* We fixed one, but... */
                }

              conflicts = new_conflicts;
              /* Fall through in moved_away handling */
            }
          else
            return svn_error_createf(SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE,
                                     NULL,
                                     _("Tree conflict can only be resolved to "
                                       "'working' or 'mine-conflict' state; "
                                       "'%s' not resolved"),
                                     svn_dirent_local_style(local_abspath,
                                                            scratch_pool));
        }

      if (reason == svn_wc_conflict_reason_moved_away
           && action == svn_wc_conflict_action_edit)
        {
          /* After updates, we can resolve local moved-away
           * vs. any incoming change, either by updating the
           * moved-away node (mine-conflict) or by breaking the
           * move (theirs-conflict). */
          if (conflict_choice == svn_wc_conflict_choose_mine_conflict)
            {
              err = svn_wc__db_update_moved_away_conflict_victim(
                        db, local_abspath, src_op_root_abspath,
                        operation, action, reason,
                        cancel_func, cancel_baton,
                        notify_func, notify_baton,
                        scratch_pool);

              if (err)
                SVN_ERR(handle_tree_conflict_resolution_failure(
                          local_abspath, err, resolve_later));
              else
                *did_resolve = TRUE;
            }
          else if (conflict_choice == svn_wc_conflict_choose_merged)
            {
              /* We must break the move if the user accepts the current
               * working copy state instead of updating the move.
               * Else the move would be left in an invalid state. */

              SVN_ERR(svn_wc__db_op_break_moved_away(db, local_abspath,
                                                     src_op_root_abspath, TRUE,
                                                     notify_func, notify_baton,
                                                     scratch_pool));
              *did_resolve = TRUE;
              return SVN_NO_ERROR; /* Conflict is marked resolved */
            }
          else
            return svn_error_createf(SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE,
                                     NULL,
                                     _("Tree conflict can only be resolved to "
                                       "'working' or 'mine-conflict' state; "
                                       "'%s' not resolved"),
                                     svn_dirent_local_style(local_abspath,
                                                            scratch_pool));
        }
      else if (reason == svn_wc_conflict_reason_moved_away
               && action != svn_wc_conflict_action_edit)
        {
          /* action added is impossible, because that would imply that
             something was added, but before that already moved...
             (which would imply a replace) */
          SVN_ERR_ASSERT(action == svn_wc_conflict_action_delete
                         || action == svn_wc_conflict_action_replace);

          if (conflict_choice == svn_wc_conflict_choose_merged)
            {
              /* Whatever was moved is removed at its original location by the
                 update. That must also remove the recording of the move, so
                 we don't have to do anything here. */

              *did_resolve = TRUE;
            }
          else if (conflict_choice == svn_wc_conflict_choose_mine_conflict)
            {
              return svn_error_createf(SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE,
                                       NULL,
                                       _("Tree conflict can only be "
                                         "resolved to 'working' state; "
                                         "'%s' is no longer moved"),
                                       svn_dirent_local_style(local_abspath,
                                                              scratch_pool));
            }
        }
    }

  if (! *did_resolve)
    {
      if (conflict_choice != svn_wc_conflict_choose_merged)
        {
          /* For other tree conflicts, there is no way to pick
           * theirs-full or mine-full, etc. Throw an error if the
           * user expects us to be smarter than we really are. */
          return svn_error_createf(SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE,
                                   NULL,
                                   _("Tree conflict can only be "
                                     "resolved to 'working' state; "
                                     "'%s' not resolved"),
                                   svn_dirent_local_style(local_abspath,
                                                          scratch_pool));
        }
      else
        *did_resolve = TRUE;
    }

  SVN_ERR_ASSERT(*did_resolve);

  SVN_ERR(svn_wc__db_op_mark_resolved(db, local_abspath, FALSE, FALSE, TRUE,
                                      NULL, scratch_pool));
  SVN_ERR(svn_wc__wq_run(db, local_abspath, cancel_func, cancel_baton,
                         scratch_pool));
  return SVN_NO_ERROR;
}