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
typedef  int /*<<< orphan*/  svn_wc_revision_status_t ;
typedef  int /*<<< orphan*/  svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc_context_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_context_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_revision_status2 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_revision_status(svn_wc_revision_status_t **result_p,
                       const char *wc_path,
                       const char *trail_url,
                       svn_boolean_t committed,
                       svn_cancel_func_t cancel_func,
                       void *cancel_baton,
                       apr_pool_t *pool)
{
  svn_wc_context_t *wc_ctx;
  const char *local_abspath;

  SVN_ERR(svn_dirent_get_absolute(&local_abspath, wc_path, pool));
  SVN_ERR(svn_wc_context_create(&wc_ctx, NULL /* config */, pool, pool));

  SVN_ERR(svn_wc_revision_status2(result_p, wc_ctx, local_abspath, trail_url,
                                  committed, cancel_func, cancel_baton, pool,
                                  pool));

  return svn_error_trace(svn_wc_context_destroy(wc_ctx));
}