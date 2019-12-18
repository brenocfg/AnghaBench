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
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc_context_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_context_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_get_pristine_contents2 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_get_pristine_contents(svn_stream_t **contents,
                             const char *path,
                             apr_pool_t *result_pool,
                             apr_pool_t *scratch_pool)
{
  svn_wc_context_t *wc_ctx;
  const char *local_abspath;

  SVN_ERR(svn_wc_context_create(&wc_ctx, NULL, scratch_pool, scratch_pool));
  SVN_ERR(svn_dirent_get_absolute(&local_abspath, path, scratch_pool));

  SVN_ERR(svn_wc_get_pristine_contents2(contents,
                                        wc_ctx,
                                        local_abspath,
                                        result_pool,
                                        scratch_pool));

  return svn_error_trace(svn_wc_context_destroy(wc_ctx));
}