#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  wc_id; int /*<<< orphan*/  sdb; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct revert_baton_t {scalar_t__ clear_changelists; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_CLEAR_ACTUAL_NODE_LEAVING_CHANGELIST_RECURSIVE ; 
 int /*<<< orphan*/  STMT_DELETE_ACTUAL_NODE ; 
 int /*<<< orphan*/  STMT_DELETE_ACTUAL_NODE_LEAVING_CHANGELIST_RECURSIVE ; 
 int /*<<< orphan*/  STMT_DELETE_ACTUAL_NODE_RECURSIVE ; 
 int /*<<< orphan*/  STMT_DELETE_NODES_ABOVE_DEPTH_RECURSIVE ; 
 int /*<<< orphan*/  STMT_DELETE_WC_LOCK_ORPHAN_RECURSIVE ; 
 int /*<<< orphan*/  STMT_SELECT_MOVED_HERE_CHILDREN ; 
 int /*<<< orphan*/  STMT_SELECT_MOVED_OUTSIDE ; 
 int /*<<< orphan*/  STMT_SELECT_NODE_INFO ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR_WC_INVALID_OPERATION_DEPTH ; 
 int /*<<< orphan*/  SVN_ERR_WC_PATH_NOT_FOUND ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * clear_moved_to (TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  path_for_error_message (TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int relpath_depth (char const*) ; 
 int /*<<< orphan*/ * svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*,...) ; 
 scalar_t__ svn_sqlite__column_boolean (int /*<<< orphan*/ *,int) ; 
 int svn_sqlite__column_int (int /*<<< orphan*/ *,int) ; 
 char* svn_sqlite__column_text (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_sqlite__step (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_sqlite__step_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_sqlite__update (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__db_op_break_move_internal (TYPE_1__*,char const*,int,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
op_revert_recursive_txn(void *baton,
                        svn_wc__db_wcroot_t *wcroot,
                        const char *local_relpath,
                        apr_pool_t *scratch_pool)
{
  struct revert_baton_t *rvb = baton;
  svn_sqlite__stmt_t *stmt;
  svn_boolean_t have_row;
  int op_depth;
  int select_op_depth;
  svn_boolean_t moved_here;
  int affected_rows;
  apr_pool_t *iterpool;

  /* ### Similar structure to op_revert_txn, should they be
         combined? */

  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_SELECT_NODE_INFO));
  SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));
  SVN_ERR(svn_sqlite__step(&have_row, stmt));
  if (!have_row)
    {
      SVN_ERR(svn_sqlite__reset(stmt));

      SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                        STMT_DELETE_ACTUAL_NODE));
      SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id,
                                local_relpath));
      SVN_ERR(svn_sqlite__update(&affected_rows, stmt));

      if (affected_rows)
        return SVN_NO_ERROR;  /* actual-only revert */

      return svn_error_createf(SVN_ERR_WC_PATH_NOT_FOUND, NULL,
                               _("The node '%s' was not found."),
                               path_for_error_message(wcroot,
                                                      local_relpath,
                                                      scratch_pool));
    }

  op_depth = svn_sqlite__column_int(stmt, 0);
  moved_here = svn_sqlite__column_boolean(stmt, 15);
  SVN_ERR(svn_sqlite__reset(stmt));

  if (op_depth > 0 && op_depth != relpath_depth(local_relpath))
    return svn_error_createf(SVN_ERR_WC_INVALID_OPERATION_DEPTH, NULL,
                             _("Can't revert '%s' without"
                               " reverting parent"),
                             path_for_error_message(wcroot,
                                                    local_relpath,
                                                    scratch_pool));

  /* Remove moved-here from move destinations outside the tree. */
  SVN_ERR(svn_sqlite__get_statement(
                    &stmt, wcroot->sdb, STMT_SELECT_MOVED_OUTSIDE));
  SVN_ERR(svn_sqlite__bindf(stmt, "isd", wcroot->wc_id, local_relpath,
                            op_depth));
  SVN_ERR(svn_sqlite__step(&have_row, stmt));
  while (have_row)
    {
      const char *src_relpath = svn_sqlite__column_text(stmt, 0, NULL);
      const char *dst_relpath = svn_sqlite__column_text(stmt, 1, NULL);
      int move_op_depth = svn_sqlite__column_int(stmt, 2);
      svn_error_t *err;

      err = svn_wc__db_op_break_move_internal(wcroot,
                                              src_relpath, move_op_depth,
                                              dst_relpath, NULL, scratch_pool);
      if (err)
        return svn_error_compose_create(err, svn_sqlite__reset(stmt));

      SVN_ERR(svn_sqlite__step(&have_row, stmt));
    }
  SVN_ERR(svn_sqlite__reset(stmt));

  /* Don't delete BASE nodes */
  select_op_depth = op_depth ? op_depth : 1;

  /* Reverting any non wc-root node */
  SVN_ERR(svn_sqlite__get_statement(
                    &stmt, wcroot->sdb,
                    STMT_DELETE_NODES_ABOVE_DEPTH_RECURSIVE));
  SVN_ERR(svn_sqlite__bindf(stmt, "isd", wcroot->wc_id,
                            local_relpath, select_op_depth));
  SVN_ERR(svn_sqlite__step_done(stmt));

  if (rvb->clear_changelists)
    {
      SVN_ERR(svn_sqlite__get_statement(
                        &stmt, wcroot->sdb,
                        STMT_DELETE_ACTUAL_NODE_RECURSIVE));
      SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));
      SVN_ERR(svn_sqlite__step_done(stmt));
    }
  else
    {
      SVN_ERR(svn_sqlite__get_statement(
                        &stmt, wcroot->sdb,
                        STMT_DELETE_ACTUAL_NODE_LEAVING_CHANGELIST_RECURSIVE));
      SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));
      SVN_ERR(svn_sqlite__step_done(stmt));

      SVN_ERR(svn_sqlite__get_statement(
                        &stmt, wcroot->sdb,
                        STMT_CLEAR_ACTUAL_NODE_LEAVING_CHANGELIST_RECURSIVE));
      SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));
      SVN_ERR(svn_sqlite__step_done(stmt));
    }

  /* ### This removes the locks, but what about the access batons? */
  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_DELETE_WC_LOCK_ORPHAN_RECURSIVE));
  SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id,
                            local_relpath));
  SVN_ERR(svn_sqlite__step_done(stmt));

  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_SELECT_MOVED_HERE_CHILDREN));
  SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));

  SVN_ERR(svn_sqlite__step(&have_row, stmt));

  iterpool = svn_pool_create(scratch_pool);
  while (have_row)
    {
      const char *moved_here_child_relpath;
      svn_error_t *err;

      svn_pool_clear(iterpool);

      moved_here_child_relpath = svn_sqlite__column_text(stmt, 0, iterpool);
      err = clear_moved_to(wcroot, moved_here_child_relpath, iterpool);
      if (err)
        return svn_error_trace(svn_error_compose_create(
                                        err,
                                        svn_sqlite__reset(stmt)));

      SVN_ERR(svn_sqlite__step(&have_row, stmt));
    }
  SVN_ERR(svn_sqlite__reset(stmt));
  svn_pool_destroy(iterpool);

  /* Clear potential moved-to pointing at the target node itself. */
  if (op_depth > 0 && op_depth == relpath_depth(local_relpath)
      && moved_here)
    SVN_ERR(clear_moved_to(wcroot, local_relpath, scratch_pool));

  return SVN_NO_ERROR;
}