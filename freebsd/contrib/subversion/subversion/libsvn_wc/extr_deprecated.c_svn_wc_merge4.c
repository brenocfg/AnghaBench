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
typedef  int /*<<< orphan*/  svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_wc_conflict_version_t ;
typedef  int /*<<< orphan*/  svn_wc_conflict_resolver_func2_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  enum svn_wc_merge_outcome_t { ____Placeholder_svn_wc_merge_outcome_t } svn_wc_merge_outcome_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc_merge5 (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*,char const*,char const*,char const*,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_merge4(enum svn_wc_merge_outcome_t *merge_outcome,
              svn_wc_context_t *wc_ctx,
              const char *left_abspath,
              const char *right_abspath,
              const char *target_abspath,
              const char *left_label,
              const char *right_label,
              const char *target_label,
              const svn_wc_conflict_version_t *left_version,
              const svn_wc_conflict_version_t *right_version,
              svn_boolean_t dry_run,
              const char *diff3_cmd,
              const apr_array_header_t *merge_options,
              const apr_array_header_t *prop_diff,
              svn_wc_conflict_resolver_func2_t conflict_func,
              void *conflict_baton,
              svn_cancel_func_t cancel_func,
              void *cancel_baton,
              apr_pool_t *scratch_pool)
{
  return svn_error_trace(
            svn_wc_merge5(merge_outcome,
                          NULL /* merge_props_outcome */,
                          wc_ctx,
                          left_abspath,
                          right_abspath,
                          target_abspath,
                          left_label,
                          right_label,
                          target_label,
                          left_version,
                          right_version,
                          dry_run,
                          diff3_cmd,
                          merge_options,
                          NULL /* original_props */,
                          prop_diff,
                          conflict_func, conflict_baton,
                          cancel_func, cancel_baton,
                          scratch_pool));
}