#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  wc_id; int /*<<< orphan*/  sdb; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct revert_baton_t {scalar_t__ clear_changelists; int /*<<< orphan*/ * db; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_ACTUAL_HAS_CHILDREN ; 
 int /*<<< orphan*/  STMT_CLEAR_ACTUAL_NODE_LEAVING_CHANGELIST ; 
 int /*<<< orphan*/  STMT_DELETE_ACTUAL_NODE ; 
 int /*<<< orphan*/  STMT_DELETE_ACTUAL_NODE_LEAVING_CHANGELIST ; 
 int /*<<< orphan*/  STMT_DELETE_WC_LOCK_ORPHAN ; 
 int /*<<< orphan*/  STMT_DELETE_WORKING_NODE ; 
 int /*<<< orphan*/  STMT_SELECT_GE_OP_DEPTH_CHILDREN ; 
 int /*<<< orphan*/  STMT_SELECT_NODE_INFO ; 
 int /*<<< orphan*/  STMT_UPDATE_OP_DEPTH_INCREASE_RECURSIVE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_WC_INVALID_OPERATION_DEPTH ; 
 int /*<<< orphan*/  SVN_ERR_WC_PATH_NOT_FOUND ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  clear_moved_to (TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  path_for_error_message (TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int relpath_depth (char const*) ; 
 int /*<<< orphan*/  revert_maybe_raise_moved_away (TYPE_1__*,int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*,...) ; 
 scalar_t__ svn_sqlite__column_boolean (int /*<<< orphan*/ *,int) ; 
 int svn_sqlite__column_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* svn_sqlite__column_text (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__update (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_op_break_move_internal (TYPE_1__*,char const*,int,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
op_revert_txn(void *baton,
              svn_wc__db_wcroot_t *wcroot,
              const char *local_relpath,
              apr_pool_t *scratch_pool)
{
  struct revert_baton_t *rvb = baton;
  svn_wc__db_t *db = rvb->db;
  svn_sqlite__stmt_t *stmt;
  svn_boolean_t have_row;
  int op_depth;
  svn_boolean_t moved_here;
  int affected_rows;
  const char *moved_to;
  int op_depth_below;

  /* ### Similar structure to op_revert_recursive_txn, should they be
         combined? */

  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_SELECT_NODE_INFO));
  SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));
  SVN_ERR(svn_sqlite__step(&have_row, stmt));
  if (!have_row)
    {
      SVN_ERR(svn_sqlite__reset(stmt));

      /* There was no NODE row, so attempt to delete an ACTUAL_NODE row.  */
      SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                        STMT_DELETE_ACTUAL_NODE));
      SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));
      SVN_ERR(svn_sqlite__update(&affected_rows, stmt));
      if (affected_rows)
        {
          /* Can't do non-recursive actual-only revert if actual-only
             children exist. Raise an error to cancel the transaction.  */
          SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                            STMT_ACTUAL_HAS_CHILDREN));
          SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));
          SVN_ERR(svn_sqlite__step(&have_row, stmt));
          SVN_ERR(svn_sqlite__reset(stmt));
          if (have_row)
            return svn_error_createf(SVN_ERR_WC_INVALID_OPERATION_DEPTH, NULL,
                                     _("Can't revert '%s' without"
                                       " reverting children"),
                                     path_for_error_message(wcroot,
                                                            local_relpath,
                                                            scratch_pool));
          return SVN_NO_ERROR;
        }

      return svn_error_createf(SVN_ERR_WC_PATH_NOT_FOUND, NULL,
                               _("The node '%s' was not found."),
                               path_for_error_message(wcroot,
                                                      local_relpath,
                                                      scratch_pool));
    }

  op_depth = svn_sqlite__column_int(stmt, 0);
  moved_here = svn_sqlite__column_boolean(stmt, 15);
  moved_to = svn_sqlite__column_text(stmt, 17, scratch_pool);

  SVN_ERR(svn_sqlite__step(&have_row, stmt));
  if (have_row)
    op_depth_below = svn_sqlite__column_int(stmt, 0);
  else
    op_depth_below = -1;

  SVN_ERR(svn_sqlite__reset(stmt));

  if (moved_to)
    {
      SVN_ERR(svn_wc__db_op_break_move_internal(wcroot,
                                                local_relpath, op_depth,
                                                moved_to, NULL, scratch_pool));
    }

  if (op_depth > 0 && op_depth == relpath_depth(local_relpath))
    {
      int op_depth_increased;

      /* Can't do non-recursive revert if children exist */
      SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                        STMT_SELECT_GE_OP_DEPTH_CHILDREN));
      SVN_ERR(svn_sqlite__bindf(stmt, "isd", wcroot->wc_id,
                                local_relpath, op_depth));
      SVN_ERR(svn_sqlite__step(&have_row, stmt));
      SVN_ERR(svn_sqlite__reset(stmt));
      if (have_row)
        return svn_error_createf(SVN_ERR_WC_INVALID_OPERATION_DEPTH, NULL,
                                 _("Can't revert '%s' without"
                                   " reverting children"),
                                 path_for_error_message(wcroot,
                                                        local_relpath,
                                                        scratch_pool));

      /* Rewrite the op-depth of all deleted children making the
         direct children into roots of deletes. */
      SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                     STMT_UPDATE_OP_DEPTH_INCREASE_RECURSIVE));
      SVN_ERR(svn_sqlite__bindf(stmt, "isd", wcroot->wc_id,
                                local_relpath,
                                op_depth));
      SVN_ERR(svn_sqlite__update(&op_depth_increased, stmt));

      SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                        STMT_DELETE_WORKING_NODE));
      SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));
      SVN_ERR(svn_sqlite__step_done(stmt));

      /* ### This removes the lock, but what about the access baton? */
      SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                        STMT_DELETE_WC_LOCK_ORPHAN));
      SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));
      SVN_ERR(svn_sqlite__step_done(stmt));

      /* If this node was moved-here, clear moved-to at the move source. */
      if (moved_here)
        SVN_ERR(clear_moved_to(wcroot, local_relpath, scratch_pool));

      /* If the node was moved itself, we don't have interesting moved
         children (and the move itself was already broken) */
      if (op_depth_increased && !moved_to)
        SVN_ERR(revert_maybe_raise_moved_away(wcroot, db, local_relpath,
                                              op_depth_below, scratch_pool));
    }

  if (rvb->clear_changelists)
    {
      SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                        STMT_DELETE_ACTUAL_NODE));
      SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));
      SVN_ERR(svn_sqlite__update(&affected_rows, stmt));
    }
  else
    {
      SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                  STMT_DELETE_ACTUAL_NODE_LEAVING_CHANGELIST));
      SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));
      SVN_ERR(svn_sqlite__update(&affected_rows, stmt));
      if (!affected_rows)
        {
          SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                  STMT_CLEAR_ACTUAL_NODE_LEAVING_CHANGELIST));
          SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));
          SVN_ERR(svn_sqlite__update(&affected_rows, stmt));
        }
    }

  return SVN_NO_ERROR;
}