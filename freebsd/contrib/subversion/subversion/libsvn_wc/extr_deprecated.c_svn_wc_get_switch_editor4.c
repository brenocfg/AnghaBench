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
typedef  int /*<<< orphan*/  svn_wc_notify_func2_t ;
typedef  int /*<<< orphan*/  svn_wc_external_update_t ;
typedef  int /*<<< orphan*/  svn_wc_dirents_func_t ;
typedef  int /*<<< orphan*/  svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_wc_conflict_resolver_func2_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_delta_editor_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__get_switch_editor (int /*<<< orphan*/  const**,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_get_switch_editor4(const svn_delta_editor_t **editor,
                          void **edit_baton,
                          svn_revnum_t *target_revision,
                          svn_wc_context_t *wc_ctx,
                          const char *anchor_abspath,
                          const char *target_basename,
                          const char *switch_url,
                          svn_boolean_t use_commit_times,
                          svn_depth_t depth,
                          svn_boolean_t depth_is_sticky,
                          svn_boolean_t allow_unver_obstructions,
                          svn_boolean_t server_performs_filtering,
                          const char *diff3_cmd,
                          const apr_array_header_t *preserved_exts,
                          svn_wc_dirents_func_t fetch_dirents_func,
                          void *fetch_dirents_baton,
                          svn_wc_conflict_resolver_func2_t conflict_func,
                          void *conflict_baton,
                          svn_wc_external_update_t external_func,
                          void *external_baton,
                          svn_cancel_func_t cancel_func,
                          void *cancel_baton,
                          svn_wc_notify_func2_t notify_func,
                          void *notify_baton,
                          apr_pool_t *result_pool,
                          apr_pool_t *scratch_pool)
{
  return svn_error_trace(
    svn_wc__get_switch_editor(editor, edit_baton,
                              target_revision,
                              wc_ctx,
                              anchor_abspath, target_basename,
                              switch_url, NULL,
                              use_commit_times,
                              depth, depth_is_sticky,
                              allow_unver_obstructions,
                              server_performs_filtering,
                              diff3_cmd,
                              preserved_exts,
                              fetch_dirents_func, fetch_dirents_baton,
                              conflict_func, conflict_baton,
                              external_func, external_baton,
                              cancel_func, cancel_baton,
                              notify_func, notify_baton,
                              result_pool, scratch_pool));
}