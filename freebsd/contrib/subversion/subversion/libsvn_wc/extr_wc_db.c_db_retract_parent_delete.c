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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_CLEAR_MOVED_HERE_RECURSIVE ; 
 int /*<<< orphan*/  STMT_CLEAR_MOVED_TO_RELPATH ; 
 int /*<<< orphan*/  STMT_DELETE_NODE ; 
 int /*<<< orphan*/  STMT_SELECT_LOWEST_WORKING_NODE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  presence_map ; 
 int relpath_depth (char const*) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*,int) ; 
 int svn_sqlite__column_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* svn_sqlite__column_text (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_sqlite__column_token (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__update (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__db_status_base_deleted ; 

__attribute__((used)) static svn_error_t *
db_retract_parent_delete(svn_wc__db_wcroot_t *wcroot,
                         const char *local_relpath,
                         int op_depth,
                         apr_pool_t *scratch_pool)
{
  svn_sqlite__stmt_t *stmt;
  svn_boolean_t have_row;
  int working_depth;
  svn_wc__db_status_t presence;
  const char *moved_to;

  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_SELECT_LOWEST_WORKING_NODE));
  SVN_ERR(svn_sqlite__bindf(stmt, "isd", wcroot->wc_id, local_relpath,
                            op_depth));
  SVN_ERR(svn_sqlite__step(&have_row, stmt));

  if (!have_row)
    return svn_error_trace(svn_sqlite__reset(stmt));

  working_depth = svn_sqlite__column_int(stmt, 0);
  presence = svn_sqlite__column_token(stmt, 1, presence_map);
  moved_to = svn_sqlite__column_text(stmt, 3, scratch_pool);

  SVN_ERR(svn_sqlite__reset(stmt));

  if (moved_to)
    {
      /* Turn the move into a copy to keep the NODES table valid */
      SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                        STMT_CLEAR_MOVED_HERE_RECURSIVE));
      SVN_ERR(svn_sqlite__bindf(stmt, "isd", wcroot->wc_id,
                                moved_to, relpath_depth(moved_to)));
      SVN_ERR(svn_sqlite__step_done(stmt));

      /* This leaves just the moved_to information on the origin,
         which we will remove in the next step */
    }

  if (presence == svn_wc__db_status_base_deleted)
    {
      /* Nothing left to shadow; remove the base-deleted node */
      SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb, STMT_DELETE_NODE));
    }
  else if (moved_to)
    {
      /* Clear moved to information, as this node is no longer base-deleted */
      SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                        STMT_CLEAR_MOVED_TO_RELPATH));
      }
  else
    {
      /* Nothing to update */
      return SVN_NO_ERROR;
    }

  SVN_ERR(svn_sqlite__bindf(stmt, "isd", wcroot->wc_id, local_relpath,
                            working_depth));

  return svn_error_trace(svn_sqlite__update(NULL, stmt));
}