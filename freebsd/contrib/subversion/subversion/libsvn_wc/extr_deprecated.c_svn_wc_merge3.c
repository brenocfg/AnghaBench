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
typedef  scalar_t__ svn_wc_conflict_resolver_func_t ;
typedef  int /*<<< orphan*/  svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct conflict_func_1to2_baton {void* inner_baton; scalar_t__ inner_func; } ;
typedef  enum svn_wc_merge_outcome_t { ____Placeholder_svn_wc_merge_outcome_t } svn_wc_merge_outcome_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * conflict_func_1to2_wrapper ; 
 int /*<<< orphan*/  svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_path_cstring_to_utf8 (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__adm_get_db (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__context_create_with_db (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_context_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_merge4 (int*,int /*<<< orphan*/ *,char const*,char const*,char const*,char const*,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,struct conflict_func_1to2_baton*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_merge3(enum svn_wc_merge_outcome_t *merge_outcome,
              const char *left,
              const char *right,
              const char *merge_target,
              svn_wc_adm_access_t *adm_access,
              const char *left_label,
              const char *right_label,
              const char *target_label,
              svn_boolean_t dry_run,
              const char *diff3_cmd,
              const apr_array_header_t *merge_options,
              const apr_array_header_t *prop_diff,
              svn_wc_conflict_resolver_func_t conflict_func,
              void *conflict_baton,
              apr_pool_t *pool)
{
  svn_wc_context_t *wc_ctx;
  svn_wc__db_t *db = svn_wc__adm_get_db(adm_access);
  const char *left_abspath, *right_abspath, *target_abspath;
  struct conflict_func_1to2_baton cfw;

  SVN_ERR(svn_dirent_get_absolute(&left_abspath, left, pool));
  SVN_ERR(svn_dirent_get_absolute(&right_abspath, right, pool));
  SVN_ERR(svn_dirent_get_absolute(&target_abspath, merge_target, pool));

  SVN_ERR(svn_wc__context_create_with_db(&wc_ctx, NULL /* config */, db, pool));

  cfw.inner_func = conflict_func;
  cfw.inner_baton = conflict_baton;

  if (diff3_cmd)
    SVN_ERR(svn_path_cstring_to_utf8(&diff3_cmd, diff3_cmd, pool));

  SVN_ERR(svn_wc_merge4(merge_outcome,
                        wc_ctx,
                        left_abspath,
                        right_abspath,
                        target_abspath,
                        left_label,
                        right_label,
                        target_label,
                        NULL,
                        NULL,
                        dry_run,
                        diff3_cmd,
                        merge_options,
                        prop_diff,
                        conflict_func ? conflict_func_1to2_wrapper : NULL,
                        &cfw,
                        NULL, NULL,
                        pool));

  return svn_error_trace(svn_wc_context_destroy(wc_ctx));
}