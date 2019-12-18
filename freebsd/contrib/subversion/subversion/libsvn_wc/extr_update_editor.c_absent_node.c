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
typedef  int /*<<< orphan*/  svn_wc_notify_t ;
typedef  scalar_t__ svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_node_kind_t ;
struct TYPE_8__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct edit_baton {int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; int /*<<< orphan*/  conflict_baton; scalar_t__ conflict_func; int /*<<< orphan*/  db; int /*<<< orphan*/ * target_revision; int /*<<< orphan*/  repos_uuid; int /*<<< orphan*/  repos_root; int /*<<< orphan*/  notify_baton; int /*<<< orphan*/  (* notify_func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct dir_baton {int /*<<< orphan*/  new_repos_relpath; int /*<<< orphan*/  edit_obstructed; int /*<<< orphan*/  shadowed; int /*<<< orphan*/  local_abspath; scalar_t__ skip_this; struct edit_baton* edit_baton; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 scalar_t__ SVN_ERR_WC_PATH_NOT_FOUND ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  check_tree_conflict (int /*<<< orphan*/ **,struct edit_baton*,char const*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete_conflict (int /*<<< orphan*/ *,struct edit_baton*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delete_entry (char const*,int /*<<< orphan*/ ,struct dir_baton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_notification (struct edit_baton*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mark_directory_edited (struct dir_baton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_dirent_basename (char const*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_node_unknown ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 char* svn_relpath_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__conflict_invoke_resolver (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_base_add_excluded_node (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_base_get_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_is_wcroot (scalar_t__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc__db_read_info (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__db_status_excluded ; 
 scalar_t__ svn_wc__db_status_normal ; 
 scalar_t__ svn_wc__db_status_not_present ; 
 scalar_t__ svn_wc__db_status_server_excluded ; 
 int /*<<< orphan*/  svn_wc_conflict_action_add ; 
 int /*<<< orphan*/ * svn_wc_create_notify (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_tree_conflict ; 
 int /*<<< orphan*/  svn_wc_notify_update_skip_obstruction ; 

__attribute__((used)) static svn_error_t *
absent_node(const char *path,
            svn_node_kind_t absent_kind,
            void *parent_baton,
            apr_pool_t *pool)
{
  struct dir_baton *pb = parent_baton;
  struct edit_baton *eb = pb->edit_baton;
  apr_pool_t *scratch_pool = svn_pool_create(pool);
  const char *name = svn_dirent_basename(path, NULL);
  const char *local_abspath;
  svn_error_t *err;
  svn_wc__db_status_t status;
  svn_node_kind_t kind;
  svn_skel_t *tree_conflict = NULL;

  if (pb->skip_this)
    return SVN_NO_ERROR;

  local_abspath = svn_dirent_join(pb->local_abspath, name, scratch_pool);
  /* If an item by this name is scheduled for addition that's a
     genuine tree-conflict.  */
  err = svn_wc__db_read_info(&status, &kind, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL,
                             eb->db, local_abspath,
                             scratch_pool, scratch_pool);

  if (err)
    {
      if (err->apr_err != SVN_ERR_WC_PATH_NOT_FOUND)
        return svn_error_trace(err);

      svn_error_clear(err);
      status = svn_wc__db_status_not_present;
      kind = svn_node_unknown;
    }

  if (status != svn_wc__db_status_server_excluded)
    SVN_ERR(mark_directory_edited(pb, scratch_pool));
  /* Else fall through as we should update the revision anyway */

  if (status == svn_wc__db_status_normal)
    {
      svn_boolean_t wcroot;
      /* We found an obstructing working copy or a file external! */

      SVN_ERR(svn_wc__db_is_wcroot(&wcroot, eb->db, local_abspath,
                                   scratch_pool));

      if (wcroot)
        {
          /*
             We have an obstructing working copy; possibly a directory external

             We can do two things now:
             1) notify the user, record a skip, etc.
             2) Just record the absent node in BASE in the parent
                working copy.

             As option 2 happens to be exactly what we do anyway, fall through.
           */
        }
      else
        {
          svn_boolean_t file_external;
          svn_revnum_t revnum;

          SVN_ERR(svn_wc__db_base_get_info(NULL, NULL, &revnum, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL,
                                           &file_external,
                                           eb->db, local_abspath,
                                           scratch_pool, scratch_pool));

          if (file_external)
            {
              /* The server asks us to replace a file external
                 (Existing BASE node; not reported by the working copy crawler
                  or there would have been a delete_entry() call.

                 There is no way we can store this state in the working copy as
                 the BASE layer is already filled.
                 We could error out, but that is not helping anybody; the user is not
                 even seeing with what the file external would be replaced, so let's
                 report a skip and continue the update.
               */

              if (eb->notify_func)
                {
                  svn_wc_notify_t *notify;
                  notify = svn_wc_create_notify(
                                    local_abspath,
                                    svn_wc_notify_update_skip_obstruction,
                                    scratch_pool);

                  eb->notify_func(eb->notify_baton, notify, scratch_pool);
                }

              svn_pool_destroy(scratch_pool);
              return SVN_NO_ERROR;
            }
          else
            {
              /* We have a normal local node that will now be hidden for the
                 user. Let's try to delete what is there. This may introduce
                 tree conflicts if there are local changes */
              SVN_ERR(delete_entry(path, revnum, pb, scratch_pool));

              /* delete_entry() promises that BASE is empty after the operation,
                 so we can just fall through now */
            }
        }
    }
  else if (status == svn_wc__db_status_not_present
           || status == svn_wc__db_status_server_excluded
           || status == svn_wc__db_status_excluded)
    {
      /* The BASE node is not actually there, so we can safely turn it into
         an absent node */
    }
  else
    {
      /* We have a local addition. If this would be a BASE node it would have
         been deleted before we get here. (Which might have turned it into
         a copy). */
      SVN_ERR_ASSERT(status != svn_wc__db_status_normal);

      if (!pb->shadowed && !pb->edit_obstructed)
        SVN_ERR(check_tree_conflict(&tree_conflict, eb, local_abspath,
                                    status, FALSE, svn_node_unknown,
                                    svn_wc_conflict_action_add,
                                    scratch_pool, scratch_pool));

    }

  {
    const char *repos_relpath;
    repos_relpath = svn_relpath_join(pb->new_repos_relpath, name, scratch_pool);

    if (tree_conflict)
      SVN_ERR(complete_conflict(tree_conflict, eb, local_abspath,
                                NULL, SVN_INVALID_REVNUM, repos_relpath,
                                kind, svn_node_unknown, NULL,
                                scratch_pool, scratch_pool));

    /* Insert an excluded node below the parent node to note that this child
       is absent. (This puts it in the parent db if the child is obstructed) */
    SVN_ERR(svn_wc__db_base_add_excluded_node(eb->db, local_abspath,
                                              repos_relpath, eb->repos_root,
                                              eb->repos_uuid,
                                              *(eb->target_revision),
                                              absent_kind,
                                              svn_wc__db_status_server_excluded,
                                              tree_conflict, NULL,
                                              scratch_pool));

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
        do_notification(eb, local_abspath, kind, svn_wc_notify_tree_conflict,
                        scratch_pool);
      }
  }

  svn_pool_destroy(scratch_pool);

  return SVN_NO_ERROR;
}