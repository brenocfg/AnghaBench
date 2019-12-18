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

/* Variables and functions */
 int /*<<< orphan*/  STMT_INTERNAL_BEGIN_IMMEDIATE_TRANSACTION ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  get_internal_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__step_done (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_sqlite__begin_immediate_transaction(svn_sqlite__db_t *db)
{
  svn_sqlite__stmt_t *stmt;

  SVN_ERR(get_internal_statement(&stmt, db,
                                 STMT_INTERNAL_BEGIN_IMMEDIATE_TRANSACTION));
  SVN_ERR(svn_sqlite__step_done(stmt));
  return SVN_NO_ERROR;
}