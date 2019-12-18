#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  wc_id; int /*<<< orphan*/  sdb; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  scalar_t__ svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_int64_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  STMT_DELETE_WORKING_OP_DEPTH ; 
 int /*<<< orphan*/  STMT_SELECT_MOVED_BACK ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (scalar_t__) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  add_work_items (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  op_depth_of (int*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  presence_map ; 
 int /*<<< orphan*/  relpath_depth (char const*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  svn_relpath_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*,int,...) ; 
 scalar_t__ svn_sqlite__column_boolean (int /*<<< orphan*/ *,int) ; 
 scalar_t__ svn_sqlite__column_int64 (int /*<<< orphan*/ *,int) ; 
 scalar_t__ svn_sqlite__column_is_null (int /*<<< orphan*/ *,int) ; 
 scalar_t__ svn_sqlite__column_revnum (int /*<<< orphan*/ *,int) ; 
 char* svn_sqlite__column_text (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_sqlite__column_token (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_info_internal (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__db_status_added ; 
 scalar_t__ svn_wc__db_status_excluded ; 
 scalar_t__ svn_wc__db_status_normal ; 
 scalar_t__ svn_wc__db_status_not_present ; 

__attribute__((used)) static svn_error_t *
handle_move_back(svn_boolean_t *moved_back,
                 svn_wc__db_wcroot_t *wcroot,
                 const char *local_relpath,
                 const char *moved_from_relpath,
                 const svn_skel_t *work_items,
                 apr_pool_t *scratch_pool)
{
  svn_sqlite__stmt_t *stmt;
  svn_wc__db_status_t status;
  svn_boolean_t op_root;
  svn_boolean_t have_more_work;
  int from_op_depth = 0;
  svn_boolean_t have_row;
  svn_boolean_t different = FALSE;

  SVN_ERR(add_work_items(wcroot->sdb, work_items, scratch_pool));

  SVN_ERR(svn_wc__db_read_info_internal(&status, NULL, NULL, NULL, NULL, NULL,
                                        NULL, NULL, NULL, NULL, NULL, NULL,
                                        NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                        &op_root, NULL, NULL, NULL,
                                        &have_more_work, NULL,
                                        wcroot, local_relpath,
                                        scratch_pool, scratch_pool));

  if (status != svn_wc__db_status_added || !op_root)
    return SVN_NO_ERROR;

  /* We have two cases here: BASE-move-back and WORKING-move-back */
  if (have_more_work)
    SVN_ERR(op_depth_of(&from_op_depth, wcroot,
                        svn_relpath_dirname(local_relpath, scratch_pool)));
  else
    from_op_depth = 0;

  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_SELECT_MOVED_BACK));

  SVN_ERR(svn_sqlite__bindf(stmt, "isdd", wcroot->wc_id,
                                          local_relpath,
                                          from_op_depth,
                                          relpath_depth(local_relpath)));

  SVN_ERR(svn_sqlite__step(&have_row, stmt));

  SVN_ERR_ASSERT(have_row); /* We checked that the node is an op-root */

  {
    svn_boolean_t moved_here = svn_sqlite__column_boolean(stmt, 9);
    const char *moved_to = svn_sqlite__column_text(stmt, 10, NULL);

    if (!moved_here
        || !moved_to
        || strcmp(moved_to, moved_from_relpath))
      {
        different = TRUE;
        have_row = FALSE;
      }
  }

  while (have_row)
    {
      svn_wc__db_status_t upper_status;
      svn_wc__db_status_t lower_status;

      upper_status = svn_sqlite__column_token(stmt, 1, presence_map);

      if (svn_sqlite__column_is_null(stmt, 5))
        {
          /* No lower layer replaced. */
          if (upper_status != svn_wc__db_status_not_present)
            {
              different = TRUE;
              break;
            }
          continue;
        }

      lower_status = svn_sqlite__column_token(stmt, 5, presence_map);

      if (upper_status != lower_status)
        {
          different = TRUE;
          break;
        }

      if (upper_status == svn_wc__db_status_not_present
          || upper_status == svn_wc__db_status_excluded)
        {
          SVN_ERR(svn_sqlite__step(&have_row, stmt));
          continue; /* Nothing to check */
        }
      else if (upper_status != svn_wc__db_status_normal)
        {
          /* Not a normal move. Mixed revision move? */
          different = TRUE;
          break;
        }

      {
        const char *upper_repos_relpath;
        const char *lower_repos_relpath;

        upper_repos_relpath = svn_sqlite__column_text(stmt, 3, NULL);
        lower_repos_relpath = svn_sqlite__column_text(stmt, 7, NULL);

        if (! upper_repos_relpath
            || strcmp(upper_repos_relpath, lower_repos_relpath))
          {
            different = TRUE;
            break;
          }
      }

      {
        svn_revnum_t upper_rev;
        svn_revnum_t lower_rev;

        upper_rev = svn_sqlite__column_revnum(stmt, 4);
        lower_rev = svn_sqlite__column_revnum(stmt, 8);

        if (upper_rev != lower_rev)
          {
            different = TRUE;
            break;
          }
      }

      {
        apr_int64_t upper_repos_id;
        apr_int64_t lower_repos_id;

        upper_repos_id = svn_sqlite__column_int64(stmt, 2);
        lower_repos_id = svn_sqlite__column_int64(stmt, 6);

        if (upper_repos_id != lower_repos_id)
          {
            different = TRUE;
            break;
          }
      }

      /* Check moved_here? */

      SVN_ERR(svn_sqlite__step(&have_row, stmt));
    }
  SVN_ERR(svn_sqlite__reset(stmt));

  if (! different)
    {
      /* Ok, we can now safely remove this complete move, because we
         determined that it 100% matches the layer below it. */

      /* ### We could copy the recorded timestamps from the higher to the
             lower layer in an attempt to improve status performance, but
             generally these values should be the same anyway as it was
             a no-op move. */
      SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                        STMT_DELETE_WORKING_OP_DEPTH));

      SVN_ERR(svn_sqlite__bindf(stmt, "isd", wcroot->wc_id,
                                             local_relpath,
                                             relpath_depth(local_relpath)));

      SVN_ERR(svn_sqlite__step_done(stmt));

      if (moved_back)
        *moved_back = TRUE;
    }

  return SVN_NO_ERROR;
}