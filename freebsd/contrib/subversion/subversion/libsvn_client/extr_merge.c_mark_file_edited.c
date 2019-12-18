#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  prop_state; int /*<<< orphan*/  content_state; int /*<<< orphan*/  kind; } ;
typedef  TYPE_4__ svn_wc_notify_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct merge_file_baton_t {scalar_t__ tree_conflict_reason; int /*<<< orphan*/  tree_conflict_action; int /*<<< orphan*/  tree_conflict_merge_right_node_kind; int /*<<< orphan*/  tree_conflict_merge_left_node_kind; int /*<<< orphan*/  tree_conflict_local_node_kind; TYPE_9__* parent_baton; int /*<<< orphan*/  skip_reason; int /*<<< orphan*/  shadowed; void* edited; } ;
struct TYPE_16__ {scalar_t__ ancestral; } ;
struct TYPE_18__ {int /*<<< orphan*/  skipped_abspaths; scalar_t__ reintegrate_merge; TYPE_3__ merge_source; TYPE_2__* ctx; } ;
typedef  TYPE_5__ merge_cmd_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_19__ {TYPE_1__* delete_state; int /*<<< orphan*/  edited; } ;
struct TYPE_15__ {int /*<<< orphan*/  notify_baton2; int /*<<< orphan*/  (* notify_func2 ) (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_14__ {void* found_edit; } ;

/* Variables and functions */
 scalar_t__ CONFLICT_REASON_NONE ; 
 scalar_t__ CONFLICT_REASON_SKIP ; 
 scalar_t__ CONFLICT_REASON_SKIP_WC ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 void* TRUE ; 
 int /*<<< orphan*/  mark_dir_edited (TYPE_5__*,TYPE_9__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notify_merge_begin (TYPE_5__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  record_tree_conflict (TYPE_5__*,char const*,TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  store_path (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_node_file ; 
 TYPE_4__* svn_wc_create_notify (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_skip ; 

__attribute__((used)) static svn_error_t *
mark_file_edited(merge_cmd_baton_t *merge_b,
                 struct merge_file_baton_t *fb,
                 const char *local_abspath,
                 apr_pool_t *scratch_pool)
{
  /* ### Too much common code with mark_dir_edited */
  if (fb->edited)
    return SVN_NO_ERROR;

  if (fb->parent_baton && !fb->parent_baton->edited)
    {
      const char *dir_abspath = svn_dirent_dirname(local_abspath,
                                                   scratch_pool);

      SVN_ERR(mark_dir_edited(merge_b, fb->parent_baton, dir_abspath,
                              scratch_pool));
    }

  fb->edited = TRUE;

  if (! fb->shadowed)
    return SVN_NO_ERROR; /* Easy out */

  if (fb->parent_baton
      && fb->parent_baton->delete_state
      && fb->tree_conflict_reason != CONFLICT_REASON_NONE)
    {
      fb->parent_baton->delete_state->found_edit = TRUE;
    }
  else if (fb->tree_conflict_reason == CONFLICT_REASON_SKIP
           || fb->tree_conflict_reason == CONFLICT_REASON_SKIP_WC)
    {
      /* open_directory() decided not to flag a tree conflict, but
         for clarity we produce a skip for this node that
         most likely isn't touched by the merge itself */

      if (merge_b->ctx->notify_func2)
        {
          svn_wc_notify_t *notify;

          SVN_ERR(notify_merge_begin(merge_b, local_abspath, FALSE,
                                     scratch_pool));

          notify = svn_wc_create_notify(local_abspath, svn_wc_notify_skip,
                                        scratch_pool);
          notify->kind = svn_node_file;
          notify->content_state = notify->prop_state = fb->skip_reason;

          merge_b->ctx->notify_func2(merge_b->ctx->notify_baton2,
                                     notify,
                                     scratch_pool);
        }

      if (merge_b->merge_source.ancestral
          || merge_b->reintegrate_merge)
        {
          store_path(merge_b->skipped_abspaths, local_abspath);
        }
    }
  else if (fb->tree_conflict_reason != CONFLICT_REASON_NONE)
    {
      /* open_file() decided that a tree conflict should be raised */

      SVN_ERR(record_tree_conflict(merge_b, local_abspath, fb->parent_baton,
                                   fb->tree_conflict_local_node_kind,
                                   fb->tree_conflict_merge_left_node_kind,
                                   fb->tree_conflict_merge_right_node_kind,
                                   fb->tree_conflict_action,
                                   fb->tree_conflict_reason,
                                   NULL, TRUE,
                                   scratch_pool));
    }

  return SVN_NO_ERROR;
}