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
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_sqlite__db_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prepare_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int svn_sqlite__column_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step_row (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_sqlite__read_schema_version(int *version,
                                svn_sqlite__db_t *db,
                                apr_pool_t *scratch_pool)
{
  svn_sqlite__stmt_t *stmt;

  SVN_ERR(prepare_statement(&stmt, db, "PRAGMA user_version;", scratch_pool));
  SVN_ERR(svn_sqlite__step_row(stmt));

  *version = svn_sqlite__column_int(stmt, 0);

  return svn_error_trace(svn_sqlite__finalize(stmt));
}