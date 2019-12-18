#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_12__ ;

/* Type definitions */
typedef  scalar_t__ svn_wc_notify_state_t ;
typedef  int /*<<< orphan*/  svn_wc_conflict_version_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_diff_source_t ;
struct TYPE_15__ {int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_1__ svn_client_ctx_t ;
struct svn_diff_tree_processor_t {TYPE_2__* baton; } ;
struct merge_dir_baton_t {scalar_t__ tree_conflict_reason; int /*<<< orphan*/  parent_baton; int /*<<< orphan*/  skip_reason; scalar_t__ shadowed; } ;
struct TYPE_16__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  conflicted_paths; int /*<<< orphan*/  dry_run; TYPE_12__* target; int /*<<< orphan*/  merge_source; TYPE_1__* ctx; } ;
typedef  TYPE_2__ merge_cmd_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_17__ {scalar_t__ nelts; } ;
typedef  TYPE_3__ apr_array_header_t ;
struct TYPE_14__ {int /*<<< orphan*/  abspath; } ;

/* Variables and functions */
 scalar_t__ CONFLICT_REASON_NONE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  alloc_and_store_path (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_pending_notifications (TYPE_2__*,struct merge_dir_baton_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_conflict_versions (int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_12__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mark_dir_edited (TYPE_2__*,struct merge_dir_baton_t*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_merge_props_changed (TYPE_3__ const**,char const*,TYPE_3__ const*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  record_skip (TYPE_2__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  record_update_update (TYPE_2__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_node_dir ; 
 int /*<<< orphan*/  svn_node_file ; 
 int /*<<< orphan*/  svn_wc_merge_props3 (scalar_t__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,TYPE_3__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc_notify_state_changed ; 
 scalar_t__ svn_wc_notify_state_conflicted ; 
 int /*<<< orphan*/  svn_wc_notify_state_inapplicable ; 
 scalar_t__ svn_wc_notify_state_merged ; 
 int /*<<< orphan*/  svn_wc_notify_update_shadowed_update ; 

__attribute__((used)) static svn_error_t *
merge_dir_changed(const char *relpath,
                  const svn_diff_source_t *left_source,
                  const svn_diff_source_t *right_source,
                  /*const*/ apr_hash_t *left_props,
                  /*const*/ apr_hash_t *right_props,
                  const apr_array_header_t *prop_changes,
                  void *dir_baton,
                  const struct svn_diff_tree_processor_t *processor,
                  apr_pool_t *scratch_pool)
{
  merge_cmd_baton_t *merge_b = processor->baton;
  struct merge_dir_baton_t *db = dir_baton;
  const apr_array_header_t *props;
  const char *local_abspath = svn_dirent_join(merge_b->target->abspath,
                                              relpath, scratch_pool);

  SVN_ERR(handle_pending_notifications(merge_b, db, scratch_pool));

  SVN_ERR(mark_dir_edited(merge_b, db, local_abspath, scratch_pool));

  if (db->shadowed)
    {
      if (db->tree_conflict_reason == CONFLICT_REASON_NONE)
        {
          /* We haven't notified for this node yet: report a skip */
          SVN_ERR(record_skip(merge_b, local_abspath, svn_node_dir,
                              svn_wc_notify_update_shadowed_update,
                              db->skip_reason, db->parent_baton,
                              scratch_pool));
        }

      return SVN_NO_ERROR;
    }

  SVN_ERR(prepare_merge_props_changed(&props, local_abspath, prop_changes,
                                      merge_b, scratch_pool, scratch_pool));

  if (props->nelts)
    {
      const svn_wc_conflict_version_t *left;
      const svn_wc_conflict_version_t *right;
      svn_client_ctx_t *ctx = merge_b->ctx;
      svn_wc_notify_state_t prop_state;

      SVN_ERR(make_conflict_versions(&left, &right, local_abspath,
                                     svn_node_dir, svn_node_dir,
                                     &merge_b->merge_source,
                                     merge_b->target,
                                     scratch_pool, scratch_pool));

      SVN_ERR(svn_wc_merge_props3(&prop_state, ctx->wc_ctx, local_abspath,
                                  left, right,
                                  left_props, props,
                                  merge_b->dry_run,
                                  NULL, NULL,
                                  ctx->cancel_func, ctx->cancel_baton,
                                  scratch_pool));

      if (prop_state == svn_wc_notify_state_conflicted)
        {
          alloc_and_store_path(&merge_b->conflicted_paths, local_abspath,
                               merge_b->pool);
        }

      if (prop_state == svn_wc_notify_state_conflicted
          || prop_state == svn_wc_notify_state_merged
          || prop_state == svn_wc_notify_state_changed)
        {
          SVN_ERR(record_update_update(merge_b, local_abspath, svn_node_file,
                                       svn_wc_notify_state_inapplicable,
                                       prop_state, scratch_pool));
        }
    }

  return SVN_NO_ERROR;
}