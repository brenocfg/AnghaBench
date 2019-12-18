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
typedef  int /*<<< orphan*/  svn_wc_notify_state_t ;
typedef  int /*<<< orphan*/  svn_wc_notify_action_t ;
struct TYPE_5__ {int /*<<< orphan*/  sdb; int /*<<< orphan*/  abspath; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_INSERT_UPDATE_MOVE_LIST ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  kind_map_none ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__step_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__conflict_read_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_mark_conflict_internal (TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_wq_add_internal (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_state_inapplicable ; 
 int /*<<< orphan*/  svn_wc_notify_tree_conflict ; 

__attribute__((used)) static svn_error_t *
update_move_list_add(svn_wc__db_wcroot_t *wcroot,
                     const char *local_relpath,
                     svn_wc__db_t *db,
                     svn_wc_notify_action_t action,
                     svn_node_kind_t kind,
                     svn_wc_notify_state_t content_state,
                     svn_wc_notify_state_t prop_state,
                     svn_skel_t *conflict,
                     svn_skel_t *work_item,
                     apr_pool_t *scratch_pool)
{
  svn_sqlite__stmt_t *stmt;

  if (conflict)
    {
      svn_boolean_t tree_conflict;

      SVN_ERR(svn_wc__conflict_read_info(NULL, NULL, NULL, NULL,
                                         &tree_conflict,
                                         db, wcroot->abspath, conflict,
                                         scratch_pool, scratch_pool));
      if (tree_conflict)
        {
          action = svn_wc_notify_tree_conflict;
          content_state = svn_wc_notify_state_inapplicable;
          prop_state = svn_wc_notify_state_inapplicable;
        }
    }

  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_INSERT_UPDATE_MOVE_LIST));
  SVN_ERR(svn_sqlite__bindf(stmt, "sdtdd", local_relpath,
                            action, kind_map_none, kind,
                            content_state, prop_state));
  SVN_ERR(svn_sqlite__step_done(stmt));

  if (conflict)
    SVN_ERR(svn_wc__db_mark_conflict_internal(wcroot, local_relpath, conflict,
                                              scratch_pool));

  if (work_item)
    SVN_ERR(svn_wc__db_wq_add_internal(wcroot, work_item, scratch_pool));

  return SVN_NO_ERROR;
}