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
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_sqlite__db_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct bump_baton {int /*<<< orphan*/  wcroot_abspath; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  STMT_UPGRADE_30_SELECT_CONFLICT_SEPARATE ; 
 int /*<<< orphan*/  STMT_UPGRADE_TO_30 ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * bump_30_upgrade_one_conflict (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__exec_statements (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_open (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
bump_to_30(void *baton, svn_sqlite__db_t *sdb, apr_pool_t *scratch_pool)
{
  struct bump_baton *bb = baton;
  svn_boolean_t have_row;
  apr_pool_t *iterpool = svn_pool_create(scratch_pool);
  svn_sqlite__stmt_t *stmt;
  svn_wc__db_t *db; /* Read only temp db */

  SVN_ERR(svn_wc__db_open(&db, NULL, TRUE /* open_without_upgrade */, FALSE,
                          scratch_pool, scratch_pool));

  SVN_ERR(svn_sqlite__get_statement(&stmt, sdb,
                                    STMT_UPGRADE_30_SELECT_CONFLICT_SEPARATE));
  SVN_ERR(svn_sqlite__step(&have_row, stmt));

  while (have_row)
    {
      svn_error_t *err;
      svn_pool_clear(iterpool);

      err = bump_30_upgrade_one_conflict(db, bb->wcroot_abspath, stmt, sdb,
                                         iterpool);

      if (err)
        {
          return svn_error_trace(
                    svn_error_compose_create(
                            err,
                            svn_sqlite__reset(stmt)));
        }

      SVN_ERR(svn_sqlite__step(&have_row, stmt));
    }
  SVN_ERR(svn_sqlite__reset(stmt));

  SVN_ERR(svn_sqlite__exec_statements(sdb, STMT_UPGRADE_TO_30));
  SVN_ERR(svn_wc__db_close(db));
  return SVN_NO_ERROR;
}