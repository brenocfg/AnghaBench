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
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_SELECT_MOVED_FROM_FOR_DELETE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int relpath_depth (char const*) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 char* svn_relpath_join (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_relpath_skip_ancestor (char const*,char const*) ; 
 int /*<<< orphan*/  svn_relpath_split (char const**,char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*) ; 
 int svn_sqlite__column_int (int /*<<< orphan*/ *,int) ; 
 char* svn_sqlite__column_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
resolve_moved_from(const char **moved_from_relpath,
                   int *moved_from_op_depth,
                   svn_wc__db_wcroot_t *wcroot,
                   const char *root_relpath,
                   const char *local_relpath,
                   int op_depth,
                   apr_pool_t *result_pool,
                   apr_pool_t *scratch_pool)
{
  const char *suffix = "";
  svn_sqlite__stmt_t *stmt;
  const char *m_from_relpath;
  int m_from_op_depth;
  int m_move_from_depth;
  svn_boolean_t have_row;

  while (relpath_depth(local_relpath) > op_depth)
    {
      const char *name;
      svn_relpath_split(&local_relpath, &name, local_relpath, scratch_pool);
      suffix = svn_relpath_join(suffix, name, scratch_pool);
    }

  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_SELECT_MOVED_FROM_FOR_DELETE));
  SVN_ERR(svn_sqlite__bindf(stmt, "is",
                            wcroot->wc_id, local_relpath));
  SVN_ERR(svn_sqlite__step(&have_row, stmt));

  if (!have_row)
    {
      /* assert(have_row); */
      *moved_from_relpath = NULL;
      *moved_from_op_depth = -1;

      SVN_ERR(svn_sqlite__reset(stmt));

      return SVN_NO_ERROR;
    }

  m_from_relpath = svn_sqlite__column_text(stmt, 0, scratch_pool);
  m_from_op_depth = svn_sqlite__column_int(stmt, 1);
  m_move_from_depth = svn_sqlite__column_int(stmt, 2);

  SVN_ERR(svn_sqlite__reset(stmt));

  if (! svn_relpath_skip_ancestor(root_relpath, m_from_relpath))
    {
      *moved_from_relpath = svn_relpath_join(m_from_relpath, suffix,
                                             result_pool);
      *moved_from_op_depth = m_from_op_depth; /* ### Ok? */
      return SVN_NO_ERROR;
    }
  else if (!m_move_from_depth)
    {
      *moved_from_relpath = NULL;
      *moved_from_op_depth = -1;
      return SVN_NO_ERROR;
    }

  return svn_error_trace(
        resolve_moved_from(moved_from_relpath,
                           moved_from_op_depth,
                           wcroot,
                           root_relpath,
                           svn_relpath_join(m_from_relpath, suffix,
                                            scratch_pool),
                           m_move_from_depth,
                           result_pool, scratch_pool));
}