#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  node_kind; int /*<<< orphan*/  path_in_repos; int /*<<< orphan*/  peg_rev; } ;
typedef  TYPE_2__ svn_wc_conflict_version_t ;
typedef  int /*<<< orphan*/  svn_wc_conflict_reason_t ;
typedef  int /*<<< orphan*/  svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_9__ {int /*<<< orphan*/  local_relpath; TYPE_1__* b; } ;
typedef  TYPE_3__ added_node_baton_t ;
struct TYPE_7__ {int /*<<< orphan*/  new_version; int /*<<< orphan*/ * wcroot; int /*<<< orphan*/ * db; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  create_tree_conflict (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_node_none ; 
 int /*<<< orphan*/  svn_wc__db_base_get_info_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_conflict_action_add ; 
 TYPE_2__* svn_wc_conflict_version_dup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_state_inapplicable ; 
 int /*<<< orphan*/  svn_wc_notify_tree_conflict ; 
 int /*<<< orphan*/  svn_wc_operation_update ; 
 int /*<<< orphan*/  update_move_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
mark_update_add_add_tree_conflict(added_node_baton_t *nb,
                                  svn_node_kind_t base_kind,
                                  svn_node_kind_t working_kind,
                                  svn_wc_conflict_reason_t local_change,
                                  apr_pool_t *result_pool,
                                  apr_pool_t *scratch_pool)

{
  svn_wc__db_t *db = nb->b->db;
  svn_wc__db_wcroot_t *wcroot = nb->b->wcroot;
  svn_wc_conflict_version_t *new_version;
  svn_skel_t *conflict;

  new_version = svn_wc_conflict_version_dup(nb->b->new_version, result_pool);

  /* Fill in conflict info templates with info for this node. */
  SVN_ERR(svn_wc__db_base_get_info_internal(NULL, NULL, &new_version->peg_rev,
                                            &new_version->path_in_repos,
                                            NULL, NULL, NULL, NULL, NULL, NULL,
                                            NULL, NULL, NULL, NULL, NULL,
                                            wcroot, nb->local_relpath,
                                            scratch_pool, scratch_pool));
  new_version->node_kind = base_kind;

  SVN_ERR(create_tree_conflict(&conflict, wcroot, nb->local_relpath,
                               nb->local_relpath, db, NULL, new_version,
                               svn_wc_operation_update,
                               svn_node_none, base_kind, NULL,
                               local_change, svn_wc_conflict_action_add,
                               NULL, scratch_pool, scratch_pool));

  SVN_ERR(update_move_list_add(wcroot, nb->local_relpath, db,
                               svn_wc_notify_tree_conflict, working_kind,
                               svn_wc_notify_state_inapplicable,
                               svn_wc_notify_state_inapplicable,
                               conflict, NULL, scratch_pool));
  return SVN_NO_ERROR;
}