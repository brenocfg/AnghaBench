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
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_CREATE_UPDATE_MOVE_LIST ; 
 int /*<<< orphan*/  STMT_SELECT_MOVED_DESCENDANTS_SRC ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kind_map ; 
 int /*<<< orphan*/ * svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*,int) ; 
 int svn_sqlite__column_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* svn_sqlite__column_text (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__column_token (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__exec_statements (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_op_break_move_internal (TYPE_1__*,char const*,int,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_move_broken ; 
 int /*<<< orphan*/  svn_wc_notify_state_inapplicable ; 
 int /*<<< orphan*/  update_move_list_add (TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * verify_write_lock (TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
break_moved_away(svn_wc__db_wcroot_t *wcroot,
                 svn_wc__db_t *db,
                 const char *local_relpath,
                 int parent_src_op_depth,
                 apr_pool_t *scratch_pool)
{
  svn_sqlite__stmt_t *stmt;
  svn_boolean_t have_row;
  apr_pool_t *iterpool;
  svn_error_t *err = NULL;

  SVN_ERR(svn_sqlite__exec_statements(wcroot->sdb,
                                      STMT_CREATE_UPDATE_MOVE_LIST));

  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_SELECT_MOVED_DESCENDANTS_SRC));
  SVN_ERR(svn_sqlite__bindf(stmt, "isd", wcroot->wc_id, local_relpath,
                            parent_src_op_depth));
  SVN_ERR(svn_sqlite__step(&have_row, stmt));

  iterpool = svn_pool_create(scratch_pool);
  while (have_row)
    {
      int src_op_depth = svn_sqlite__column_int(stmt, 0);
      const char *src_relpath = svn_sqlite__column_text(stmt, 1, NULL);
      svn_node_kind_t src_kind = svn_sqlite__column_token(stmt, 2, kind_map);
      const char *dst_relpath = svn_sqlite__column_text(stmt, 4, NULL);

      svn_pool_clear(iterpool);

      err = verify_write_lock(wcroot, src_relpath, iterpool);

      if (!err)
        err = verify_write_lock(wcroot, dst_relpath, iterpool);

      if (err)
        break;

      err = svn_error_trace(
              svn_wc__db_op_break_move_internal(wcroot,
                                                src_relpath, src_op_depth,
                                                dst_relpath, NULL, iterpool));

      if (err)
        break;

      err = svn_error_trace(
              update_move_list_add(wcroot, src_relpath, db,
                                   svn_wc_notify_move_broken,
                                   src_kind,
                                   svn_wc_notify_state_inapplicable,
                                   svn_wc_notify_state_inapplicable,
                                   NULL, NULL, scratch_pool));

      if (err)
        break;

      SVN_ERR(svn_sqlite__step(&have_row, stmt));
    }
  svn_pool_destroy(iterpool);

  return svn_error_compose_create(err, svn_sqlite__reset(stmt));
}