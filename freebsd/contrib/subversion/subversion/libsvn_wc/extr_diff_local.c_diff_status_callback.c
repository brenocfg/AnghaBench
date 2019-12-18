#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ node_status; scalar_t__ text_status; scalar_t__ prop_status; scalar_t__ kind; char const* moved_from_abspath; int /*<<< orphan*/  copied; int /*<<< orphan*/  versioned; } ;
typedef  TYPE_1__ svn_wc_status3_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  scalar_t__ svn_wc__db_status_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  scalar_t__ svn_boolean_t ;
struct node_state_t {int /*<<< orphan*/ * baton; int /*<<< orphan*/ * propchanges; int /*<<< orphan*/  pool; int /*<<< orphan*/  left_props; int /*<<< orphan*/  right_props; scalar_t__ skip_children; struct node_state_t* parent; int /*<<< orphan*/  right_src; int /*<<< orphan*/  left_src; int /*<<< orphan*/  relpath; int /*<<< orphan*/  skip; int /*<<< orphan*/  local_abspath; } ;
struct diff_baton {int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; struct node_state_t* cur; TYPE_2__* processor; int /*<<< orphan*/  anchor_abspath; int /*<<< orphan*/ * db; int /*<<< orphan*/  ignore_ancestry; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;
struct TYPE_11__ {int /*<<< orphan*/  (* dir_closed ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* dir_changed ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ensure_state (struct diff_baton*,char const*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_depth_unknown ; 
 char const* svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_is_ancestor (int /*<<< orphan*/ ,char const*) ; 
 char* svn_dirent_skip_ancestor (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_prop_diffs (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__db_base_get_info (scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_base_get_props (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_info (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_props (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__db_status_deleted ; 
 scalar_t__ svn_wc__db_status_incomplete ; 
 scalar_t__ svn_wc__db_status_normal ; 
 int /*<<< orphan*/  svn_wc__diff_base_only_dir (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__diff_base_only_file (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__diff_base_working_diff (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__diff_local_only_dir (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,char const*,TYPE_2__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__diff_local_only_file (int /*<<< orphan*/ *,char const*,char const*,char const*,TYPE_2__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc_status_conflicted ; 
 scalar_t__ svn_wc_status_none ; 
 scalar_t__ svn_wc_status_normal ; 

__attribute__((used)) static svn_error_t *
diff_status_callback(void *baton,
                     const char *local_abspath,
                     const svn_wc_status3_t *status,
                     apr_pool_t *scratch_pool)
{
  struct diff_baton *eb = baton;
  svn_wc__db_t *db = eb->db;

  if (! status->versioned)
    return SVN_NO_ERROR; /* unversioned (includes dir externals) */

  if (status->node_status == svn_wc_status_conflicted
      && status->text_status == svn_wc_status_none
      && status->prop_status == svn_wc_status_none)
    {
      /* Node is an actual only node describing a tree conflict */
      return SVN_NO_ERROR;
    }

  /* Not text/prop modified, not copied. Easy out */
  if (status->node_status == svn_wc_status_normal && !status->copied)
    return SVN_NO_ERROR;

  /* Mark all directories where we are no longer inside as closed */
  while (eb->cur
         && !svn_dirent_is_ancestor(eb->cur->local_abspath, local_abspath))
    {
      struct node_state_t *ns = eb->cur;

      if (!ns->skip)
        {
          if (ns->propchanges)
            SVN_ERR(eb->processor->dir_changed(ns->relpath,
                                               ns->left_src,
                                               ns->right_src,
                                               ns->left_props,
                                               ns->right_props,
                                               ns->propchanges,
                                               ns->baton,
                                               eb->processor,
                                               ns->pool));
          else
            SVN_ERR(eb->processor->dir_closed(ns->relpath,
                                              ns->left_src,
                                              ns->right_src,
                                              ns->baton,
                                              eb->processor,
                                              ns->pool));
        }
      eb->cur = ns->parent;
      svn_pool_clear(ns->pool);
    }
  SVN_ERR(ensure_state(eb, svn_dirent_dirname(local_abspath, scratch_pool),
                       FALSE, scratch_pool));

  if (eb->cur && eb->cur->skip_children)
    return SVN_NO_ERROR;

  /* This code does about the same thing as the inner body of
     walk_local_nodes_diff() in diff_editor.c, except that
     it is already filtered by the status walker, doesn't have to
     account for remote changes (and many tiny other details) */

  {
    svn_boolean_t repos_only;
    svn_boolean_t local_only;
    svn_wc__db_status_t db_status;
    svn_boolean_t have_base;
    svn_node_kind_t base_kind;
    svn_node_kind_t db_kind = status->kind;
    svn_depth_t depth_below_here = svn_depth_unknown;

    const char *child_abspath = local_abspath;
    const char *child_relpath = svn_dirent_skip_ancestor(eb->anchor_abspath,
                                                         local_abspath);


    repos_only = FALSE;
    local_only = FALSE;

    /* ### optimize away this call using status info. Should
           be possible in almost every case (except conflict, missing, obst.)*/
    SVN_ERR(svn_wc__db_read_info(&db_status, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL,
                                 &have_base, NULL, NULL,
                                 eb->db, local_abspath,
                                 scratch_pool, scratch_pool));
    if (!have_base)
      {
        local_only = TRUE; /* Only report additions */
      }
    else if (db_status == svn_wc__db_status_normal
             || db_status == svn_wc__db_status_incomplete)
      {
        /* Simple diff */
        base_kind = db_kind;
      }
    else if (db_status == svn_wc__db_status_deleted)
      {
        svn_wc__db_status_t base_status;
        repos_only = TRUE;
        SVN_ERR(svn_wc__db_base_get_info(&base_status, &base_kind, NULL,
                                         NULL, NULL, NULL, NULL, NULL,
                                         NULL, NULL, NULL, NULL, NULL,
                                         NULL, NULL, NULL,
                                         eb->db, local_abspath,
                                         scratch_pool, scratch_pool));

        if (base_status != svn_wc__db_status_normal
            && base_status != svn_wc__db_status_incomplete)
          return SVN_NO_ERROR;
      }
    else
      {
        /* working status is either added or deleted */
        svn_wc__db_status_t base_status;

        SVN_ERR(svn_wc__db_base_get_info(&base_status, &base_kind, NULL,
                                         NULL, NULL, NULL, NULL, NULL,
                                         NULL, NULL, NULL, NULL, NULL,
                                         NULL, NULL, NULL,
                                         eb->db, local_abspath,
                                         scratch_pool, scratch_pool));

        if (base_status != svn_wc__db_status_normal
            && base_status != svn_wc__db_status_incomplete)
          local_only = TRUE;
        else if (base_kind != db_kind || !eb->ignore_ancestry)
          {
            repos_only = TRUE;
            local_only = TRUE;
          }
      }

    if (repos_only)
      {
        /* Report repository form deleted */
        if (base_kind == svn_node_file)
          SVN_ERR(svn_wc__diff_base_only_file(db, child_abspath,
                                              child_relpath,
                                              SVN_INVALID_REVNUM,
                                              eb->processor,
                                              eb->cur ? eb->cur->baton : NULL,
                                              scratch_pool));
        else if (base_kind == svn_node_dir)
          SVN_ERR(svn_wc__diff_base_only_dir(db, child_abspath,
                                             child_relpath,
                                             SVN_INVALID_REVNUM,
                                             depth_below_here,
                                             eb->processor,
                                             eb->cur ? eb->cur->baton : NULL,
                                             eb->cancel_func,
                                             eb->cancel_baton,
                                             scratch_pool));
      }
    else if (!local_only)
      {
        /* Diff base against actual */
        if (db_kind == svn_node_file)
          {
            SVN_ERR(svn_wc__diff_base_working_diff(db, child_abspath,
                                                   child_relpath,
                                                   SVN_INVALID_REVNUM,
                                                   eb->processor,
                                                   eb->cur
                                                        ? eb->cur->baton
                                                        : NULL,
                                                   FALSE,
                                                   eb->cancel_func,
                                                   eb->cancel_baton,
                                                   scratch_pool));
          }
        else if (db_kind == svn_node_dir)
          {
            SVN_ERR(ensure_state(eb, local_abspath, FALSE, scratch_pool));

            if (status->prop_status != svn_wc_status_none
                && status->prop_status != svn_wc_status_normal)
              {
                apr_array_header_t *propchanges;
                SVN_ERR(svn_wc__db_base_get_props(&eb->cur->left_props,
                                                  eb->db, local_abspath,
                                                  eb->cur->pool,
                                                  scratch_pool));
                SVN_ERR(svn_wc__db_read_props(&eb->cur->right_props,
                                              eb->db, local_abspath,
                                              eb->cur->pool,
                                              scratch_pool));

                SVN_ERR(svn_prop_diffs(&propchanges,
                                       eb->cur->right_props,
                                       eb->cur->left_props,
                                       eb->cur->pool));

                eb->cur->propchanges = propchanges;
              }
          }
      }

    if (local_only && (db_status != svn_wc__db_status_deleted))
      {
        /* Moved from. Relative from diff anchor*/
        const char *moved_from_relpath = NULL;

        if (status->moved_from_abspath)
          {
            moved_from_relpath = svn_dirent_skip_ancestor(
                                          eb->anchor_abspath,
                                          status->moved_from_abspath);
          }

        if (db_kind == svn_node_file)
          SVN_ERR(svn_wc__diff_local_only_file(db, child_abspath,
                                               child_relpath,
                                               moved_from_relpath,
                                               eb->processor,
                                               eb->cur ? eb->cur->baton : NULL,
                                               FALSE,
                                               eb->cancel_func,
                                               eb->cancel_baton,
                                               scratch_pool));
        else if (db_kind == svn_node_dir)
          SVN_ERR(svn_wc__diff_local_only_dir(db, child_abspath,
                                              child_relpath, depth_below_here,
                                              moved_from_relpath,
                                              eb->processor,
                                              eb->cur ? eb->cur->baton : NULL,
                                              FALSE,
                                              eb->cancel_func,
                                              eb->cancel_baton,
                                              scratch_pool));
      }

    if (db_kind == svn_node_dir && (local_only || repos_only))
      SVN_ERR(ensure_state(eb, local_abspath, TRUE /* skip */, scratch_pool));
  }

  return SVN_NO_ERROR;
}