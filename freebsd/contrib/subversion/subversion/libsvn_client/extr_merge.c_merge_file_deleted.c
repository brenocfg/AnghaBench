#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_diff_source_t ;
typedef  void* svn_boolean_t ;
struct svn_diff_tree_processor_t {TYPE_4__* baton; } ;
struct merge_file_baton_t {scalar_t__ tree_conflict_reason; TYPE_6__* parent_baton; int /*<<< orphan*/  skip_reason; scalar_t__ shadowed; } ;
struct TYPE_15__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  paths_with_deleted_mergeinfo; TYPE_3__* ctx; int /*<<< orphan*/  dry_run; scalar_t__ force_delete; scalar_t__ record_only; TYPE_1__* target; } ;
typedef  TYPE_4__ merge_cmd_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_16__ {TYPE_2__* delete_state; } ;
struct TYPE_14__ {int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; int /*<<< orphan*/  wc_ctx; } ;
struct TYPE_13__ {void* found_edit; int /*<<< orphan*/  compared_abspaths; } ;
struct TYPE_12__ {int /*<<< orphan*/  abspath; } ;

/* Variables and functions */
 scalar_t__ CONFLICT_REASON_NONE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 void* TRUE ; 
 int /*<<< orphan*/  alloc_and_store_path (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  files_same_p (void**,char const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mark_file_edited (TYPE_4__*,struct merge_file_baton_t*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  record_skip (TYPE_4__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  record_tree_conflict (TYPE_4__*,char const*,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  record_update_delete (TYPE_4__*,TYPE_6__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  store_path (int /*<<< orphan*/ ,char const*) ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_node_file ; 
 int /*<<< orphan*/  svn_node_none ; 
 int /*<<< orphan*/  svn_wc_conflict_action_delete ; 
 int /*<<< orphan*/  svn_wc_conflict_reason_edited ; 
 int /*<<< orphan*/  svn_wc_delete4 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_update_shadowed_delete ; 

__attribute__((used)) static svn_error_t *
merge_file_deleted(const char *relpath,
                   const svn_diff_source_t *left_source,
                   const char *left_file,
                   /*const*/ apr_hash_t *left_props,
                   void *file_baton,
                   const struct svn_diff_tree_processor_t *processor,
                   apr_pool_t *scratch_pool)
{
  merge_cmd_baton_t *merge_b = processor->baton;
  struct merge_file_baton_t *fb = file_baton;
  const char *local_abspath = svn_dirent_join(merge_b->target->abspath,
                                              relpath, scratch_pool);
  svn_boolean_t same;

  SVN_ERR(mark_file_edited(merge_b, fb, local_abspath, scratch_pool));

  if (fb->shadowed)
    {
      if (fb->tree_conflict_reason == CONFLICT_REASON_NONE)
        {
          /* We haven't notified for this node yet: report a skip */
          SVN_ERR(record_skip(merge_b, local_abspath, svn_node_file,
                              svn_wc_notify_update_shadowed_delete,
                              fb->skip_reason, fb->parent_baton,
                              scratch_pool));
        }

      return SVN_NO_ERROR;
    }

  /* Easy out: We are only applying mergeinfo differences. */
  if (merge_b->record_only)
    {
      return SVN_NO_ERROR;
    }

  /* If the files are identical, attempt deletion */
  if (merge_b->force_delete)
    same = TRUE;
  else
    SVN_ERR(files_same_p(&same, left_file, left_props,
                         local_abspath, merge_b->ctx->wc_ctx,
                         scratch_pool));

  if (fb->parent_baton
      && fb->parent_baton->delete_state)
    {
      if (same)
        {
          /* Note that we checked this file */
          store_path(fb->parent_baton->delete_state->compared_abspaths,
                     local_abspath);
        }
      else
        {
          /* We found some modification. Parent should raise a tree conflict */
          fb->parent_baton->delete_state->found_edit = TRUE;
        }

      return SVN_NO_ERROR;
    }
  else if (same)
    {
      if (!merge_b->dry_run)
        SVN_ERR(svn_wc_delete4(merge_b->ctx->wc_ctx, local_abspath,
                               FALSE /* keep_local */, FALSE /* unversioned */,
                               merge_b->ctx->cancel_func,
                               merge_b->ctx->cancel_baton,
                               NULL, NULL /* no notify */,
                               scratch_pool));

      /* Record that we might have deleted mergeinfo */
      alloc_and_store_path(&merge_b->paths_with_deleted_mergeinfo,
                           local_abspath, merge_b->pool);

      /* And notify the deletion */
      SVN_ERR(record_update_delete(merge_b, fb->parent_baton, local_abspath,
                                   svn_node_file, scratch_pool));
    }
  else
    {
      /* The files differ, so raise a conflict instead of deleting */

      /* This is use case 5 described in the paper attached to issue
       * #2282.  See also notes/tree-conflicts/detection.txt
       */
      SVN_ERR(record_tree_conflict(merge_b, local_abspath, fb->parent_baton,
                                   svn_node_file,
                                   svn_node_file,
                                   svn_node_none,
                                   svn_wc_conflict_action_delete,
                                   svn_wc_conflict_reason_edited,
                                   NULL, TRUE,
                                   scratch_pool));
    }

  return SVN_NO_ERROR;
}