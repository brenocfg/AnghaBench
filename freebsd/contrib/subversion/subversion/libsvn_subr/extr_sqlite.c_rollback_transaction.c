#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_sqlite__db_t ;
struct TYPE_12__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_INTERNAL_ROLLBACK_TRANSACTION ; 
 scalar_t__ SVN_ERR_SQLITE_BUSY ; 
 int /*<<< orphan*/  SVN_ERR_SQLITE_ROLLBACK_FAILED ; 
 TYPE_1__* get_internal_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_all_statements (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* svn_error_compose_create (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* svn_error_create (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__step_done (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
rollback_transaction(svn_sqlite__db_t *db,
                     svn_error_t *error_to_wrap)
{
  svn_sqlite__stmt_t *stmt;
  svn_error_t *err;

  err = get_internal_statement(&stmt, db, STMT_INTERNAL_ROLLBACK_TRANSACTION);
  if (!err)
    {
      err = svn_error_trace(svn_sqlite__step_done(stmt));

      if (err && err->apr_err == SVN_ERR_SQLITE_BUSY)
        {
          /* ### Houston, we have a problem!

             We are trying to rollback but we can't because some
             statements are still busy. This leaves the database
             unusable for future transactions as the current transaction
             is still open.

             As we are returning the actual error as the most relevant
             error in the chain, our caller might assume that it can
             retry/compensate on this error (e.g. SVN_WC_LOCKED), while
             in fact the SQLite database is unusable until the statements
             started within this transaction are reset and the transaction
             aborted.

             We try to compensate by resetting all prepared but unreset
             statements; but we leave the busy error in the chain anyway to
             help diagnosing the original error and help in finding where
             a reset statement is missing. */
          err = svn_error_trace(reset_all_statements(db, err));
          err = svn_error_compose_create(
                      svn_error_trace(svn_sqlite__step_done(stmt)),
                      err);
        }
    }

  if (err)
    {
      /* Rollback failed, use a specific error code. */
      err = svn_error_create(SVN_ERR_SQLITE_ROLLBACK_FAILED, err, NULL);
    }

  return svn_error_compose_create(error_to_wrap, err);
}