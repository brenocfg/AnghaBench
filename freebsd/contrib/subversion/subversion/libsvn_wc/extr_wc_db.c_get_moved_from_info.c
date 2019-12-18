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
 int /*<<< orphan*/  STMT_SELECT_MOVED_FROM_RELPATH ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 char* svn_relpath_join (char const*,char const*,int /*<<< orphan*/ *) ; 
 char* svn_relpath_skip_ancestor (char const*,char const*) ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*) ; 
 int svn_sqlite__column_int (int /*<<< orphan*/ *,int) ; 
 char* svn_sqlite__column_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_moved_from_info(const char **moved_from_relpath,
                    const char **moved_from_op_root_relpath,
                    const char *moved_to_op_root_relpath,
                    int *op_depth,
                    svn_wc__db_wcroot_t *wcroot,
                    const char *local_relpath,
                    apr_pool_t *result_pool,
                    apr_pool_t *scratch_pool)
{
  svn_sqlite__stmt_t *stmt;
  svn_boolean_t have_row;

  /* Run a query to get the moved-from path from the DB. */
  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_SELECT_MOVED_FROM_RELPATH));
  SVN_ERR(svn_sqlite__bindf(stmt, "is",
                            wcroot->wc_id, moved_to_op_root_relpath));
  SVN_ERR(svn_sqlite__step(&have_row, stmt));

  if (!have_row)
    {
      /* The move was only recorded at the copy-half, possibly because
       * the move operation was interrupted mid-way between the copy
       * and the delete. Treat this node as a normal copy. */
      if (moved_from_relpath)
        *moved_from_relpath = NULL;
      if (moved_from_op_root_relpath)
        *moved_from_op_root_relpath = NULL;

      SVN_ERR(svn_sqlite__reset(stmt));
      return SVN_NO_ERROR;
    }

  if (op_depth)
    *op_depth = svn_sqlite__column_int(stmt, 1);

  if (moved_from_relpath || moved_from_op_root_relpath)
    {
      const char *db_delete_op_root_relpath;

      /* The moved-from path from the DB is the relpath of
       * the op_root of the delete-half of the move. */
      db_delete_op_root_relpath = svn_sqlite__column_text(stmt, 0,
                                                          result_pool);
      if (moved_from_op_root_relpath)
        *moved_from_op_root_relpath = db_delete_op_root_relpath;

      if (moved_from_relpath)
        {
          if (strcmp(moved_to_op_root_relpath, local_relpath) == 0)
            {
              /* LOCAL_RELPATH is the op_root of the copied-half of the
               * move, so the correct MOVED_FROM_ABSPATH is the op-root
               * of the delete-half. */
              *moved_from_relpath = db_delete_op_root_relpath;
            }
          else
            {
              const char *child_relpath;

              /* LOCAL_RELPATH is a child that was copied along with the
               * op_root of the copied-half of the move. Construct the
               * corresponding path beneath the op_root of the delete-half. */

              /* Grab the child path relative to the op_root of the move
               * destination. */
              child_relpath = svn_relpath_skip_ancestor(
                                moved_to_op_root_relpath, local_relpath);

              SVN_ERR_ASSERT(child_relpath && strlen(child_relpath) > 0);

              /* This join is valid because LOCAL_RELPATH has not been moved
               * within the copied-half of the move yet -- else, it would
               * be its own op_root. */
              *moved_from_relpath = svn_relpath_join(db_delete_op_root_relpath,
                                                     child_relpath,
                                                     result_pool);
            }
        }
    }

  SVN_ERR(svn_sqlite__reset(stmt));

  return SVN_NO_ERROR;
}