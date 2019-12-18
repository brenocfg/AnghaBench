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
 int /*<<< orphan*/  STMT_INTERNAL_COMMIT_TRANSACTION ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * get_internal_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rollback_transaction (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__step_done (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_sqlite__finish_transaction(svn_sqlite__db_t *db,
                               svn_error_t *err)
{
  svn_sqlite__stmt_t *stmt;

  /* Commit or rollback the sqlite transaction. */
  if (err)
    {
      return svn_error_trace(rollback_transaction(db, err));
    }
  else
    {
      err = get_internal_statement(&stmt, db,
                                   STMT_INTERNAL_COMMIT_TRANSACTION);
      if (!err)
        err = svn_error_trace(svn_sqlite__step_done(stmt));

      /* Need to rollback if the commit fails as well, because otherwise the
         db connection will be left in an unusable state.

         One important case to keep in mind is trying to COMMIT with concurrent
         readers. In case the commit fails, because someone else is holding a
         shared lock, sqlite keeps the transaction, and *also* keeps the file
         locks on the database. While the first part only prevents from using
         this connection, the second part prevents everyone else from accessing
         the database while the connection is open.

         See https://www.sqlite.org/lang_transaction.html

         COMMIT might also result in an SQLITE_BUSY return code if an another
         thread or process has a shared lock on the database that prevented
         the database from being updated. When COMMIT fails in this way, the
         transaction remains active and the COMMIT can be retried later after
         the reader has had a chance to clear. */
      if (err)
        return svn_error_trace(rollback_transaction(db, err));
    }

  return SVN_NO_ERROR;
}