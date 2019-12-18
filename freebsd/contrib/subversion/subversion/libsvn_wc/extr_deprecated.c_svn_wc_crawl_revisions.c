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
typedef  int /*<<< orphan*/  svn_wc_notify_func_t ;
typedef  int /*<<< orphan*/  svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  svn_ra_reporter_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct wrap_2to1_report_baton {void* baton; int /*<<< orphan*/  const* reporter; } ;
struct compat_notify_baton_t {void* baton; int /*<<< orphan*/  func; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  compat_call_notify_func ; 
 int /*<<< orphan*/ * svn_wc_crawl_revisions2 (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct wrap_2to1_report_baton*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct compat_notify_baton_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wrap_2to1_reporter ; 

svn_error_t *
svn_wc_crawl_revisions(const char *path,
                       svn_wc_adm_access_t *adm_access,
                       const svn_ra_reporter_t *reporter,
                       void *report_baton,
                       svn_boolean_t restore_files,
                       svn_boolean_t recurse,
                       svn_boolean_t use_commit_times,
                       svn_wc_notify_func_t notify_func,
                       void *notify_baton,
                       svn_wc_traversal_info_t *traversal_info,
                       apr_pool_t *pool)
{
  struct wrap_2to1_report_baton wrb;
  struct compat_notify_baton_t nb;

  wrb.reporter = reporter;
  wrb.baton = report_baton;

  nb.func = notify_func;
  nb.baton = notify_baton;

  return svn_wc_crawl_revisions2(path, adm_access, &wrap_2to1_reporter, &wrb,
                                 restore_files, recurse, use_commit_times,
                                 compat_call_notify_func, &nb,
                                 traversal_info,
                                 pool);
}