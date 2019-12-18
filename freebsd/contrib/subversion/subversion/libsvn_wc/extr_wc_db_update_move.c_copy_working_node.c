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
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_INSERT_ACTUAL_NODE ; 
 int /*<<< orphan*/  STMT_INSERT_WORKING_NODE_COPY_FROM ; 
 int /*<<< orphan*/  STMT_SELECT_ACTUAL_NODE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  presence_map ; 
 int /*<<< orphan*/  relpath_depth (char const*) ; 
 char* svn_relpath_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*,...) ; 
 char* svn_sqlite__column_blob (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_status_normal ; 

__attribute__((used)) static svn_error_t *
copy_working_node(const char *src_relpath,
                  const char *dst_relpath,
                  svn_wc__db_wcroot_t *wcroot,
                  apr_pool_t *scratch_pool)
{
  svn_sqlite__stmt_t *stmt;
  svn_boolean_t have_row;
  const char *dst_parent_relpath = svn_relpath_dirname(dst_relpath,
                                                       scratch_pool);

  /* Add a WORKING row for the new node, based on the source. */
  SVN_ERR(svn_sqlite__get_statement(&stmt,wcroot->sdb,
                                    STMT_INSERT_WORKING_NODE_COPY_FROM));
  SVN_ERR(svn_sqlite__bindf(stmt, "issdst", wcroot->wc_id, src_relpath,
                            dst_relpath, relpath_depth(dst_relpath),
                            dst_parent_relpath, presence_map,
                            svn_wc__db_status_normal));
  SVN_ERR(svn_sqlite__step_done(stmt));

  /* Copy properties over.  ### This loses changelist association. */
  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_SELECT_ACTUAL_NODE));
  SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, src_relpath));
  SVN_ERR(svn_sqlite__step(&have_row, stmt));
  if (have_row)
    {
      apr_size_t props_size;
      const char *properties;

      properties = svn_sqlite__column_blob(stmt, 1, &props_size,
                                           scratch_pool);
      SVN_ERR(svn_sqlite__reset(stmt));
      SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                        STMT_INSERT_ACTUAL_NODE));
      SVN_ERR(svn_sqlite__bindf(stmt, "issbs",
                                wcroot->wc_id, dst_relpath,
                                svn_relpath_dirname(dst_relpath,
                                                    scratch_pool),
                                properties, props_size, NULL));
      SVN_ERR(svn_sqlite__step(&have_row, stmt));
    }
  SVN_ERR(svn_sqlite__reset(stmt));

  return SVN_NO_ERROR;
}