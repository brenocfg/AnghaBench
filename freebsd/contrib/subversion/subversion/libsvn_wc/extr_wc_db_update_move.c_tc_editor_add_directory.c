#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  db; TYPE_3__* wcroot; } ;
typedef  TYPE_1__ update_move_baton_t ;
typedef  int /*<<< orphan*/  svn_wc_conflict_reason_t ;
typedef  scalar_t__ svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_9__ {scalar_t__ skip; scalar_t__ shadowed; TYPE_1__* umb; } ;
typedef  TYPE_2__ node_move_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_10__ {int /*<<< orphan*/  abspath; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  create_node_tree_conflict (int /*<<< orphan*/ **,TYPE_2__*,char const*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mark_parent_edited (TYPE_2__*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_check_path (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_node_dir ; 
 scalar_t__ svn_node_none ; 
 int /*<<< orphan*/  svn_wc__db_read_info_internal (scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__db_status_added ; 
 scalar_t__ svn_wc__db_status_deleted ; 
 int /*<<< orphan*/  svn_wc__wq_build_dir_install (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_conflict_action_add ; 
 int /*<<< orphan*/  svn_wc_conflict_action_replace ; 
 int /*<<< orphan*/  svn_wc_conflict_reason_added ; 
 int /*<<< orphan*/  svn_wc_conflict_reason_deleted ; 
 int /*<<< orphan*/  svn_wc_conflict_reason_replaced ; 
 int /*<<< orphan*/  svn_wc_conflict_reason_unversioned ; 
 int /*<<< orphan*/  svn_wc_notify_state_inapplicable ; 
 int /*<<< orphan*/  svn_wc_notify_update_add ; 
 int /*<<< orphan*/  svn_wc_notify_update_replace ; 
 int /*<<< orphan*/  update_move_list_add (TYPE_3__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
tc_editor_add_directory(node_move_baton_t *nmb,
                        const char *relpath,
                        svn_node_kind_t old_kind,
                        apr_hash_t *props,
                        apr_pool_t *scratch_pool)
{
  update_move_baton_t *b = nmb->umb;
  const char *local_abspath;
  svn_node_kind_t wc_kind;
  svn_skel_t *work_item = NULL;
  svn_skel_t *conflict = NULL;
  svn_wc_conflict_reason_t reason = svn_wc_conflict_reason_unversioned;

  SVN_ERR(mark_parent_edited(nmb, scratch_pool));
  if (nmb->skip)
    return SVN_NO_ERROR;

  if (nmb->shadowed)
    {
      svn_wc__db_status_t status;

      SVN_ERR(svn_wc__db_read_info_internal(&status, &wc_kind, NULL, NULL,
                                            NULL, NULL, NULL, NULL, NULL, NULL,
                                            NULL, NULL, NULL, NULL, NULL, NULL,
                                            NULL, NULL, NULL, NULL, NULL, NULL,
                                            NULL, NULL, NULL,
                                            b->wcroot, relpath,
                                            scratch_pool, scratch_pool));

      if (status == svn_wc__db_status_deleted)
        reason = svn_wc_conflict_reason_deleted;
      else if (status != svn_wc__db_status_added)
        wc_kind = svn_node_none;
      else if (old_kind == svn_node_none)
        reason = svn_wc_conflict_reason_added;
      else
        reason = svn_wc_conflict_reason_replaced;
    }
  else
    wc_kind = svn_node_none;

  local_abspath = svn_dirent_join(b->wcroot->abspath, relpath, scratch_pool);

  if (wc_kind == svn_node_none)
    {
      /* Check for unversioned tree-conflict */
      SVN_ERR(svn_io_check_path(local_abspath, &wc_kind, scratch_pool));
    }

  if (!nmb->shadowed && wc_kind == old_kind)
    wc_kind = svn_node_none; /* Node will be gone once we install */

  if (wc_kind != svn_node_none
      && (nmb->shadowed || wc_kind != old_kind)) /* replace */
    {
      SVN_ERR(create_node_tree_conflict(&conflict, nmb, relpath,
                                        old_kind, svn_node_dir,
                                        reason,
                                        (old_kind == svn_node_none)
                                          ? svn_wc_conflict_action_add
                                          : svn_wc_conflict_action_replace,
                                        NULL,
                                        scratch_pool, scratch_pool));
      nmb->skip = TRUE;
    }
  else
    {
      SVN_ERR(svn_wc__wq_build_dir_install(&work_item, b->db, local_abspath,
                                           scratch_pool, scratch_pool));
    }

  SVN_ERR(update_move_list_add(b->wcroot, relpath, b->db,
                               (old_kind == svn_node_none)
                                  ? svn_wc_notify_update_add
                                  : svn_wc_notify_update_replace,
                               svn_node_dir,
                               svn_wc_notify_state_inapplicable,
                               svn_wc_notify_state_inapplicable,
                               conflict, work_item, scratch_pool));
  return SVN_NO_ERROR;
}