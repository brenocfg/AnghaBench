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
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/ * svn_diff__tree_processor_copy_as_changed_create (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__diff7 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__wrap_diff_callbacks (int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,void*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_diff6(svn_wc_context_t *wc_ctx,
             const char *local_abspath,
             const svn_wc_diff_callbacks4_t *callbacks,
             void *callback_baton,
             svn_depth_t depth,
             svn_boolean_t ignore_ancestry,
             svn_boolean_t show_copies_as_adds,
             svn_boolean_t use_git_diff_format,
             const apr_array_header_t *changelist_filter,
             svn_cancel_func_t cancel_func,
             void *cancel_baton,
             apr_pool_t *scratch_pool)
{
  const svn_diff_tree_processor_t *processor;

  SVN_ERR(svn_wc__wrap_diff_callbacks(&processor,
                                      callbacks, callback_baton, TRUE,
                                      scratch_pool, scratch_pool));

  if (use_git_diff_format)
    show_copies_as_adds = TRUE;
  if (show_copies_as_adds)
    ignore_ancestry = FALSE;

  if (! show_copies_as_adds && !use_git_diff_format)
    processor = svn_diff__tree_processor_copy_as_changed_create(processor,
                                                                scratch_pool);

  return svn_error_trace(svn_wc__diff7(NULL, NULL,
                                       wc_ctx, local_abspath,
                                       depth,
                                       ignore_ancestry,
                                       changelist_filter,
                                       processor,
                                       cancel_func, cancel_baton,
                                       scratch_pool, scratch_pool));
}