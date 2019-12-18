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
struct TYPE_5__ {int /*<<< orphan*/  sdb; int /*<<< orphan*/  wc_id; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_CLEAR_MOVED_TO_RELPATH ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_WC_PATH_UNEXPECTED_STATUS ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_work_items (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_moved_here (TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  path_for_error_message (TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__update (int*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__db_op_break_move_internal(svn_wc__db_wcroot_t *wcroot,
                                  const char *src_relpath,
                                  int delete_op_depth,
                                  const char *dst_relpath,
                                  const svn_skel_t *work_items,
                                  apr_pool_t *scratch_pool)
{
  svn_sqlite__stmt_t *stmt;
  int affected;

  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_CLEAR_MOVED_TO_RELPATH));
  SVN_ERR(svn_sqlite__bindf(stmt, "isd", wcroot->wc_id, src_relpath,
                            delete_op_depth));
  SVN_ERR(svn_sqlite__update(&affected, stmt));

  if (affected != 1)
    return svn_error_createf(SVN_ERR_WC_PATH_UNEXPECTED_STATUS, NULL,
                             _("Path '%s' is not moved"),
                             path_for_error_message(wcroot, src_relpath,
                                                    scratch_pool));

  SVN_ERR(clear_moved_here(wcroot, dst_relpath, scratch_pool));

  SVN_ERR(add_work_items(wcroot->sdb, work_items, scratch_pool));
  return SVN_NO_ERROR;
}