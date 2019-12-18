#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_operation_t ;
struct TYPE_9__ {int /*<<< orphan*/  node_kind; } ;
typedef  TYPE_1__ svn_wc_conflict_version_t ;
typedef  scalar_t__ svn_wc_conflict_reason_t ;
struct TYPE_10__ {scalar_t__ action; scalar_t__ reason; } ;
typedef  TYPE_2__ svn_wc_conflict_description2_t ;
typedef  scalar_t__ svn_wc_conflict_action_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_io_check_path (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_node_none ; 
 int /*<<< orphan*/  svn_wc__conflict_read_tree_conflict (scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc_conflict_action_delete ; 
 TYPE_2__* svn_wc_conflict_description_create_tree2 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__ const*,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc_conflict_reason_deleted ; 
 scalar_t__ svn_wc_conflict_reason_missing ; 
 scalar_t__ svn_wc_conflict_reason_moved_away ; 
 scalar_t__ svn_wc_conflict_reason_obstructed ; 
 scalar_t__ svn_wc_conflict_reason_unversioned ; 
 int /*<<< orphan*/  svn_wc_operation_switch ; 
 int /*<<< orphan*/  svn_wc_operation_update ; 

__attribute__((used)) static svn_error_t *
read_tree_conflict_desc(svn_wc_conflict_description2_t **desc,
                        svn_wc__db_t *db,
                        const char *local_abspath,
                        svn_node_kind_t node_kind,
                        const svn_skel_t *conflict_skel,
                        svn_wc_operation_t operation,
                        const svn_wc_conflict_version_t *left_version,
                        const svn_wc_conflict_version_t *right_version,
                        apr_pool_t *result_pool,
                        apr_pool_t *scratch_pool)
{
  svn_node_kind_t local_kind;
  svn_wc_conflict_reason_t reason;
  svn_wc_conflict_action_t action;

  SVN_ERR(svn_wc__conflict_read_tree_conflict(
            &reason, &action, NULL,
            db, local_abspath, conflict_skel, scratch_pool, scratch_pool));

  if (reason == svn_wc_conflict_reason_missing)
    local_kind = svn_node_none;
  else if (reason == svn_wc_conflict_reason_unversioned ||
           reason == svn_wc_conflict_reason_obstructed)
    SVN_ERR(svn_io_check_path(local_abspath, &local_kind, scratch_pool));
  else if (action == svn_wc_conflict_action_delete
           && left_version
           && (operation == svn_wc_operation_update
               ||operation == svn_wc_operation_switch)
           && (reason == svn_wc_conflict_reason_deleted
               || reason == svn_wc_conflict_reason_moved_away))
    {
      /* We have nothing locally to take the kind from */
      local_kind = left_version->node_kind;
    }
  else
    local_kind = node_kind;

  *desc = svn_wc_conflict_description_create_tree2(local_abspath, local_kind,
                                                   operation,
                                                   left_version, right_version,
                                                   result_pool);
  (*desc)->reason = reason;
  (*desc)->action = action;

  return SVN_NO_ERROR;
}