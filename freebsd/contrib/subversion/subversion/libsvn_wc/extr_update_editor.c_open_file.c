#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ svn_wc_conflict_reason_t ;
typedef  int /*<<< orphan*/  svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct file_baton {void* shadowed; void* edit_obstructed; int /*<<< orphan*/  local_abspath; int /*<<< orphan*/ * edit_conflict; int /*<<< orphan*/  pool; void* already_notified; void* skip_this; int /*<<< orphan*/  old_repos_relpath; int /*<<< orphan*/  new_repos_relpath; int /*<<< orphan*/  original_checksum; int /*<<< orphan*/  changed_author; int /*<<< orphan*/  changed_date; int /*<<< orphan*/  changed_rev; int /*<<< orphan*/  old_revision; int /*<<< orphan*/  local_prop_mods; } ;
struct edit_baton {int /*<<< orphan*/  db; } ;
struct dir_baton {struct edit_baton* edit_baton; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 void* TRUE ; 
 int /*<<< orphan*/  calculate_repos_relpath (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct edit_baton*,struct dir_baton*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_tree_conflict (int /*<<< orphan*/ **,struct edit_baton*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_notification (struct edit_baton*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_file_baton (struct file_baton**,struct dir_baton*,char const*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  node_already_conflicted (scalar_t__*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remember_skipped_tree (struct edit_baton*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_node_file ; 
 int /*<<< orphan*/  svn_node_unknown ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__conflict_read_tree_conflict (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_base_get_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_is_wcroot (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_conflict_action_edit ; 
 scalar_t__ svn_wc_conflict_reason_deleted ; 
 scalar_t__ svn_wc_conflict_reason_moved_away ; 
 scalar_t__ svn_wc_conflict_reason_obstructed ; 
 scalar_t__ svn_wc_conflict_reason_replaced ; 
 int /*<<< orphan*/  svn_wc_notify_skip_conflicted ; 
 int /*<<< orphan*/  svn_wc_notify_update_skip_obstruction ; 

__attribute__((used)) static svn_error_t *
open_file(const char *path,
          void *parent_baton,
          svn_revnum_t base_revision,
          apr_pool_t *pool,
          void **file_baton)
{
  struct dir_baton *pb = parent_baton;
  struct edit_baton *eb = pb->edit_baton;
  struct file_baton *fb;
  svn_boolean_t conflicted;
  svn_boolean_t conflict_ignored = FALSE;
  svn_boolean_t have_work;
  svn_wc__db_status_t status;
  svn_node_kind_t wc_kind;
  svn_skel_t *tree_conflict = NULL;

  /* the file_pool can stick around for a *long* time, so we want to use
     a subpool for any temporary allocations. */
  apr_pool_t *scratch_pool = svn_pool_create(pool);

  SVN_ERR(make_file_baton(&fb, pb, path, FALSE, pool));
  *file_baton = fb;

  if (fb->skip_this)
    return SVN_NO_ERROR;

  /* Detect obstructing working copies */
  {
    svn_boolean_t is_root;

    SVN_ERR(svn_wc__db_is_wcroot(&is_root, eb->db, fb->local_abspath,
                                 pool));

    if (is_root)
      {
        /* Just skip this node; a future update will handle it */
        SVN_ERR(remember_skipped_tree(eb, fb->local_abspath, pool));
        fb->skip_this = TRUE;
        fb->already_notified = TRUE;

        do_notification(eb, fb->local_abspath, svn_node_file,
                        svn_wc_notify_update_skip_obstruction, pool);

        return SVN_NO_ERROR;
      }
  }

  /* Sanity check. */

  SVN_ERR(svn_wc__db_read_info(&status, &wc_kind, &fb->old_revision,
                               &fb->old_repos_relpath, NULL, NULL,
                               &fb->changed_rev, &fb->changed_date,
                               &fb->changed_author, NULL,
                               &fb->original_checksum, NULL, NULL, NULL,
                               NULL, NULL, NULL, NULL, NULL, NULL,
                               &conflicted, NULL, NULL, &fb->local_prop_mods,
                               NULL, NULL, &have_work,
                               eb->db, fb->local_abspath,
                               fb->pool, scratch_pool));

  if (have_work)
    SVN_ERR(svn_wc__db_base_get_info(NULL, NULL, &fb->old_revision,
                                     &fb->old_repos_relpath, NULL, NULL,
                                     &fb->changed_rev, &fb->changed_date,
                                     &fb->changed_author, NULL,
                                     &fb->original_checksum, NULL, NULL,
                                     NULL, NULL, NULL,
                                     eb->db, fb->local_abspath,
                                     fb->pool, scratch_pool));

  SVN_ERR(calculate_repos_relpath(&fb->new_repos_relpath, fb->local_abspath,
                                  fb->old_repos_relpath, eb, pb,
                                  fb->pool, scratch_pool));

  /* Is this path a conflict victim? */
  if (fb->shadowed)
    conflicted = FALSE; /* Conflict applies to WORKING */
  else if (conflicted)
    SVN_ERR(node_already_conflicted(&conflicted, &conflict_ignored,
                                    eb->db, fb->local_abspath, pool));
  if (conflicted)
    {
      SVN_ERR(remember_skipped_tree(eb, fb->local_abspath, pool));

      fb->skip_this = TRUE;
      fb->already_notified = TRUE;

      do_notification(eb, fb->local_abspath, svn_node_unknown,
                      svn_wc_notify_skip_conflicted, scratch_pool);

      svn_pool_destroy(scratch_pool);

      return SVN_NO_ERROR;
    }
  else if (conflict_ignored)
    {
      fb->shadowed = TRUE;
    }

  /* Check for conflicts only when we haven't already recorded
   * a tree-conflict on a parent node. */
  if (!fb->shadowed)
    SVN_ERR(check_tree_conflict(&tree_conflict, eb, fb->local_abspath,
                                status, TRUE, svn_node_file,
                                svn_wc_conflict_action_edit,
                                fb->pool, scratch_pool));

  /* Is this path the victim of a newly-discovered tree conflict? */
  if (tree_conflict != NULL)
    {
      svn_wc_conflict_reason_t reason;
      fb->edit_conflict = tree_conflict;
      /* Other modifications wouldn't be a tree conflict */

      SVN_ERR(svn_wc__conflict_read_tree_conflict(&reason, NULL, NULL,
                                                  eb->db, fb->local_abspath,
                                                  tree_conflict,
                                                  scratch_pool, scratch_pool));
      SVN_ERR_ASSERT(reason == svn_wc_conflict_reason_deleted
                     || reason == svn_wc_conflict_reason_moved_away
                     || reason == svn_wc_conflict_reason_replaced
                     || reason == svn_wc_conflict_reason_obstructed);

      /* Continue updating BASE */
      if (reason == svn_wc_conflict_reason_obstructed)
        fb->edit_obstructed = TRUE;
      else
        fb->shadowed = TRUE;
    }

  svn_pool_destroy(scratch_pool);

  return SVN_NO_ERROR;
}