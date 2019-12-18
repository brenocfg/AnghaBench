#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  lock_state; int /*<<< orphan*/  prop_state; int /*<<< orphan*/  content_state; int /*<<< orphan*/  kind; } ;
typedef  TYPE_1__ svn_wc_notify_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
struct TYPE_15__ {int /*<<< orphan*/  (* close_directory ) (void*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* add_directory ) (char const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ;} ;
typedef  TYPE_2__ svn_delta_editor_t ;
typedef  int /*<<< orphan*/  svn_client_import_filter_func_t ;
struct TYPE_16__ {int /*<<< orphan*/  notify_baton2; int /*<<< orphan*/  (* notify_func2 ) (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_3__ svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_17__ {int /*<<< orphan*/  repos_changed; } ;
typedef  TYPE_4__ import_ctx_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  get_filtered_children (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  import_children (char const*,char const*,int /*<<< orphan*/ *,TYPE_2__ const*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (char const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_node_dir ; 
 int /*<<< orphan*/  svn_path_check_valid (char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc_create_notify (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_commit_added ; 
 int /*<<< orphan*/  svn_wc_notify_lock_state_inapplicable ; 
 int /*<<< orphan*/  svn_wc_notify_state_inapplicable ; 

__attribute__((used)) static svn_error_t *
import_dir(const svn_delta_editor_t *editor,
           void *dir_baton,
           const char *local_abspath,
           const char *edit_path,
           svn_depth_t depth,
           apr_hash_t *excludes,
           apr_array_header_t *global_ignores,
           svn_boolean_t no_ignore,
           svn_boolean_t no_autoprops,
           svn_boolean_t ignore_unknown_node_types,
           svn_client_import_filter_func_t filter_callback,
           void *filter_baton,
           import_ctx_t *import_ctx,
           svn_client_ctx_t *ctx,
           apr_pool_t *pool)
{
  apr_hash_t *dirents;
  void *this_dir_baton;

  SVN_ERR(svn_path_check_valid(local_abspath, pool));
  SVN_ERR(get_filtered_children(&dirents, local_abspath, excludes, NULL,
                                global_ignores, filter_callback,
                                filter_baton, ctx, pool, pool));

  /* Import this directory, but not yet its children. */
  {
    /* Add the new subdirectory, getting a descent baton from the editor. */
    SVN_ERR(editor->add_directory(edit_path, dir_baton, NULL,
                                  SVN_INVALID_REVNUM, pool, &this_dir_baton));

    /* Remember that the repository was modified */
    import_ctx->repos_changed = TRUE;

    /* By notifying before the recursive call below, we display
       a directory add before displaying adds underneath the
       directory.  To do it the other way around, just move this
       after the recursive call. */
    if (ctx->notify_func2)
      {
        svn_wc_notify_t *notify
          = svn_wc_create_notify(local_abspath, svn_wc_notify_commit_added,
                                 pool);
        notify->kind = svn_node_dir;
        notify->content_state = notify->prop_state
          = svn_wc_notify_state_inapplicable;
        notify->lock_state = svn_wc_notify_lock_state_inapplicable;
        ctx->notify_func2(ctx->notify_baton2, notify, pool);
      }
  }

  /* Now import the children recursively. */
  SVN_ERR(import_children(local_abspath, edit_path, dirents, editor,
                          this_dir_baton, depth, excludes, global_ignores,
                          no_ignore, no_autoprops, ignore_unknown_node_types,
                          filter_callback, filter_baton,
                          import_ctx, ctx, pool));

  /* Finally, close the sub-directory. */
  SVN_ERR(editor->close_directory(this_dir_baton, pool));

  return SVN_NO_ERROR;
}