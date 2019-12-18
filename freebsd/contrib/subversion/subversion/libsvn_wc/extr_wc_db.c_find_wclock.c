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
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_SELECT_ANCESTOR_WCLOCKS ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 char* apr_pstrndup (int /*<<< orphan*/ *,char const*,int) ; 
 int relpath_depth (char const*) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 scalar_t__ svn_relpath_skip_ancestor (char const*,char const*) ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*,char const*) ; 
 int svn_sqlite__column_int (int /*<<< orphan*/ *,int) ; 
 char* svn_sqlite__column_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step (scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
find_wclock(const char **lock_relpath,
            svn_wc__db_wcroot_t *wcroot,
            const char *dir_relpath,
            apr_pool_t *result_pool,
            apr_pool_t *scratch_pool)
{
  svn_sqlite__stmt_t *stmt;
  svn_boolean_t have_row;
  int dir_depth = relpath_depth(dir_relpath);
  const char *first_relpath;

  /* Check for locks on all directories that might be ancestors.
     As our new apis only use recursive locks the number of locks stored
     in the DB will be very low */
  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_SELECT_ANCESTOR_WCLOCKS));

  /* Get the top level relpath to reduce the worst case number of results
     to the number of directories below this node plus two.
     (1: the node itself and 2: the wcroot). */
  first_relpath = strchr(dir_relpath, '/');

  if (first_relpath != NULL)
    first_relpath = apr_pstrndup(scratch_pool, dir_relpath,
                                 first_relpath - dir_relpath);
  else
    first_relpath = dir_relpath;

  SVN_ERR(svn_sqlite__bindf(stmt, "iss",
                            wcroot->wc_id,
                            dir_relpath,
                            first_relpath));

  SVN_ERR(svn_sqlite__step(&have_row, stmt));

  while (have_row)
    {
      const char *relpath = svn_sqlite__column_text(stmt, 0, NULL);

      if (svn_relpath_skip_ancestor(relpath, dir_relpath))
        {
          int locked_levels = svn_sqlite__column_int(stmt, 1);
          int row_depth = relpath_depth(relpath);

          if (locked_levels == -1
              || locked_levels + row_depth >= dir_depth)
            {
              *lock_relpath = apr_pstrdup(result_pool, relpath);
              SVN_ERR(svn_sqlite__reset(stmt));
              return SVN_NO_ERROR;
            }
        }

      SVN_ERR(svn_sqlite__step(&have_row, stmt));
    }

  *lock_relpath = NULL;

  return svn_error_trace(svn_sqlite__reset(stmt));
}