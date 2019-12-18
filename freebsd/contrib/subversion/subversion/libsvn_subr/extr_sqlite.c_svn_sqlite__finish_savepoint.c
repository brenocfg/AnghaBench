#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_sqlite__db_t ;
struct TYPE_11__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_INTERNAL_RELEASE_SAVEPOINT_SVN ; 
 int /*<<< orphan*/  STMT_INTERNAL_ROLLBACK_TO_SAVEPOINT_SVN ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_1__*) ; 
 scalar_t__ SVN_ERR_SQLITE_BUSY ; 
 TYPE_1__* get_internal_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_all_statements (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* svn_error_compose_create (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__step_done (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_sqlite__finish_savepoint(svn_sqlite__db_t *db,
                             svn_error_t *err)
{
  svn_sqlite__stmt_t *stmt;

  if (err)
    {
      svn_error_t *err2;

      err2 = get_internal_statement(&stmt, db,
                                    STMT_INTERNAL_ROLLBACK_TO_SAVEPOINT_SVN);

      if (!err2)
        {
          err2 = svn_error_trace(svn_sqlite__step_done(stmt));

          if (err2 && err2->apr_err == SVN_ERR_SQLITE_BUSY)
            {
              /* Ok, we have a major problem. Some statement is still open,
                 which makes it impossible to release this savepoint.

                 ### See huge comment in rollback_transaction() for
                     further details */

              err2 = svn_error_trace(reset_all_statements(db, err2));
              err2 = svn_error_compose_create(
                          svn_error_trace(svn_sqlite__step_done(stmt)),
                          err2);
            }
        }

      err = svn_error_compose_create(err, err2);
      err2 = get_internal_statement(&stmt, db,
                                    STMT_INTERNAL_RELEASE_SAVEPOINT_SVN);

      if (!err2)
        err2 = svn_error_trace(svn_sqlite__step_done(stmt));

      return svn_error_compose_create(err, err2);
    }

  SVN_ERR(get_internal_statement(&stmt, db,
                                 STMT_INTERNAL_RELEASE_SAVEPOINT_SVN));

  /* ### Releasing a savepoint can fail and leave the db connection
         unusable; see svn_sqlite__finish_transaction(). */
  return svn_error_trace(svn_sqlite__step_done(stmt));
}