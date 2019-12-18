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
typedef  int /*<<< orphan*/  svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  scan_addition (int /*<<< orphan*/ *,char const**,char const**,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 

svn_error_t *
svn_wc__db_scan_addition_internal(
              svn_wc__db_status_t *status,
              const char **op_root_relpath_p,
              const char **repos_relpath,
              apr_int64_t *repos_id,
              const char **original_repos_relpath,
              apr_int64_t *original_repos_id,
              svn_revnum_t *original_revision,
              svn_wc__db_wcroot_t *wcroot,
              const char *local_relpath,
              apr_pool_t *result_pool,
              apr_pool_t *scratch_pool)
{
  return svn_error_trace(
      scan_addition(status, op_root_relpath_p, repos_relpath, repos_id,
                    original_repos_relpath, original_repos_id,
                    original_revision, NULL, NULL, NULL,
                    wcroot, local_relpath, result_pool, scratch_pool));
}