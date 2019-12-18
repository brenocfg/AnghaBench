#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_operation_t ;
typedef  int /*<<< orphan*/  svn_wc_notify_func2_t ;
struct TYPE_6__ {int /*<<< orphan*/  peg_rev; } ;
typedef  TYPE_1__ svn_wc_conflict_version_t ;
typedef  int /*<<< orphan*/  svn_wc_conflict_action_t ;
typedef  int /*<<< orphan*/  svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_WC__DB_WITH_TXN4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VERIFY_USABLE_WCROOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fetch_conflict_details (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__**,TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_op_mark_resolved_internal (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_op_raise_moved_away_internal (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_conflict_internal (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_update_move_list_notify (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_wcroot_parse_local_abspath (int /*<<< orphan*/ **,char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__db_op_raise_moved_away(svn_wc__db_t *db,
                               const char *local_abspath,
                               svn_wc_notify_func2_t notify_func,
                               void *notify_baton,
                               apr_pool_t *scratch_pool)
{
  svn_wc__db_wcroot_t *wcroot;
  const char *local_relpath;
  svn_wc_operation_t operation;
  svn_wc_conflict_action_t action;
  svn_wc_conflict_version_t *left_version, *right_version;
  int move_src_op_depth;
  svn_skel_t *conflict;

  SVN_ERR(svn_wc__db_wcroot_parse_local_abspath(&wcroot, &local_relpath,
                                                db, local_abspath,
                                                scratch_pool, scratch_pool));
  VERIFY_USABLE_WCROOT(wcroot);

  SVN_WC__DB_WITH_TXN4(
    svn_wc__db_read_conflict_internal(&conflict, NULL, NULL,
                                      wcroot, local_relpath,
                                      scratch_pool, scratch_pool),
    fetch_conflict_details(&move_src_op_depth,
                           &operation, &action,
                           &left_version, &right_version,
                           wcroot, db, local_relpath, conflict,
                           scratch_pool, scratch_pool),
    svn_wc__db_op_mark_resolved_internal(wcroot, local_relpath, db,
                                         FALSE, FALSE, TRUE,
                                         NULL, scratch_pool),
    svn_wc__db_op_raise_moved_away_internal(wcroot, local_relpath,
                                            move_src_op_depth,
                                            db, operation, action,
                                            left_version, right_version,
                                            scratch_pool),
    wcroot);

  /* These version numbers are valid for update/switch notifications 
     only! */
  SVN_ERR(svn_wc__db_update_move_list_notify(wcroot,
                                             (left_version
                                              ? left_version->peg_rev
                                              : SVN_INVALID_REVNUM),
                                             (right_version
                                              ? right_version->peg_rev
                                              : SVN_INVALID_REVNUM),
                                             notify_func, notify_baton,
                                             scratch_pool));

  return SVN_NO_ERROR;
}