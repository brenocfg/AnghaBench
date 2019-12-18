#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  kind; int /*<<< orphan*/  prop_state; int /*<<< orphan*/  content_state; } ;
typedef  TYPE_1__ svn_wc_notify_t ;
typedef  int /*<<< orphan*/  svn_wc_notify_state_t ;
typedef  scalar_t__ svn_wc_merge_outcome_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_7__ {int /*<<< orphan*/  notify_baton2; int /*<<< orphan*/  (* notify_func2 ) (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_2__ svn_client_ctx_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_file_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_del_on_pool_cleanup ; 
 int /*<<< orphan*/  svn_io_open_unique_file3 (int /*<<< orphan*/ **,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_node_file ; 
 int /*<<< orphan*/  svn_prop_diffs (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc_create_notify (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_merge5 (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc_merge_conflict ; 
 int /*<<< orphan*/  svn_wc_notify_state_conflicted ; 
 int /*<<< orphan*/  svn_wc_notify_state_merged ; 
 int /*<<< orphan*/  svn_wc_notify_update_update ; 
 int /*<<< orphan*/  svn_wc_prop_list2 (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
merge_added_files(const char *local_abspath,
                  const char *incoming_added_file_abspath,
                  apr_hash_t *incoming_added_file_props,
                  svn_client_ctx_t *ctx,
                  apr_pool_t *scratch_pool)
{
  svn_wc_merge_outcome_t merge_content_outcome;
  svn_wc_notify_state_t merge_props_outcome;
  apr_file_t *empty_file;
  const char *empty_file_abspath;
  apr_array_header_t *propdiffs;
  apr_hash_t *working_props;

  /* Create an empty file as fake "merge-base" for the two added files.
   * The files are not ancestrally related so this is the best we can do. */
  SVN_ERR(svn_io_open_unique_file3(&empty_file, &empty_file_abspath, NULL,
                                   svn_io_file_del_on_pool_cleanup,
                                   scratch_pool, scratch_pool));

  /* Get a copy of the working file's properties. */
  SVN_ERR(svn_wc_prop_list2(&working_props, ctx->wc_ctx, local_abspath,
                            scratch_pool, scratch_pool));

  /* Create a property diff for the files. */
  SVN_ERR(svn_prop_diffs(&propdiffs, incoming_added_file_props,
                         working_props, scratch_pool));

  /* Perform the file merge. */
  SVN_ERR(svn_wc_merge5(&merge_content_outcome, &merge_props_outcome,
                        ctx->wc_ctx, empty_file_abspath,
                        incoming_added_file_abspath, local_abspath,
                        NULL, NULL, NULL, /* labels */
                        NULL, NULL, /* conflict versions */
                        FALSE, /* dry run */
                        NULL, NULL, /* diff3_cmd, merge_options */
                        NULL, propdiffs,
                        NULL, NULL, /* conflict func/baton */
                        NULL, NULL, /* don't allow user to cancel here */
                        scratch_pool));

  if (ctx->notify_func2)
    {
      svn_wc_notify_t *notify = svn_wc_create_notify(
                                   local_abspath,
                                   svn_wc_notify_update_update,
                                   scratch_pool);

      if (merge_content_outcome == svn_wc_merge_conflict)
        notify->content_state = svn_wc_notify_state_conflicted;
      else
        notify->content_state = svn_wc_notify_state_merged;
      notify->prop_state = merge_props_outcome;
      notify->kind = svn_node_file;
      ctx->notify_func2(ctx->notify_baton2, notify, scratch_pool);
    }

  return SVN_NO_ERROR;
}