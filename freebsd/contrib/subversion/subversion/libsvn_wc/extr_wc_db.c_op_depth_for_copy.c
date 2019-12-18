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
typedef  scalar_t__ svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_SELECT_WORKING_NODE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  presence_map ; 
 int relpath_depth (char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_relpath_join (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_relpath_split (char const**,char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*) ; 
 int svn_sqlite__column_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_sqlite__column_int64 (int /*<<< orphan*/ *,int) ; 
 scalar_t__ svn_sqlite__column_revnum (int /*<<< orphan*/ *,int) ; 
 char* svn_sqlite__column_text (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_sqlite__column_token (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step (scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__db_status_incomplete ; 
 scalar_t__ svn_wc__db_status_normal ; 

__attribute__((used)) static svn_error_t *
op_depth_for_copy(int *op_depth,
                  int *np_op_depth,
                  int *parent_op_depth,
                  apr_int64_t copyfrom_repos_id,
                  const char *copyfrom_relpath,
                  svn_revnum_t copyfrom_revision,
                  svn_wc__db_wcroot_t *wcroot,
                  const char *local_relpath,
                  apr_pool_t *scratch_pool)
{
  const char *parent_relpath, *name;
  svn_sqlite__stmt_t *stmt;
  svn_boolean_t have_row;
  int incomplete_op_depth = -1;
  int min_op_depth = 1; /* Never touch BASE */

  *op_depth = relpath_depth(local_relpath);
  *np_op_depth = -1;

  svn_relpath_split(&parent_relpath, &name, local_relpath, scratch_pool);
  *parent_op_depth = relpath_depth(parent_relpath);

  if (!copyfrom_relpath)
    return SVN_NO_ERROR;

  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_SELECT_WORKING_NODE));
  SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));
  SVN_ERR(svn_sqlite__step(&have_row, stmt));
  if (have_row)
    {
      svn_wc__db_status_t status = svn_sqlite__column_token(stmt, 1,
                                                            presence_map);

      min_op_depth = svn_sqlite__column_int(stmt, 0);
      if (status == svn_wc__db_status_incomplete)
        incomplete_op_depth = min_op_depth;
    }
  SVN_ERR(svn_sqlite__reset(stmt));

  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_SELECT_WORKING_NODE));
  SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, parent_relpath));
  SVN_ERR(svn_sqlite__step(&have_row, stmt));
  if (have_row)
    {
      svn_wc__db_status_t presence = svn_sqlite__column_token(stmt, 1,
                                                              presence_map);

      *parent_op_depth = svn_sqlite__column_int(stmt, 0);
      if (*parent_op_depth < min_op_depth)
        {
          /* We want to create a copy; not overwrite the lower layers */
          SVN_ERR(svn_sqlite__reset(stmt));
          return SVN_NO_ERROR;
        }

      /* You can only add children below a node that exists.
         In WORKING that must be status added, which is represented
         as presence normal */
      SVN_ERR_ASSERT(presence == svn_wc__db_status_normal);

      if ((incomplete_op_depth < 0)
          || (incomplete_op_depth == *parent_op_depth))
        {
          apr_int64_t parent_copyfrom_repos_id
            = svn_sqlite__column_int64(stmt, 10);
          const char *parent_copyfrom_relpath
            = svn_sqlite__column_text(stmt, 11, NULL);
          svn_revnum_t parent_copyfrom_revision
            = svn_sqlite__column_revnum(stmt, 12);

          if (parent_copyfrom_repos_id == copyfrom_repos_id)
            {
              if (copyfrom_revision == parent_copyfrom_revision
                  && !strcmp(copyfrom_relpath,
                             svn_relpath_join(parent_copyfrom_relpath, name,
                                              scratch_pool)))
                *op_depth = *parent_op_depth;
              else if (incomplete_op_depth > 0)
                *np_op_depth = incomplete_op_depth;
            }
        }
    }
  SVN_ERR(svn_sqlite__reset(stmt));

  return SVN_NO_ERROR;
}