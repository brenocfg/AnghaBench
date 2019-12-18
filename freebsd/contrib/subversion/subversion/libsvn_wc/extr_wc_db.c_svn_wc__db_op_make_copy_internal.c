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
struct TYPE_8__ {int /*<<< orphan*/  sdb; int /*<<< orphan*/  wc_id; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  INVALID_REPOS_ID ; 
 int /*<<< orphan*/  STMT_COPY_OP_DEPTH_RECURSIVE ; 
 int /*<<< orphan*/  STMT_INSERT_DELETE_FROM_NODE_RECURSIVE ; 
 int /*<<< orphan*/  STMT_SELECT_WORKING_NODE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_WC_PATH_UNEXPECTED_STATUS ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_work_items (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  catch_copy_of_server_excluded (TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  db_move_moved_to_down_recursive (TYPE_1__*,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_copy_txn (TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  path_for_error_message (TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int relpath_depth (char const*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*,...) ; 
 int svn_sqlite__column_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__update (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_mark_conflict_internal (TYPE_1__*,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__db_op_make_copy_internal(svn_wc__db_wcroot_t *wcroot,
                                 const char *local_relpath,
                                 svn_boolean_t move_move_info,
                                 const svn_skel_t *conflicts,
                                 const svn_skel_t *work_items,
                                 apr_pool_t *scratch_pool)
{
  svn_sqlite__stmt_t *stmt;
  svn_boolean_t have_row;
  int op_depth = -1;

  /* The update editor is supposed to call this function when there is
     no working node for LOCAL_ABSPATH. */
  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_SELECT_WORKING_NODE));
  SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));
  SVN_ERR(svn_sqlite__step(&have_row, stmt));
  if (have_row)
    op_depth = svn_sqlite__column_int(stmt, 0);
  SVN_ERR(svn_sqlite__reset(stmt));

  if (have_row)
    {
      if (op_depth == relpath_depth(local_relpath))
        return svn_error_createf(SVN_ERR_WC_PATH_UNEXPECTED_STATUS, NULL,
                             _("Modification of '%s' already exists"),
                             path_for_error_message(wcroot,
                                                    local_relpath,
                                                    scratch_pool));

      /* We have a working layer, but not one at the op-depth of local-relpath,
         so we can create a copy by just copying the lower layer */

      SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                        STMT_COPY_OP_DEPTH_RECURSIVE));
      SVN_ERR(svn_sqlite__bindf(stmt, "isdd", wcroot->wc_id, local_relpath,
                                op_depth, relpath_depth(local_relpath)));
      SVN_ERR(svn_sqlite__step_done(stmt));
    }
  else
    {
      int affected_rows;

      op_depth = relpath_depth(local_relpath);
      /* We don't allow copies to contain server-excluded nodes;
         the update editor is going to have to bail out. */
      SVN_ERR(catch_copy_of_server_excluded(wcroot, local_relpath,
                                            scratch_pool));

      /* Insert a shadowing layer */
      SVN_ERR(svn_sqlite__get_statement(
                        &stmt, wcroot->sdb,
                        STMT_INSERT_DELETE_FROM_NODE_RECURSIVE));

      /* As we are keeping whatever is below, move the*/

      SVN_ERR(svn_sqlite__bindf(stmt, "isdd",
                                wcroot->wc_id, local_relpath,
                                0, op_depth));
      SVN_ERR(svn_sqlite__update(&affected_rows, stmt));
      SVN_ERR_ASSERT(affected_rows > 0);

      if (!move_move_info)
        SVN_ERR(db_move_moved_to_down_recursive(wcroot, local_relpath,
                                                op_depth, scratch_pool));


      SVN_ERR(make_copy_txn(wcroot, local_relpath,
                            INVALID_REPOS_ID, NULL, SVN_INVALID_REVNUM,
                            op_depth, FALSE, op_depth,
                            scratch_pool));
    }

  if (conflicts)
    SVN_ERR(svn_wc__db_mark_conflict_internal(wcroot, local_relpath,
                                              conflicts, scratch_pool));

  SVN_ERR(add_work_items(wcroot->sdb, work_items, scratch_pool));

  return SVN_NO_ERROR;
}