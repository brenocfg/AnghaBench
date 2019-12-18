#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_conflict_reason_t ;
typedef  scalar_t__ svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_9__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int svn_boolean_t ;
struct file_baton {int /*<<< orphan*/  local_abspath; void* already_notified; int /*<<< orphan*/ * edit_conflict; int /*<<< orphan*/  pool; int /*<<< orphan*/  name; int /*<<< orphan*/  new_repos_relpath; int /*<<< orphan*/  old_revision; int /*<<< orphan*/  old_repos_relpath; int /*<<< orphan*/  edit_baton; void* shadowed; void* obstruction_found; void* add_existed; void* skip_this; } ;
struct edit_baton {char* target_basename; int /*<<< orphan*/  db; int /*<<< orphan*/  target_abspath; scalar_t__ allow_unver_obstructions; int /*<<< orphan*/  adds_as_modification; int /*<<< orphan*/  clean_checkout; } ;
struct dir_baton {scalar_t__ deletion_conflicts; int /*<<< orphan*/  pool; int /*<<< orphan*/  not_present_nodes; scalar_t__ parent_baton; struct edit_baton* edit_baton; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int FALSE ; 
 int IS_NODE_PRESENT (scalar_t__) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_WC_OBSTRUCTED_UPDATE ; 
 scalar_t__ SVN_ERR_WC_PATH_NOT_FOUND ; 
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 TYPE_1__* SVN_NO_ERROR ; 
 void* TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calculate_repos_relpath (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct edit_baton*,struct dir_baton*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_tree_conflict (int /*<<< orphan*/ **,struct edit_baton*,int /*<<< orphan*/ ,scalar_t__,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete_conflict (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_notification (struct edit_baton*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_file_baton (struct file_baton**,struct dir_baton*,char const*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mark_file_edited (struct file_baton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  node_already_conflicted (int*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remember_skipped_tree (struct edit_baton*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_dirent_local_style (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 
 int /*<<< orphan*/ * svn_hash_gets (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_check_path (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 int /*<<< orphan*/  svn_node_kind_to_word (scalar_t__) ; 
 scalar_t__ svn_node_none ; 
 scalar_t__ svn_node_symlink ; 
 scalar_t__ svn_node_unknown ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__conflict_read_tree_conflict (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__conflict_skel_add_tree_conflict (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__conflict_skel_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__db_is_wcroot (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_op_mark_conflict (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc__db_read_info (scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_scan_addition (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__db_status_added ; 
 scalar_t__ svn_wc__db_status_incomplete ; 
 scalar_t__ svn_wc__db_status_normal ; 
 scalar_t__ svn_wc__db_status_not_present ; 
 int /*<<< orphan*/  svn_wc_conflict_action_add ; 
 int /*<<< orphan*/  svn_wc_conflict_action_replace ; 
 int /*<<< orphan*/  svn_wc_conflict_reason_unversioned ; 
 scalar_t__ svn_wc_is_adm_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_skip_conflicted ; 
 int /*<<< orphan*/  svn_wc_notify_tree_conflict ; 
 int /*<<< orphan*/  svn_wc_notify_update_skip_obstruction ; 

__attribute__((used)) static svn_error_t *
add_file(const char *path,
         void *parent_baton,
         const char *copyfrom_path,
         svn_revnum_t copyfrom_rev,
         apr_pool_t *pool,
         void **file_baton)
{
  struct dir_baton *pb = parent_baton;
  struct edit_baton *eb = pb->edit_baton;
  struct file_baton *fb;
  svn_node_kind_t kind;
  svn_node_kind_t wc_kind;
  svn_wc__db_status_t status;
  apr_pool_t *scratch_pool;
  svn_boolean_t conflicted;
  svn_boolean_t conflict_ignored = FALSE;
  svn_boolean_t versioned_locally_and_present;
  svn_skel_t *tree_conflict = NULL;
  svn_error_t *err = SVN_NO_ERROR;

  SVN_ERR_ASSERT(! (copyfrom_path || SVN_IS_VALID_REVNUM(copyfrom_rev)));

  SVN_ERR(make_file_baton(&fb, pb, path, TRUE, pool));
  *file_baton = fb;

  if (fb->skip_this)
    return SVN_NO_ERROR;

  SVN_ERR(calculate_repos_relpath(&fb->new_repos_relpath, fb->local_abspath,
                                  NULL, eb, pb, fb->pool, pool));
  SVN_ERR(mark_file_edited(fb, pool));

  /* The file_pool can stick around for a *long* time, so we want to
     use a subpool for any temporary allocations. */
  scratch_pool = svn_pool_create(pool);


  /* It may not be named the same as the administrative directory. */
  if (svn_wc_is_adm_dir(fb->name, pool))
    return svn_error_createf(
       SVN_ERR_WC_OBSTRUCTED_UPDATE, NULL,
       _("Failed to add file '%s': object of the same name as the "
         "administrative directory"),
       svn_dirent_local_style(fb->local_abspath, pool));

  if (!eb->clean_checkout)
    {
      SVN_ERR(svn_io_check_path(fb->local_abspath, &kind, scratch_pool));

      err = svn_wc__db_read_info(&status, &wc_kind, NULL, NULL, NULL, NULL, NULL,
                                NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                NULL, NULL, NULL, NULL, NULL,
                                &conflicted, NULL, NULL, NULL, NULL, NULL, NULL,
                                eb->db, fb->local_abspath,
                                scratch_pool, scratch_pool);
    }
  else
    {
      kind =  svn_node_none;
      status = svn_wc__db_status_not_present;
      wc_kind = svn_node_unknown;
      conflicted = FALSE;
    }

  if (err)
    {
      if (err->apr_err != SVN_ERR_WC_PATH_NOT_FOUND)
        return svn_error_trace(err);

      svn_error_clear(err);
      wc_kind = svn_node_unknown;
      conflicted = FALSE;

      versioned_locally_and_present = FALSE;
    }
  else if (status == svn_wc__db_status_normal && wc_kind == svn_node_unknown)
    {
      SVN_ERR_ASSERT(conflicted);
      versioned_locally_and_present = FALSE; /* Tree conflict ACTUAL-only node */
    }
  else if (status == svn_wc__db_status_normal
           || status == svn_wc__db_status_incomplete)
    {
      svn_boolean_t root;

      SVN_ERR(svn_wc__db_is_wcroot(&root, eb->db, fb->local_abspath,
                                   scratch_pool));

      if (root)
        {
          /* !! We found the root of a working copy obstructing the wc !!

             If the directory would be part of our own working copy then
             we wouldn't have been called as an add_directory().

             The only thing we can do is add a not-present node, to allow
             a future update to bring in the new files when the problem is
             resolved.  Note that svn_wc__db_base_add_not_present_node()
             explicitly adds the node into the parent's node database. */

          svn_hash_sets(pb->not_present_nodes,
                        apr_pstrdup(pb->pool, fb->name),
                        svn_node_kind_to_word(svn_node_dir));
        }
      else if (wc_kind == svn_node_dir)
        {
          /* We have an editor violation. Github sometimes does this
             in its subversion compatibility code, when changing the
             depth of a working copy, or on updates from incomplete */
        }
      else
        {
          /* We found a file external occupating the place we need in BASE.

             We can't add a not-present node in this case as that would overwrite
             the file external. Luckily the file external itself stops us from
             forgetting a child of this parent directory like an obstructing
             working copy would.

             The reason we get here is that the adm crawler doesn't report
             file externals.
           */
          SVN_ERR_ASSERT(wc_kind == svn_node_file
                         || wc_kind == svn_node_symlink);
        }

      SVN_ERR(remember_skipped_tree(eb, fb->local_abspath, pool));
      fb->skip_this = TRUE;
      fb->already_notified = TRUE;

      do_notification(eb, fb->local_abspath, wc_kind,
                      svn_wc_notify_update_skip_obstruction, scratch_pool);

      svn_pool_destroy(scratch_pool);

      return SVN_NO_ERROR;
    }
  else
    versioned_locally_and_present = IS_NODE_PRESENT(status);


  /* Is this path a conflict victim? */
  if (fb->shadowed)
    conflicted = FALSE; /* Conflict applies to WORKING */
  else if (conflicted)
    {
      if (pb->deletion_conflicts)
        tree_conflict = svn_hash_gets(pb->deletion_conflicts, fb->name);

      if (tree_conflict)
        {
          svn_wc_conflict_reason_t reason;
          const char *move_src_op_root_abspath;
          /* So this deletion wasn't just a deletion, it is actually a
             replacement. Let's install a better tree conflict. */

          SVN_ERR(svn_wc__conflict_read_tree_conflict(&reason, NULL,
                                                      &move_src_op_root_abspath,
                                                      eb->db,
                                                      fb->local_abspath,
                                                      tree_conflict,
                                                      fb->pool, scratch_pool));

          tree_conflict = svn_wc__conflict_skel_create(fb->pool);

          SVN_ERR(svn_wc__conflict_skel_add_tree_conflict(
                                        tree_conflict,
                                        eb->db, fb->local_abspath,
                                        reason, svn_wc_conflict_action_replace,
                                        move_src_op_root_abspath,
                                        fb->pool, scratch_pool));

          /* And now stop checking for conflicts here and just perform
             a shadowed update */
          fb->edit_conflict = tree_conflict; /* Cache for close_file */
          tree_conflict = NULL; /* No direct notification */
          fb->shadowed = TRUE; /* Just continue */
          conflicted = FALSE; /* No skip */
        }
      else
        SVN_ERR(node_already_conflicted(&conflicted, &conflict_ignored,
                                        eb->db, fb->local_abspath, pool));
    }

  /* Now the usual conflict handling: skip. */
  if (conflicted)
    {
      SVN_ERR(remember_skipped_tree(eb, fb->local_abspath, pool));

      fb->skip_this = TRUE;
      fb->already_notified = TRUE;

      /* We skip this node, but once the update completes the parent node will
         be updated to the new revision. So a future recursive update of the
         parent will not bring in this new node as the revision of the parent
         describes to the repository that all children are available.

         To resolve this problem, we add a not-present node to allow bringing
         the node in once this conflict is resolved.

         Note that we can safely assume that no present base node exists,
         because then we would not have received an add_file.
       */
      svn_hash_sets(pb->not_present_nodes, apr_pstrdup(pb->pool, fb->name),
                    svn_node_kind_to_word(svn_node_file));

      do_notification(eb, fb->local_abspath, svn_node_file,
                      svn_wc_notify_skip_conflicted, scratch_pool);

      svn_pool_destroy(scratch_pool);

      return SVN_NO_ERROR;
    }
  else if (conflict_ignored)
    {
      fb->shadowed = TRUE;
    }

  if (fb->shadowed)
    {
      /* Nothing to check; does not and will not exist in working copy */
    }
  else if (versioned_locally_and_present)
    {
      /* What to do with a versioned or schedule-add file:

         If the UUID doesn't match the parent's, or the URL isn't a child of
         the parent dir's URL, it's an error.

         Set add_existed so that user notification is delayed until after any
         text or prop conflicts have been found.

         Whether the incoming add is a symlink or a file will only be known in
         close_file(), when the props are known. So with a locally added file
         or symlink, let close_file() check for a tree conflict.

         We will never see missing files here, because these would be
         re-added during the crawler phase. */
      svn_boolean_t local_is_file;

      /* Is the local node a copy or move */
      if (status == svn_wc__db_status_added)
        SVN_ERR(svn_wc__db_scan_addition(&status, NULL, NULL, NULL, NULL, NULL,
                                         NULL, NULL, NULL,
                                         eb->db, fb->local_abspath,
                                         scratch_pool, scratch_pool));

      /* Is there something that is a file? */
      local_is_file = (wc_kind == svn_node_file
                       || wc_kind == svn_node_symlink);

      /* Do tree conflict checking if
       *  - if there is a local copy.
       *  - if this is a switch operation
       *  - the node kinds mismatch
       *
       * During switch, local adds at the same path as incoming adds get
       * "lost" in that switching back to the original will no longer have the
       * local add. So switch always alerts the user with a tree conflict. */
      if (!eb->adds_as_modification
          || !local_is_file
          || status != svn_wc__db_status_added)
        {
          SVN_ERR(check_tree_conflict(&tree_conflict, eb,
                                      fb->local_abspath,
                                      status, FALSE, svn_node_none,
                                      svn_wc_conflict_action_add,
                                      fb->pool, scratch_pool));
        }

      if (tree_conflict == NULL)
        fb->add_existed = TRUE; /* Take over WORKING */
      else
        fb->shadowed = TRUE; /* Only update BASE */

    }
  else if (kind != svn_node_none)
    {
      /* There's an unversioned node at this path. */
      fb->obstruction_found = TRUE;

      /* Unversioned, obstructing files are handled by text merge/conflict,
       * if unversioned obstructions are allowed. */
      if (! (kind == svn_node_file && eb->allow_unver_obstructions))
        {
          /* Bring in the node as deleted */ /* ### Obstructed Conflict */
          fb->shadowed = TRUE;

          /* Mark a conflict */
          tree_conflict = svn_wc__conflict_skel_create(fb->pool);

          SVN_ERR(svn_wc__conflict_skel_add_tree_conflict(
                                        tree_conflict,
                                        eb->db, fb->local_abspath,
                                        svn_wc_conflict_reason_unversioned,
                                        svn_wc_conflict_action_add,
                                        NULL,
                                        fb->pool, scratch_pool));
        }
    }

  /* When this is not the update target add a not-present BASE node now,
     to allow marking the parent directory complete in its close_edit() call.
     This resolves issues when that occurs before the close_file(). */
  if (pb->parent_baton
      || *eb->target_basename == '\0'
      || (strcmp(fb->local_abspath, eb->target_abspath) != 0))
    {
      svn_hash_sets(pb->not_present_nodes, apr_pstrdup(pb->pool, fb->name),
                    svn_node_kind_to_word(svn_node_file));
    }

  if (tree_conflict != NULL)
    {
      SVN_ERR(complete_conflict(tree_conflict,
                                fb->edit_baton,
                                fb->local_abspath,
                                fb->old_repos_relpath,
                                fb->old_revision,
                                fb->new_repos_relpath,
                                wc_kind, svn_node_file,
                                pb->deletion_conflicts
                                  ? svn_hash_gets(pb->deletion_conflicts,
                                                  fb->name)
                                  : NULL,
                                fb->pool, scratch_pool));

      SVN_ERR(svn_wc__db_op_mark_conflict(eb->db,
                                          fb->local_abspath,
                                          tree_conflict, NULL,
                                          scratch_pool));

      fb->edit_conflict = tree_conflict;

      fb->already_notified = TRUE;
      do_notification(eb, fb->local_abspath, svn_node_file,
                      svn_wc_notify_tree_conflict, scratch_pool);
    }

  svn_pool_destroy(scratch_pool);

  return SVN_NO_ERROR;
}