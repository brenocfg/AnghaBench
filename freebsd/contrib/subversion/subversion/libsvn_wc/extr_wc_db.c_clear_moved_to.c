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
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_CLEAR_MOVED_TO_RELPATH ; 
 int /*<<< orphan*/  STMT_SELECT_MOVED_FROM_RELPATH ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*,...) ; 
 int svn_sqlite__column_int (int /*<<< orphan*/ *,int) ; 
 char* svn_sqlite__column_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step_row (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__update (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
clear_moved_to(svn_wc__db_wcroot_t *wcroot,
               const char *moved_to_relpath,
               apr_pool_t *scratch_pool)
{
  svn_sqlite__stmt_t *stmt;
  const char *moved_from_relpath;
  int moved_from_op_depth;

  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_SELECT_MOVED_FROM_RELPATH));
  SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, moved_to_relpath));
  SVN_ERR(svn_sqlite__step_row(stmt));

  moved_from_relpath = svn_sqlite__column_text(stmt, 0, scratch_pool);
  moved_from_op_depth = svn_sqlite__column_int(stmt, 1);
  SVN_ERR(svn_sqlite__reset(stmt));

  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_CLEAR_MOVED_TO_RELPATH));
  SVN_ERR(svn_sqlite__bindf(stmt, "isd", wcroot->wc_id,
                            moved_from_relpath, moved_from_op_depth));
  SVN_ERR(svn_sqlite__update(NULL, stmt));

  return SVN_NO_ERROR;
}