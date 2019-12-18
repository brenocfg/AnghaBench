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
struct TYPE_3__ {int /*<<< orphan*/  sdb; int /*<<< orphan*/  abspath; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  STMT_DELETE_REVERT_LIST ; 
 int /*<<< orphan*/  STMT_SELECT_REVERT_LIST ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int TRUE ; 
 int /*<<< orphan*/  kind_map ; 
 int relpath_depth (char const*) ; 
 int /*<<< orphan*/  svn_node_unknown ; 
 int /*<<< orphan*/ * svn_skel__parse (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,char const*) ; 
 void* svn_sqlite__column_blob (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int svn_sqlite__column_boolean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int svn_sqlite__column_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_sqlite__column_is_null (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_sqlite__column_token (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__conflict_read_markers (int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
revert_list_read(svn_boolean_t *reverted,
                 const apr_array_header_t **marker_paths,
                 svn_boolean_t *copied_here,
                 svn_node_kind_t *kind,
                 svn_wc__db_wcroot_t *wcroot,
                 const char *local_relpath,
                 svn_wc__db_t *db,
                 apr_pool_t *result_pool,
                 apr_pool_t *scratch_pool)
{
  svn_sqlite__stmt_t *stmt;
  svn_boolean_t have_row;

  *reverted = FALSE;
  *marker_paths = NULL;
  *copied_here = FALSE;
  *kind = svn_node_unknown;

  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_SELECT_REVERT_LIST));
  SVN_ERR(svn_sqlite__bindf(stmt, "s", local_relpath));
  SVN_ERR(svn_sqlite__step(&have_row, stmt));
  if (have_row)
    {
      svn_boolean_t is_actual = svn_sqlite__column_boolean(stmt, 0);
      svn_boolean_t another_row = FALSE;

      if (is_actual)
        {
          apr_size_t conflict_len;
          const void *conflict_data;

          conflict_data = svn_sqlite__column_blob(stmt, 5, &conflict_len,
                                                  scratch_pool);
          if (conflict_data)
            {
              svn_skel_t *conflicts = svn_skel__parse(conflict_data,
                                                      conflict_len,
                                                      scratch_pool);

              SVN_ERR(svn_wc__conflict_read_markers(marker_paths,
                                                    db, wcroot->abspath,
                                                    conflicts,
                                                    result_pool,
                                                    scratch_pool));
            }

          if (!svn_sqlite__column_is_null(stmt, 1)) /* notify */
            *reverted = TRUE;

          SVN_ERR(svn_sqlite__step(&another_row, stmt));
        }

      if (!is_actual || another_row)
        {
          *reverted = TRUE;
          if (!svn_sqlite__column_is_null(stmt, 4)) /* repos_id */
            {
              int op_depth = svn_sqlite__column_int(stmt, 3);
              *copied_here = (op_depth == relpath_depth(local_relpath));
            }
          *kind = svn_sqlite__column_token(stmt, 2, kind_map);
        }

    }
  SVN_ERR(svn_sqlite__reset(stmt));

  if (have_row)
    {
      SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                        STMT_DELETE_REVERT_LIST));
      SVN_ERR(svn_sqlite__bindf(stmt, "s", local_relpath));
      SVN_ERR(svn_sqlite__step_done(stmt));
    }

  return SVN_NO_ERROR;
}