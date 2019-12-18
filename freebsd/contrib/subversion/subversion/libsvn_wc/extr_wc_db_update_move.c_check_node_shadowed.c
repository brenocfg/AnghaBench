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
struct TYPE_3__ {int /*<<< orphan*/  wc_id; int /*<<< orphan*/  sdb; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  STMT_SELECT_WORKING_NODE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*) ; 
 int svn_sqlite__column_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step (int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
check_node_shadowed(svn_boolean_t *shadowed,
                    svn_wc__db_wcroot_t *wcroot,
                    const char *local_relpath,
                    int move_root_dst_op_depth,
                    apr_pool_t *scratch_pool)
{
  svn_sqlite__stmt_t *stmt;
  svn_boolean_t have_row;

  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_SELECT_WORKING_NODE));
  SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));

  SVN_ERR(svn_sqlite__step(&have_row, stmt));

  if (have_row)
    {
      int op_depth = svn_sqlite__column_int(stmt, 0);

      *shadowed = (op_depth > move_root_dst_op_depth);
    }
  else
    *shadowed = FALSE;
  SVN_ERR(svn_sqlite__reset(stmt));

  return SVN_NO_ERROR;
}