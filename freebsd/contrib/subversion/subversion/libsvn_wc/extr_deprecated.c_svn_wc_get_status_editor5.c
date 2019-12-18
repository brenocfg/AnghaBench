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
typedef  int /*<<< orphan*/  svn_wc_status_func4_t ;
typedef  int /*<<< orphan*/  svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_delta_editor_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__get_status_editor (int /*<<< orphan*/  const**,void**,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_get_status_editor5(const svn_delta_editor_t **editor,
                          void **edit_baton,
                          void **set_locks_baton,
                          svn_revnum_t *edit_revision,
                          svn_wc_context_t *wc_ctx,
                          const char *anchor_abspath,
                          const char *target_basename,
                          svn_depth_t depth,
                          svn_boolean_t get_all,
                          svn_boolean_t no_ignore,
                          svn_boolean_t depth_as_sticky,
                          svn_boolean_t server_performs_filtering,
                          const apr_array_header_t *ignore_patterns,
                          svn_wc_status_func4_t status_func,
                          void *status_baton,
                          svn_cancel_func_t cancel_func,
                          void *cancel_baton,
                          apr_pool_t *result_pool,
                          apr_pool_t *scratch_pool)
{
  return svn_error_trace(
    svn_wc__get_status_editor(editor, edit_baton,
                              set_locks_baton,
                              edit_revision,
                              wc_ctx,
                              anchor_abspath,
                              target_basename,
                              depth, get_all,
                              TRUE, /* check_working_copy */
                              no_ignore, depth_as_sticky,
                              server_performs_filtering,
                              ignore_patterns,
                              status_func, status_baton,
                              cancel_func, cancel_baton,
                              result_pool,
                              scratch_pool));
}