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
 int /*<<< orphan*/  STMT_UPDATE_MOVED_TO_RELPATH ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_WC_PATH_NOT_FOUND ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*,int,...) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__update (int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
db_move_moved_to(svn_wc__db_wcroot_t *wcroot,
                 const char *src1_relpath,
                 int src1_op_depth,
                 const char *src2_relpath,
                 int src2_op_depth,
                 const char *dst_relpath,
                 apr_pool_t *scratch_pool)
{
  svn_sqlite__stmt_t *stmt;
  int affected_rows;

  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                     STMT_UPDATE_MOVED_TO_RELPATH));
  SVN_ERR(svn_sqlite__bindf(stmt, "isd", wcroot->wc_id,
                            src1_relpath, src1_op_depth));
  SVN_ERR(svn_sqlite__update(&affected_rows, stmt));

  if (affected_rows == 1)
    {
      SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                     STMT_UPDATE_MOVED_TO_RELPATH));
      SVN_ERR(svn_sqlite__bindf(stmt, "isds", wcroot->wc_id,
                                src2_relpath, src2_op_depth,
                                dst_relpath));
      SVN_ERR(svn_sqlite__update(&affected_rows, stmt));
    }
  if (affected_rows != 1)
    return svn_error_create(SVN_ERR_WC_PATH_NOT_FOUND, NULL, NULL);

  return SVN_NO_ERROR;
}