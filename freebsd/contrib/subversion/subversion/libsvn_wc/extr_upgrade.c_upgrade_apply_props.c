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
typedef  scalar_t__ svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_sqlite__db_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_3__ {scalar_t__ nelts; } ;
typedef  TYPE_1__ apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_INSERT_ACTUAL_PROPS ; 
 int /*<<< orphan*/  STMT_SELECT_NODE_INFO ; 
 int /*<<< orphan*/  STMT_UPDATE_ACTUAL_PROPS ; 
 int /*<<< orphan*/  STMT_UPDATE_NODE_PROPS ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_WC_CORRUPT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int SVN_WC__NO_REVERT_FILES ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  presence_map ; 
 int /*<<< orphan*/  svn_dirent_join (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_prop_diffs (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_relpath_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__bind_properties (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__bind_text (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*,...) ; 
 int svn_sqlite__column_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_sqlite__column_token (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__update (int*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__db_status_deleted ; 
 scalar_t__ svn_wc__db_status_normal ; 
 scalar_t__ svn_wc__db_status_not_present ; 

__attribute__((used)) static svn_error_t *
upgrade_apply_props(svn_sqlite__db_t *sdb,
                    const char *dir_abspath,
                    const char *local_relpath,
                    apr_hash_t *base_props,
                    apr_hash_t *revert_props,
                    apr_hash_t *working_props,
                    int original_format,
                    apr_int64_t wc_id,
                    apr_pool_t *scratch_pool)
{
  svn_sqlite__stmt_t *stmt;
  svn_boolean_t have_row;
  int top_op_depth = -1;
  int below_op_depth = -1;
  svn_wc__db_status_t top_presence;
  svn_wc__db_status_t below_presence;
  int affected_rows;

  /* ### working_props: use set_props_txn.
     ### if working_props == NULL, then skip. what if they equal the
     ### pristine props? we should probably do the compare here.
     ###
     ### base props go into WORKING_NODE if avail, otherwise BASE.
     ###
     ### revert only goes into BASE. (and WORKING better be there!)

     Prior to 1.4.0 (ORIGINAL_FORMAT < 8), REVERT_PROPS did not exist. If a
     file was deleted, then a copy (potentially with props) was disallowed
     and could not replace the deletion. An addition *could* be performed,
     but that would never bring its own props.

     1.4.0 through 1.4.5 created the concept of REVERT_PROPS, but had a
     bug in svn_wc_add_repos_file2() whereby a copy-with-props did NOT
     construct a REVERT_PROPS if the target had no props. Thus, reverting
     the delete/copy would see no REVERT_PROPS to restore, leaving the
     props from the copy source intact, and appearing as if they are (now)
     the base props for the previously-deleted file. (wc corruption)

     1.4.6 ensured that an empty REVERT_PROPS would be established at all
     times. See issue 2530, and r861670 as starting points.

     We will use ORIGINAL_FORMAT and SVN_WC__NO_REVERT_FILES to determine
     the handling of our inputs, relative to the state of this node.
  */

  SVN_ERR(svn_sqlite__get_statement(&stmt, sdb, STMT_SELECT_NODE_INFO));
  SVN_ERR(svn_sqlite__bindf(stmt, "is", wc_id, local_relpath));
  SVN_ERR(svn_sqlite__step(&have_row, stmt));
  if (have_row)
    {
      top_op_depth = svn_sqlite__column_int(stmt, 0);
      top_presence = svn_sqlite__column_token(stmt, 3, presence_map);
      SVN_ERR(svn_sqlite__step(&have_row, stmt));
      if (have_row)
        {
          below_presence = svn_sqlite__column_token(stmt, 3, presence_map);

          /* There might be an intermediate layer on mixed-revision copies,
             or when BASE is shadowed */
          if (below_presence == svn_wc__db_status_not_present
              || below_presence == svn_wc__db_status_deleted)
            SVN_ERR(svn_sqlite__step(&have_row, stmt));

          if (have_row)
            {
              below_presence = svn_sqlite__column_token(stmt, 3, presence_map);
              below_op_depth = svn_sqlite__column_int(stmt, 0);
            }
        }
    }
  SVN_ERR(svn_sqlite__reset(stmt));

  /* Detect the buggy scenario described above. We cannot upgrade this
     working copy if we have no idea where BASE_PROPS should go.  */
  if (original_format > SVN_WC__NO_REVERT_FILES
      && revert_props == NULL
      && top_op_depth != -1
      && top_presence == svn_wc__db_status_normal
      && below_op_depth != -1
      && below_presence != svn_wc__db_status_not_present)
    {
      /* There should be REVERT_PROPS, so it appears that we just ran into
         the described bug. Sigh.  */
      return svn_error_createf(SVN_ERR_WC_CORRUPT, NULL,
                               _("The properties of '%s' are in an "
                                 "indeterminate state and cannot be "
                                 "upgraded. See issue #2530."),
                               svn_dirent_local_style(
                                 svn_dirent_join(dir_abspath, local_relpath,
                                                 scratch_pool), scratch_pool));
    }

  /* Need at least one row, or two rows if there are revert props */
  if (top_op_depth == -1
      || (below_op_depth == -1 && revert_props))
    return svn_error_createf(SVN_ERR_WC_CORRUPT, NULL,
                             _("Insufficient NODES rows for '%s'"),
                             svn_dirent_local_style(
                               svn_dirent_join(dir_abspath, local_relpath,
                                               scratch_pool), scratch_pool));

  /* one row, base props only: upper row gets base props
     two rows, base props only: lower row gets base props
     two rows, revert props only: lower row gets revert props
     two rows, base and revert props: upper row gets base, lower gets revert */


  if (revert_props || below_op_depth == -1)
    {
      SVN_ERR(svn_sqlite__get_statement(&stmt, sdb,
                                        STMT_UPDATE_NODE_PROPS));
      SVN_ERR(svn_sqlite__bindf(stmt, "isd",
                                wc_id, local_relpath, top_op_depth));
      SVN_ERR(svn_sqlite__bind_properties(stmt, 4, base_props, scratch_pool));
      SVN_ERR(svn_sqlite__update(&affected_rows, stmt));

      SVN_ERR_ASSERT(affected_rows == 1);
    }

  if (below_op_depth != -1)
    {
      apr_hash_t *props = revert_props ? revert_props : base_props;

      SVN_ERR(svn_sqlite__get_statement(&stmt, sdb,
                                        STMT_UPDATE_NODE_PROPS));
      SVN_ERR(svn_sqlite__bindf(stmt, "isd",
                                wc_id, local_relpath, below_op_depth));
      SVN_ERR(svn_sqlite__bind_properties(stmt, 4, props, scratch_pool));
      SVN_ERR(svn_sqlite__update(&affected_rows, stmt));

      SVN_ERR_ASSERT(affected_rows == 1);
    }

  /* If there are WORKING_PROPS, then they always go into ACTUAL_NODE.  */
  if (working_props != NULL
      && base_props != NULL)
    {
      apr_array_header_t *diffs;

      SVN_ERR(svn_prop_diffs(&diffs, working_props, base_props, scratch_pool));

      if (diffs->nelts == 0)
        working_props = NULL; /* No differences */
    }

  if (working_props != NULL)
    {
      SVN_ERR(svn_sqlite__get_statement(&stmt, sdb,
                                  STMT_UPDATE_ACTUAL_PROPS));
      SVN_ERR(svn_sqlite__bindf(stmt, "is", wc_id, local_relpath));
      SVN_ERR(svn_sqlite__bind_properties(stmt, 3, working_props,
                                          scratch_pool));
      SVN_ERR(svn_sqlite__update(&affected_rows, stmt));

      if (affected_rows == 0)
        {
          /* We have to insert a row in ACTUAL */

          SVN_ERR(svn_sqlite__get_statement(&stmt, sdb,
                                            STMT_INSERT_ACTUAL_PROPS));
          SVN_ERR(svn_sqlite__bindf(stmt, "is", wc_id, local_relpath));
          if (*local_relpath != '\0')
            SVN_ERR(svn_sqlite__bind_text(stmt, 3,
                                          svn_relpath_dirname(local_relpath,
                                                              scratch_pool)));
          SVN_ERR(svn_sqlite__bind_properties(stmt, 4, working_props,
                                              scratch_pool));
          return svn_error_trace(svn_sqlite__step_done(stmt));
        }
    }

  return SVN_NO_ERROR;
}