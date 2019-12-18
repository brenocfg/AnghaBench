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
typedef  int /*<<< orphan*/  svn_wc_notify_action_t ;
typedef  scalar_t__ svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
struct edit_baton {char const* target_abspath; int target_deleted; int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; int /*<<< orphan*/  conflict_baton; scalar_t__ conflict_func; int /*<<< orphan*/  db; int /*<<< orphan*/ * target_revision; } ;
struct dir_baton {scalar_t__ edit_obstructed; scalar_t__ shadowed; int /*<<< orphan*/  local_abspath; int /*<<< orphan*/  pool; scalar_t__ deletion_conflicts; scalar_t__ old_repos_relpath; scalar_t__ skip_this; struct edit_baton* edit_baton; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int TRUE ; 
 scalar_t__ apr_hash_make (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  calculate_repos_relpath (char const**,char const*,char const*,struct edit_baton*,struct dir_baton*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_tree_conflict (int /*<<< orphan*/ **,struct edit_baton*,char const*,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete_conflict (int /*<<< orphan*/ *,struct edit_baton*,char const*,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_notification (struct edit_baton*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mark_directory_edited (struct dir_baton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  node_already_conflicted (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  path_join_under_root (char const**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remember_skipped_tree (struct edit_baton*,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_node_none ; 
 int /*<<< orphan*/  svn_node_unknown ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 char* svn_relpath_basename (char const*,int /*<<< orphan*/ *) ; 
 char* svn_relpath_skip_ancestor (scalar_t__,char const*) ; 
 int /*<<< orphan*/  svn_wc__conflict_invoke_resolver (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_base_get_info (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_base_remove (int /*<<< orphan*/ ,char const*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_is_wcroot (int*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_info (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__db_status_excluded ; 
 scalar_t__ svn_wc__db_status_not_present ; 
 scalar_t__ svn_wc__db_status_server_excluded ; 
 int /*<<< orphan*/  svn_wc__wq_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_conflict_action_delete ; 
 int /*<<< orphan*/  svn_wc_notify_skip_conflicted ; 
 int /*<<< orphan*/  svn_wc_notify_tree_conflict ; 
 int /*<<< orphan*/  svn_wc_notify_update_delete ; 
 int /*<<< orphan*/  svn_wc_notify_update_shadowed_delete ; 
 int /*<<< orphan*/  svn_wc_notify_update_skip_obstruction ; 

__attribute__((used)) static svn_error_t *
delete_entry(const char *path,
             svn_revnum_t revision,
             void *parent_baton,
             apr_pool_t *pool)
{
  struct dir_baton *pb = parent_baton;
  struct edit_baton *eb = pb->edit_baton;
  const char *base = svn_relpath_basename(path, NULL);
  const char *local_abspath;
  const char *repos_relpath;
  const char *deleted_repos_relpath;
  svn_node_kind_t kind;
  svn_revnum_t old_revision;
  svn_boolean_t conflicted;
  svn_boolean_t have_work;
  svn_skel_t *tree_conflict = NULL;
  svn_wc__db_status_t status;
  svn_wc__db_status_t base_status;
  apr_pool_t *scratch_pool;
  svn_boolean_t deleting_target;
  svn_boolean_t deleting_switched;

  if (pb->skip_this)
    return SVN_NO_ERROR;

  scratch_pool = svn_pool_create(pb->pool);

  SVN_ERR(mark_directory_edited(pb, scratch_pool));

  SVN_ERR(path_join_under_root(&local_abspath, pb->local_abspath, base,
                               scratch_pool));

  deleting_target =  (strcmp(local_abspath, eb->target_abspath) == 0);

  /* Detect obstructing working copies */
  {
    svn_boolean_t is_root;


    SVN_ERR(svn_wc__db_is_wcroot(&is_root, eb->db, local_abspath,
                                 scratch_pool));

    if (is_root)
      {
        /* Just skip this node; a future update will handle it */
        SVN_ERR(remember_skipped_tree(eb, local_abspath, pool));
        do_notification(eb, local_abspath, svn_node_unknown,
                        svn_wc_notify_update_skip_obstruction, scratch_pool);

        svn_pool_destroy(scratch_pool);

        return SVN_NO_ERROR;
      }
  }

  SVN_ERR(svn_wc__db_read_info(&status, &kind, &old_revision, &repos_relpath,
                               NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                               NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                               &conflicted, NULL, NULL, NULL,
                               NULL, NULL, &have_work,
                               eb->db, local_abspath,
                               scratch_pool, scratch_pool));

  if (!have_work)
    {
      base_status = status;
    }
  else
    SVN_ERR(svn_wc__db_base_get_info(&base_status, NULL, &old_revision,
                                     &repos_relpath,
                                     NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                     NULL, NULL, NULL, NULL, NULL,
                                     eb->db, local_abspath,
                                     scratch_pool, scratch_pool));

  if (pb->old_repos_relpath && repos_relpath)
    {
      const char *expected_name;

      expected_name = svn_relpath_skip_ancestor(pb->old_repos_relpath,
                                                repos_relpath);

      deleting_switched = (!expected_name || strcmp(expected_name, base) != 0);
    }
  else
    deleting_switched = FALSE;

  /* Is this path a conflict victim? */
  if (pb->shadowed)
    conflicted = FALSE; /* Conflict applies to WORKING */
  else if (conflicted)
    SVN_ERR(node_already_conflicted(&conflicted, NULL,
                                    eb->db, local_abspath, scratch_pool));
  if (conflicted)
    {
      SVN_ERR(remember_skipped_tree(eb, local_abspath, scratch_pool));

      do_notification(eb, local_abspath, svn_node_unknown,
                      svn_wc_notify_skip_conflicted,
                      scratch_pool);

      svn_pool_destroy(scratch_pool);

      return SVN_NO_ERROR;
    }


  /* Receive the remote removal of excluded/server-excluded/not present node.
     Do not notify, but perform the change even when the node is shadowed */
  if (base_status == svn_wc__db_status_not_present
      || base_status == svn_wc__db_status_excluded
      || base_status == svn_wc__db_status_server_excluded)
    {
      SVN_ERR(svn_wc__db_base_remove(eb->db, local_abspath, TRUE,
                                     deleting_target, FALSE,
                                     *eb->target_revision,
                                     NULL, NULL,
                                     scratch_pool));

      if (deleting_target)
        eb->target_deleted = TRUE;

      svn_pool_destroy(scratch_pool);

      return SVN_NO_ERROR;
    }

  /* Is this path the victim of a newly-discovered tree conflict?  If so,
   * remember it and notify the client. Then (if it was existing and
   * modified), re-schedule the node to be added back again, as a (modified)
   * copy of the previous base version.  */

  /* Check for conflicts only when we haven't already recorded
   * a tree-conflict on a parent node. */
  if (!pb->shadowed && !pb->edit_obstructed)
    {
      SVN_ERR(check_tree_conflict(&tree_conflict, eb, local_abspath,
                                  status, TRUE,
                                  kind,
                                  svn_wc_conflict_action_delete,
                                  pb->pool, scratch_pool));
    }

  if (tree_conflict != NULL)
    {
      /* When we raise a tree conflict on a node, we don't want to mark the
       * node as skipped, to allow a replacement to continue doing at least
       * a bit of its work (possibly adding a not present node, for the
       * next update) */
      if (!pb->deletion_conflicts)
        pb->deletion_conflicts = apr_hash_make(pb->pool);

      svn_hash_sets(pb->deletion_conflicts, apr_pstrdup(pb->pool, base),
                    tree_conflict);

      /* Whatever the kind of conflict, we can just clear BASE
         by turning whatever is there into a copy */
    }

  /* Calculate the repository-relative path of the entry which was
   * deleted. For updates it's the same as REPOS_RELPATH but for
   * switches it is within the switch target. */
  SVN_ERR(calculate_repos_relpath(&deleted_repos_relpath, local_abspath,
                                  repos_relpath, eb, pb, scratch_pool,
                                  scratch_pool));
  SVN_ERR(complete_conflict(tree_conflict, eb, local_abspath, repos_relpath,
                            old_revision, deleted_repos_relpath,
                            kind, svn_node_none, NULL,
                            pb->pool, scratch_pool));

  /* Issue a wq operation to delete the BASE_NODE data and to delete actual
     nodes based on that from disk, but leave any WORKING_NODEs on disk.

     Local modifications are already turned into copies at this point.

     If the thing being deleted is the *target* of this update, then
     we need to recreate a 'deleted' entry, so that the parent can give
     accurate reports about itself in the future. */
  if (! deleting_target && ! deleting_switched)
    {
      /* Delete, and do not leave a not-present node.  */
      SVN_ERR(svn_wc__db_base_remove(eb->db, local_abspath,
                                     (tree_conflict != NULL),
                                     FALSE, FALSE,
                                     SVN_INVALID_REVNUM /* not_present_rev */,
                                     tree_conflict, NULL,
                                     scratch_pool));
    }
  else
    {
      /* Delete, leaving a not-present node.  */
      SVN_ERR(svn_wc__db_base_remove(eb->db, local_abspath,
                                     (tree_conflict != NULL),
                                     TRUE, FALSE,
                                     *eb->target_revision,
                                     tree_conflict, NULL,
                                     scratch_pool));
      if (deleting_target)
        eb->target_deleted = TRUE;
      else
        {
          /* Don't remove the not-present marker at the final bump */
          SVN_ERR(remember_skipped_tree(eb, local_abspath, pool));
        }
    }

  SVN_ERR(svn_wc__wq_run(eb->db, pb->local_abspath,
                         eb->cancel_func, eb->cancel_baton,
                         scratch_pool));

  /* Notify. */
  if (tree_conflict)
    {
      if (eb->conflict_func)
        SVN_ERR(svn_wc__conflict_invoke_resolver(eb->db, local_abspath,
                                                 kind,
                                                 tree_conflict,
                                                 NULL /* merge_options */,
                                                 eb->conflict_func,
                                                 eb->conflict_baton,
                                                 eb->cancel_func,
                                                 eb->cancel_baton,
                                                 scratch_pool));
      do_notification(eb, local_abspath, kind,
                      svn_wc_notify_tree_conflict, scratch_pool);
    }
  else
    {
      svn_wc_notify_action_t action = svn_wc_notify_update_delete;

      if (pb->shadowed || pb->edit_obstructed)
        action = svn_wc_notify_update_shadowed_delete;

      do_notification(eb, local_abspath, kind, action, scratch_pool);
    }

  svn_pool_destroy(scratch_pool);

  return SVN_NO_ERROR;
}