#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_wc__db_status_t ;
struct TYPE_8__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  scalar_t__ svn_depth_t ;
struct edit_baton {char* target_basename; scalar_t__ requested_depth; int /*<<< orphan*/ * pool; int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; int /*<<< orphan*/  wcroot_abspath; int /*<<< orphan*/  db; int /*<<< orphan*/  target_abspath; scalar_t__ switch_repos_relpath; int /*<<< orphan*/  notify_baton; int /*<<< orphan*/  notify_func; int /*<<< orphan*/  edited; int /*<<< orphan*/  wcroot_iprops; int /*<<< orphan*/  skipped_trees; int /*<<< orphan*/ * target_revision; int /*<<< orphan*/  repos_uuid; int /*<<< orphan*/  repos_root; int /*<<< orphan*/  target_deleted; int /*<<< orphan*/  anchor_abspath; int /*<<< orphan*/  root_opened; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_WC_PATH_NOT_FOUND ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  apr_pool_cleanup_kill (int /*<<< orphan*/ *,struct edit_baton*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_edit_baton ; 
 scalar_t__ svn_depth_empty ; 
 scalar_t__ svn_depth_infinity ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc__db_base_get_info (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_base_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_op_bump_revisions_post_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_props_streamily (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct edit_baton*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__db_status_excluded ; 
 int /*<<< orphan*/  svn_wc__db_temp_op_end_directory_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__wq_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_keywords_after_switch_cb ; 

__attribute__((used)) static svn_error_t *
close_edit(void *edit_baton,
           apr_pool_t *pool)
{
  struct edit_baton *eb = edit_baton;
  apr_pool_t *scratch_pool = eb->pool;

  /* The editor didn't even open the root; we have to take care of
     some cleanup stuffs. */
  if (! eb->root_opened
      && *eb->target_basename == '\0')
    {
      /* We need to "un-incomplete" the root directory. */
      SVN_ERR(svn_wc__db_temp_op_end_directory_update(eb->db,
                                                      eb->anchor_abspath,
                                                      scratch_pool));
    }

  /* By definition, anybody "driving" this editor for update or switch
     purposes at a *minimum* must have called set_target_revision() at
     the outset, and close_edit() at the end -- even if it turned out
     that no changes ever had to be made, and open_root() was never
     called.  That's fine.  But regardless, when the edit is over,
     this editor needs to make sure that *all* paths have had their
     revisions bumped to the new target revision. */

  /* Make sure our update target now has the new working revision.
     Also, if this was an 'svn switch', then rewrite the target's
     url.  All of this tweaking might happen recursively!  Note
     that if eb->target is NULL, that's okay (albeit "sneaky",
     some might say).  */

  /* Extra check: if the update did nothing but make its target
     'deleted', then do *not* run cleanup on the target, as it
     will only remove the deleted entry!  */
  if (! eb->target_deleted)
    {
      SVN_ERR(svn_wc__db_op_bump_revisions_post_update(eb->db,
                                                       eb->target_abspath,
                                                       eb->requested_depth,
                                                       eb->switch_repos_relpath,
                                                       eb->repos_root,
                                                       eb->repos_uuid,
                                                       *(eb->target_revision),
                                                       eb->skipped_trees,
                                                       eb->wcroot_iprops,
                                                       ! eb->edited,
                                                       eb->notify_func,
                                                       eb->notify_baton,
                                                       eb->pool));

      if (*eb->target_basename != '\0')
        {
          svn_wc__db_status_t status;
          svn_error_t *err;

          /* Note: we are fetching information about the *target*, not anchor.
             There is no guarantee that the target has a BASE node.
             For example:

               The node was not present in BASE, but locally-added, and the
               update did not create a new BASE node "under" the local-add.

             If there is no BASE node for the target, then we certainly don't
             have to worry about removing it. */
          err = svn_wc__db_base_get_info(&status, NULL, NULL, NULL, NULL, NULL,
                                         NULL, NULL, NULL, NULL, NULL, NULL,
                                         NULL, NULL, NULL, NULL,
                                         eb->db, eb->target_abspath,
                                         scratch_pool, scratch_pool);
          if (err)
            {
              if (err->apr_err != SVN_ERR_WC_PATH_NOT_FOUND)
                return svn_error_trace(err);

              svn_error_clear(err);
            }
          else if (status == svn_wc__db_status_excluded)
            {
              /* There is a small chance that the explicit target of an update/
                 switch is gone in the repository, in that specific case the
                 node hasn't been re-added to the BASE tree by this update.

                 If so, we should get rid of this excluded node now. */

              SVN_ERR(svn_wc__db_base_remove(eb->db, eb->target_abspath,
                                             TRUE, FALSE, FALSE,
                                             SVN_INVALID_REVNUM,
                                             NULL, NULL, scratch_pool));
            }
        }
    }

  /* Update keywords in switched files.
     GOTO #1975 (the year of the Altair 8800). */
  if (eb->switch_repos_relpath)
    {
      svn_depth_t depth;

      if (eb->requested_depth > svn_depth_empty)
        depth = eb->requested_depth;
      else
        depth = svn_depth_infinity;

      SVN_ERR(svn_wc__db_read_props_streamily(eb->db,
                                              eb->target_abspath,
                                              depth,
                                              FALSE, /* pristine */
                                              NULL, /* changelists */
                                              update_keywords_after_switch_cb,
                                              eb,
                                              eb->cancel_func,
                                              eb->cancel_baton,
                                              scratch_pool));
    }

  /* The edit is over: run the wq with proper cancel support,
     but first kill the handler that would run it on the pool
     cleanup at the end of this function. */
  apr_pool_cleanup_kill(eb->pool, eb, cleanup_edit_baton);

  SVN_ERR(svn_wc__wq_run(eb->db, eb->wcroot_abspath,
                         eb->cancel_func, eb->cancel_baton,
                         eb->pool));

  /* The edit is over, free its pool.
     ### No, this is wrong.  Who says this editor/baton won't be used
     again?  But the change is not merely to remove this call.  We
     should also make eb->pool not be a subpool (see make_editor),
     and change callers of svn_client_{checkout,update,switch} to do
     better pool management. ### */

  svn_pool_destroy(eb->pool);

  return SVN_NO_ERROR;
}