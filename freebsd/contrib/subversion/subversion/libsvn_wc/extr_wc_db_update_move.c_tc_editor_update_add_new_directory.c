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
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_9__ {TYPE_1__* b; int /*<<< orphan*/  local_relpath; void* skip; } ;
typedef  TYPE_2__ added_node_baton_t ;
struct TYPE_10__ {int /*<<< orphan*/  abspath; } ;
struct TYPE_8__ {int /*<<< orphan*/  db; TYPE_3__* wcroot; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 void* TRUE ; 
 int /*<<< orphan*/  mark_update_add_add_tree_conflict (TYPE_2__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_check_path (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_none ; 
 int /*<<< orphan*/  svn_wc_conflict_reason_added ; 
 int /*<<< orphan*/  svn_wc_notify_state_inapplicable ; 
 int /*<<< orphan*/  svn_wc_notify_update_add ; 
 int /*<<< orphan*/  update_local_add_mark_parent_edited (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_local_add_notify_obstructed_or_missing (TYPE_2__*,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_move_list_add (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
tc_editor_update_add_new_directory(added_node_baton_t *nb,
                                   svn_node_kind_t base_kind,
                                   apr_hash_t *base_props,
                                   apr_hash_t *working_props,
                                   apr_pool_t *scratch_pool)
{
  const char *local_abspath;
  svn_node_kind_t kind_on_disk;

  SVN_ERR(update_local_add_mark_parent_edited(nb, scratch_pool));
  if (nb->skip)
    return SVN_NO_ERROR;

  if (base_kind != svn_node_none)
    {
      SVN_ERR(mark_update_add_add_tree_conflict(nb, base_kind, svn_node_dir,
                                                svn_wc_conflict_reason_added,
                                                scratch_pool, scratch_pool));
      nb->skip = TRUE;
      return SVN_NO_ERROR;
    }

  /* Check for obstructions. */
  local_abspath = svn_dirent_join(nb->b->wcroot->abspath, nb->local_relpath,
                                  scratch_pool);
  SVN_ERR(svn_io_check_path(local_abspath, &kind_on_disk, scratch_pool));
  if (kind_on_disk != svn_node_dir)
    {
      SVN_ERR(update_local_add_notify_obstructed_or_missing(nb, svn_node_dir,
                                                            kind_on_disk,
                                                            scratch_pool));
      nb->skip = TRUE;
      return SVN_NO_ERROR;
    }

  /* Nothing else to do. Locally added directories are an op-root in NODES. */

  SVN_ERR(update_move_list_add(nb->b->wcroot, nb->local_relpath, nb->b->db,
                               svn_wc_notify_update_add, svn_node_dir,
                               svn_wc_notify_state_inapplicable,
                               svn_wc_notify_state_inapplicable,
                               NULL, NULL, scratch_pool));
  return SVN_NO_ERROR;
}