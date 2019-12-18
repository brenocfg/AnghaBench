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
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_SELECT_ALL_NODES ; 
 int /*<<< orphan*/  STMT_SELECT_NODE_INFO ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int relpath_depth (char const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_relpath_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 int svn_sqlite__column_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_sqlite__column_is_null (int /*<<< orphan*/ *,int) ; 
 char* svn_sqlite__column_text (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step (int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
verify_wcroot(svn_wc__db_wcroot_t *wcroot,
              apr_pool_t *scratch_pool)
{
  svn_sqlite__stmt_t *stmt;
  apr_pool_t *iterpool = svn_pool_create(scratch_pool);

  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_SELECT_ALL_NODES));
  SVN_ERR(svn_sqlite__bindf(stmt, "i", wcroot->wc_id));
  while (TRUE)
    {
      svn_boolean_t have_row;
      const char *local_relpath, *parent_relpath;
      int op_depth;

      svn_pool_clear(iterpool);

      SVN_ERR(svn_sqlite__step(&have_row, stmt));
      if (!have_row)
        break;

      op_depth = svn_sqlite__column_int(stmt, 0);
      local_relpath = svn_sqlite__column_text(stmt, 1, iterpool);
      parent_relpath = svn_sqlite__column_text(stmt, 2, iterpool);

      /* Verify parent_relpath is the parent path of local_relpath */
      VERIFY((parent_relpath == NULL)
             ? (local_relpath[0] == '\0')
             : (strcmp(svn_relpath_dirname(local_relpath, iterpool),
                       parent_relpath) == 0));

      /* Verify op_depth <= the tree depth of local_relpath */
      VERIFY(op_depth <= relpath_depth(local_relpath));

      /* Verify parent_relpath refers to a row that exists */
      /* TODO: Verify there is a suitable parent row - e.g. has op_depth <=
       * the child's and a suitable presence */
      if (parent_relpath && svn_sqlite__column_is_null(stmt, 3))
        {
          svn_sqlite__stmt_t *stmt2;
          svn_boolean_t have_a_parent_row;

          SVN_ERR(svn_sqlite__get_statement(&stmt2, wcroot->sdb,
                                            STMT_SELECT_NODE_INFO));
          SVN_ERR(svn_sqlite__bindf(stmt2, "is", wcroot->wc_id,
                                    parent_relpath));
          SVN_ERR(svn_sqlite__step(&have_a_parent_row, stmt2));
          VERIFY(have_a_parent_row);
          SVN_ERR(svn_sqlite__reset(stmt2));
        }
    }
  svn_pool_destroy(iterpool);

  return svn_error_trace(svn_sqlite__reset(stmt));
}