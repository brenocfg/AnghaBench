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
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_9__ {scalar_t__ skip; TYPE_1__* umb; } ;
typedef  TYPE_2__ node_move_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_10__ {int /*<<< orphan*/  abspath; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  copy_working_node (char const*,char const*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_node_tree_conflict (int /*<<< orphan*/ **,TYPE_2__*,char const*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mark_parent_edited (TYPE_2__*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_check_path (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_node_dir ; 
 scalar_t__ svn_node_none ; 
 int /*<<< orphan*/  svn_wc__wq_build_dir_install (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_conflict_action_add ; 
 int /*<<< orphan*/  svn_wc_conflict_action_replace ; 
 int /*<<< orphan*/  svn_wc_conflict_reason_unversioned ; 
 int /*<<< orphan*/  svn_wc_notify_state_inapplicable ; 
 int /*<<< orphan*/  svn_wc_notify_update_add ; 
 int /*<<< orphan*/  svn_wc_notify_update_replace ; 
 int /*<<< orphan*/  update_move_list_add (TYPE_3__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
tc_editor_incoming_add_directory(node_move_baton_t *nmb,
                                 const char *dst_relpath,
                                 svn_node_kind_t old_kind,
                                 apr_hash_t *props,
                                 const char *src_relpath,
                                 apr_pool_t *scratch_pool)
{
  update_move_baton_t *b = nmb->umb;
  const char *dst_abspath;
  svn_node_kind_t wc_kind;
  svn_skel_t *work_item = NULL;
  svn_skel_t *conflict = NULL;
  svn_wc_conflict_reason_t reason = svn_wc_conflict_reason_unversioned;

  SVN_ERR(mark_parent_edited(nmb, scratch_pool));
  if (nmb->skip)
    return SVN_NO_ERROR;

  dst_abspath = svn_dirent_join(b->wcroot->abspath, dst_relpath, scratch_pool);

  /* Check for unversioned tree-conflict */
  SVN_ERR(svn_io_check_path(dst_abspath, &wc_kind, scratch_pool));

  if (wc_kind == old_kind)
    wc_kind = svn_node_none; /* Node will be gone once we install */

  if (wc_kind != svn_node_none && wc_kind != old_kind) /* replace */
    {
      SVN_ERR(create_node_tree_conflict(&conflict, nmb, dst_relpath,
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
      SVN_ERR(copy_working_node(src_relpath, dst_relpath, b->wcroot,
                                scratch_pool));
      SVN_ERR(svn_wc__wq_build_dir_install(&work_item, b->db, dst_abspath,
                                           scratch_pool, scratch_pool));
    }

  SVN_ERR(update_move_list_add(b->wcroot, dst_relpath, b->db,
                               (old_kind == svn_node_none)
                                  ? svn_wc_notify_update_add
                                  : svn_wc_notify_update_replace,
                               svn_node_dir,
                               svn_wc_notify_state_inapplicable,
                               svn_wc_notify_state_inapplicable,
                               conflict, work_item, scratch_pool));
  return SVN_NO_ERROR;
}