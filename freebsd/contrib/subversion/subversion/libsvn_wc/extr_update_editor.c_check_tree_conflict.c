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
typedef  int /*<<< orphan*/  svn_wc_conflict_action_t ;
typedef  int svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct edit_baton {int /*<<< orphan*/  db; int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_MALFUNCTION () ; 
 int /*<<< orphan*/  SVN_ERR_WC_FOUND_CONFLICT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ SVN_WC_CONFLICT_REASON_NONE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_check_path (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_node_none ; 
 int /*<<< orphan*/  svn_wc__conflict_skel_add_tree_conflict (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,scalar_t__,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__conflict_skel_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_base_moved_to (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_scan_addition (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
#define  svn_wc__db_status_added 137 
#define  svn_wc__db_status_base_deleted 136 
#define  svn_wc__db_status_copied 135 
#define  svn_wc__db_status_deleted 134 
#define  svn_wc__db_status_excluded 133 
#define  svn_wc__db_status_incomplete 132 
#define  svn_wc__db_status_moved_here 131 
#define  svn_wc__db_status_normal 130 
#define  svn_wc__db_status_not_present 129 
#define  svn_wc__db_status_server_excluded 128 
 int /*<<< orphan*/  svn_wc__node_has_local_mods (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_conflict_action_add ; 
 int /*<<< orphan*/  svn_wc_conflict_action_delete ; 
 int /*<<< orphan*/  svn_wc_conflict_action_edit ; 
 int /*<<< orphan*/  svn_wc_conflict_action_replace ; 
 scalar_t__ svn_wc_conflict_reason_added ; 
 scalar_t__ svn_wc_conflict_reason_deleted ; 
 scalar_t__ svn_wc_conflict_reason_edited ; 
 scalar_t__ svn_wc_conflict_reason_moved_away ; 
 scalar_t__ svn_wc_conflict_reason_moved_here ; 
 scalar_t__ svn_wc_conflict_reason_obstructed ; 
 scalar_t__ svn_wc_conflict_reason_replaced ; 

__attribute__((used)) static svn_error_t *
check_tree_conflict(svn_skel_t **pconflict,
                    struct edit_baton *eb,
                    const char *local_abspath,
                    svn_wc__db_status_t working_status,
                    svn_boolean_t exists_in_repos,
                    svn_node_kind_t expected_kind,
                    svn_wc_conflict_action_t action,
                    apr_pool_t *result_pool,
                    apr_pool_t *scratch_pool)
{
  svn_wc_conflict_reason_t reason = SVN_WC_CONFLICT_REASON_NONE;
  svn_boolean_t modified = FALSE;
  const char *move_src_op_root_abspath = NULL;

  *pconflict = NULL;

  /* Find out if there are any local changes to this node that may
   * be the "reason" of a tree-conflict with the incoming "action". */
  switch (working_status)
    {
      case svn_wc__db_status_added:
      case svn_wc__db_status_moved_here:
      case svn_wc__db_status_copied:
        if (!exists_in_repos)
          {
            /* The node is locally added, and it did not exist before.  This
             * is an 'update', so the local add can only conflict with an
             * incoming 'add'.  In fact, if we receive anything else than an
             * svn_wc_conflict_action_add (which includes 'added',
             * 'copied-here' and 'moved-here') during update on a node that
             * did not exist before, then something is very wrong.
             * Note that if there was no action on the node, this code
             * would not have been called in the first place. */
            SVN_ERR_ASSERT(action == svn_wc_conflict_action_add);

            /* Scan the addition in case our caller didn't. */
            if (working_status == svn_wc__db_status_added)
              SVN_ERR(svn_wc__db_scan_addition(&working_status, NULL, NULL,
                                               NULL, NULL, NULL, NULL,
                                               NULL, NULL,
                                               eb->db, local_abspath,
                                               scratch_pool, scratch_pool));

            if (working_status == svn_wc__db_status_moved_here)
              reason = svn_wc_conflict_reason_moved_here;
            else
              reason = svn_wc_conflict_reason_added;
          }
        else
          {
            /* The node is locally replaced but could also be moved-away,
               but we can't report that it is moved away and replaced.

               And we wouldn't be able to store that each of a dozen
               descendants was moved to other locations...

               Replaced is what actually happened... */

            reason = svn_wc_conflict_reason_replaced;
          }
        break;


      case svn_wc__db_status_deleted:
        {
          SVN_ERR(svn_wc__db_base_moved_to(NULL, NULL, NULL,
                                           &move_src_op_root_abspath,
                                           eb->db, local_abspath,
                                           scratch_pool, scratch_pool));
          if (move_src_op_root_abspath)
            reason = svn_wc_conflict_reason_moved_away;
          else
            reason = svn_wc_conflict_reason_deleted;
        }
        break;

      case svn_wc__db_status_incomplete:
        /* We used svn_wc__db_read_info(), so 'incomplete' means
         * - there is no node in the WORKING tree
         * - a BASE node is known to exist
         * So the node exists and is essentially 'normal'. We still need to
         * check prop and text mods, and those checks will retrieve the
         * missing information (hopefully). */
      case svn_wc__db_status_normal:
        if (action == svn_wc_conflict_action_edit)
          {
            /* An edit onto a local edit or onto *no* local changes is no
             * tree-conflict. (It's possibly a text- or prop-conflict,
             * but we don't handle those here.)
             *
             * Except when there is a local obstruction
             */
            if (exists_in_repos)
              {
                svn_node_kind_t disk_kind;

                SVN_ERR(svn_io_check_path(local_abspath, &disk_kind,
                                          scratch_pool));

                if (disk_kind != expected_kind && disk_kind != svn_node_none)
                  {
                    reason = svn_wc_conflict_reason_obstructed;
                    break;
                  }

              }
            return SVN_NO_ERROR;
          }

        /* Replace is handled as delete and then specifically in
           add_directory() and add_file(), so we only expect deletes here */
        SVN_ERR_ASSERT(action == svn_wc_conflict_action_delete);

        /* Check if the update wants to delete or replace a locally
         * modified node. */


        /* Do a deep tree detection of local changes. The update editor will
         * not visit the subdirectories of a directory that it wants to delete.
         * Therefore, we need to start a separate crawl here. */

        SVN_ERR(svn_wc__node_has_local_mods(&modified, NULL,
                                            eb->db, local_abspath, FALSE,
                                            eb->cancel_func, eb->cancel_baton,
                                            scratch_pool));

        if (modified)
          {
            if (working_status == svn_wc__db_status_deleted)
              reason = svn_wc_conflict_reason_deleted;
            else
              reason = svn_wc_conflict_reason_edited;
          }
        break;

      case svn_wc__db_status_server_excluded:
        /* Not allowed to view the node. Not allowed to report tree
         * conflicts. */
      case svn_wc__db_status_excluded:
        /* Locally marked as excluded. No conflicts wanted. */
      case svn_wc__db_status_not_present:
        /* A committed delete (but parent not updated). The delete is
           committed, so no conflict possible during update. */
        return SVN_NO_ERROR;

      case svn_wc__db_status_base_deleted:
        /* An internal status. Should never show up here. */
        SVN_ERR_MALFUNCTION();
        break;

    }

  if (reason == SVN_WC_CONFLICT_REASON_NONE)
    /* No conflict with the current action. */
    return SVN_NO_ERROR;


  /* Sanity checks. Note that if there was no action on the node, this function
   * would not have been called in the first place.*/
  if (reason == svn_wc_conflict_reason_edited
      || reason == svn_wc_conflict_reason_obstructed
      || reason == svn_wc_conflict_reason_deleted
      || reason == svn_wc_conflict_reason_moved_away
      || reason == svn_wc_conflict_reason_replaced)
    {
      /* When the node existed before (it was locally deleted, replaced or
       * edited), then 'update' cannot add it "again". So it can only send
       * _action_edit, _delete or _replace. */
    if (action != svn_wc_conflict_action_edit
        && action != svn_wc_conflict_action_delete
        && action != svn_wc_conflict_action_replace)
      return svn_error_createf(SVN_ERR_WC_FOUND_CONFLICT, NULL,
               _("Unexpected attempt to add a node at path '%s'"),
               svn_dirent_local_style(local_abspath, scratch_pool));
    }
  else if (reason == svn_wc_conflict_reason_added ||
           reason == svn_wc_conflict_reason_moved_here)
    {
      /* When the node did not exist before (it was locally added),
       * then 'update' cannot want to modify it in any way.
       * It can only send _action_add. */
      if (action != svn_wc_conflict_action_add)
        return svn_error_createf(SVN_ERR_WC_FOUND_CONFLICT, NULL,
                 _("Unexpected attempt to edit, delete, or replace "
                   "a node at path '%s'"),
                 svn_dirent_local_style(local_abspath, scratch_pool));

    }


  /* A conflict was detected. Create a conflict skel to record it. */
  *pconflict = svn_wc__conflict_skel_create(result_pool);

  SVN_ERR(svn_wc__conflict_skel_add_tree_conflict(*pconflict,
                                                  eb->db, local_abspath,
                                                  reason,
                                                  action,
                                                  move_src_op_root_abspath,
                                                  result_pool, scratch_pool));

  return SVN_NO_ERROR;
}