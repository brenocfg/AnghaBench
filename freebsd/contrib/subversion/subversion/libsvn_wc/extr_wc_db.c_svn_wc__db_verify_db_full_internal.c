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
struct TYPE_3__ {int /*<<< orphan*/  abspath; int /*<<< orphan*/  sdb; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/ * (* svn_wc__db_verify_cb_t ) (void*,int /*<<< orphan*/ ,char const*,int,int,char const*,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_STATIC_VERIFY ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int svn_sqlite__column_int (int /*<<< orphan*/ *,int) ; 
 char* svn_sqlite__column_text (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step (scalar_t__*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__db_verify_db_full_internal(svn_wc__db_wcroot_t *wcroot,
                                   svn_wc__db_verify_cb_t callback,
                                   void *baton,
                                   apr_pool_t *scratch_pool)
{
  svn_sqlite__stmt_t *stmt;
  svn_boolean_t have_row;
  svn_error_t *err = NULL;
  apr_pool_t *iterpool = svn_pool_create(scratch_pool);

  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb, STMT_STATIC_VERIFY));
  SVN_ERR(svn_sqlite__step(&have_row, stmt));

  while (have_row)
    {
      const char *local_relpath;
      int op_depth = svn_sqlite__column_int(stmt, 1);
      int id = svn_sqlite__column_int(stmt, 2);
      const char *msg;

      svn_pool_clear(iterpool);

      local_relpath =  svn_sqlite__column_text(stmt, 0, iterpool);
      msg = svn_sqlite__column_text(stmt, 3, scratch_pool);

      err = callback(baton, wcroot->abspath, local_relpath, op_depth,
                     id, msg, iterpool);

      if (err)
        break;

      SVN_ERR(svn_sqlite__step(&have_row, stmt));
    }

  svn_pool_destroy(iterpool);

  return svn_error_trace(
            svn_error_compose_create(err, svn_sqlite__reset(stmt)));
}