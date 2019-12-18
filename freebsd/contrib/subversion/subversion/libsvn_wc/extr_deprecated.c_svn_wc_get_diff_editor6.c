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
typedef  int /*<<< orphan*/  svn_wc_diff_callbacks4_t ;
typedef  int /*<<< orphan*/  svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_diff_tree_processor_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_delta_editor_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/ * svn_diff__tree_processor_copy_as_changed_create (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_diff__tree_processor_reverse_create (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__get_diff_editor (int /*<<< orphan*/  const**,void**,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__wrap_diff_callbacks (int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,void*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_get_diff_editor6(const svn_delta_editor_t **editor,
                        void **edit_baton,
                        svn_wc_context_t *wc_ctx,
                        const char *anchor_abspath,
                        const char *target,
                        svn_depth_t depth,
                        svn_boolean_t ignore_ancestry,
                        svn_boolean_t show_copies_as_adds,
                        svn_boolean_t use_git_diff_format,
                        svn_boolean_t use_text_base,
                        svn_boolean_t reverse_order,
                        svn_boolean_t server_performs_filtering,
                        const apr_array_header_t *changelist_filter,
                        const svn_wc_diff_callbacks4_t *callbacks,
                        void *callback_baton,
                        svn_cancel_func_t cancel_func,
                        void *cancel_baton,
                        apr_pool_t *result_pool,
                        apr_pool_t *scratch_pool)
{
  const svn_diff_tree_processor_t *diff_processor;

  /* --git implies --show-copies-as-adds */
  if (use_git_diff_format)
    show_copies_as_adds = TRUE;

  /* --show-copies-as-adds implies --notice-ancestry */
  if (show_copies_as_adds)
    ignore_ancestry = FALSE;

  SVN_ERR(svn_wc__wrap_diff_callbacks(&diff_processor,
                                      callbacks, callback_baton, TRUE,
                                      result_pool, scratch_pool));

  if (reverse_order)
    diff_processor = svn_diff__tree_processor_reverse_create(
                              diff_processor, NULL, result_pool);

  if (! show_copies_as_adds)
    diff_processor = svn_diff__tree_processor_copy_as_changed_create(
                              diff_processor, result_pool);

  return svn_error_trace(
    svn_wc__get_diff_editor(editor, edit_baton,
                            wc_ctx,
                            anchor_abspath, target,
                            depth,
                            ignore_ancestry, use_text_base,
                            reverse_order, server_performs_filtering,
                            changelist_filter,
                            diff_processor,
                            cancel_func, cancel_baton,
                            result_pool, scratch_pool));
}