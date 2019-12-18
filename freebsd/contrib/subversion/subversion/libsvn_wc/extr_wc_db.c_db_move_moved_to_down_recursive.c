#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  wc_id; int /*<<< orphan*/  sdb; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_SELECT_MOVED_DESCENDANTS_SRC ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  db_move_moved_to (TYPE_1__*,char const*,int,char const*,int,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*,int) ; 
 int svn_sqlite__column_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* svn_sqlite__column_text (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step (scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
db_move_moved_to_down_recursive(svn_wc__db_wcroot_t *wcroot,
                                const char *local_relpath,
                                int new_shadow_layer,
                                apr_pool_t *scratch_pool)
{
  svn_sqlite__stmt_t *stmt;
  svn_boolean_t have_row;
  apr_pool_t *iterpool = svn_pool_create(scratch_pool);

  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                        STMT_SELECT_MOVED_DESCENDANTS_SRC));
  SVN_ERR(svn_sqlite__bindf(stmt, "isd", wcroot->wc_id, local_relpath,
                            new_shadow_layer));
  SVN_ERR(svn_sqlite__step(&have_row, stmt));

  while (have_row)
    {
      int del_op_depth;
      const char *src_relpath;
      const char *dst_relpath;
      svn_error_t *err;

      svn_pool_clear(iterpool);

      del_op_depth = svn_sqlite__column_int(stmt, 0);
      src_relpath = svn_sqlite__column_text(stmt, 1, iterpool);
      dst_relpath = svn_sqlite__column_text(stmt, 4, iterpool);

      err = svn_error_trace(
               db_move_moved_to(
                             wcroot,
                             src_relpath, del_op_depth,
                             src_relpath, new_shadow_layer,
                             dst_relpath, iterpool));

      if (err)
        return svn_error_compose_create(err, svn_sqlite__reset(stmt));

      SVN_ERR(svn_sqlite__step(&have_row, stmt));
    }

  SVN_ERR(svn_sqlite__reset(stmt));

  return SVN_NO_ERROR;
}