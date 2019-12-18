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
typedef  int /*<<< orphan*/  svn_opt_revision_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_diff_summarize_func_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_DEPTH_INFINITY_OR_FILES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_client_diff_summarize_peg2 (char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client_diff_summarize_peg(const char *path,
                              const svn_opt_revision_t *peg_revision,
                              const svn_opt_revision_t *start_revision,
                              const svn_opt_revision_t *end_revision,
                              svn_boolean_t recurse,
                              svn_boolean_t ignore_ancestry,
                              svn_client_diff_summarize_func_t summarize_func,
                              void *summarize_baton,
                              svn_client_ctx_t *ctx,
                              apr_pool_t *pool)
{
  return svn_client_diff_summarize_peg2(path, peg_revision,
                                        start_revision, end_revision,
                                        SVN_DEPTH_INFINITY_OR_FILES(recurse),
                                        ignore_ancestry, NULL,
                                        summarize_func, summarize_baton,
                                        ctx, pool);
}