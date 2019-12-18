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
typedef  int /*<<< orphan*/  svn_wc_traversal_info_t ;
typedef  int /*<<< orphan*/  svn_wc_notify_func2_t ;
typedef  int /*<<< orphan*/  svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_ra_reporter3_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  gather_traversal_info (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_wc__adm_get_db (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__context_create_with_db (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_context_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_crawl_revisions5 (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_crawl_revisions4(const char *path,
                        svn_wc_adm_access_t *adm_access,
                        const svn_ra_reporter3_t *reporter,
                        void *report_baton,
                        svn_boolean_t restore_files,
                        svn_depth_t depth,
                        svn_boolean_t honor_depth_exclude,
                        svn_boolean_t depth_compatibility_trick,
                        svn_boolean_t use_commit_times,
                        svn_wc_notify_func2_t notify_func,
                        void *notify_baton,
                        svn_wc_traversal_info_t *traversal_info,
                        apr_pool_t *pool)
{
  svn_wc_context_t *wc_ctx;
  svn_wc__db_t *wc_db = svn_wc__adm_get_db(adm_access);
  const char *local_abspath;

  SVN_ERR(svn_wc__context_create_with_db(&wc_ctx, NULL, wc_db, pool));
  SVN_ERR(svn_dirent_get_absolute(&local_abspath, path, pool));

  SVN_ERR(svn_wc_crawl_revisions5(wc_ctx,
                                  local_abspath,
                                  reporter,
                                  report_baton,
                                  restore_files,
                                  depth,
                                  honor_depth_exclude,
                                  depth_compatibility_trick,
                                  use_commit_times,
                                  NULL /* cancel_func */,
                                  NULL /* cancel_baton */,
                                  notify_func,
                                  notify_baton,
                                  pool));

  if (traversal_info)
    SVN_ERR(gather_traversal_info(wc_ctx, local_abspath, path, depth,
                                  traversal_info, TRUE, FALSE, pool));

  return svn_error_trace(svn_wc_context_destroy(wc_ctx));
}