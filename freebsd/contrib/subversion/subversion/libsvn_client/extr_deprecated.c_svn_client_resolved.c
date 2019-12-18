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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_DEPTH_INFINITY_OR_EMPTY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_client_resolve (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_conflict_choose_merged ; 

svn_error_t *
svn_client_resolved(const char *path,
                    svn_boolean_t recursive,
                    svn_client_ctx_t *ctx,
                    apr_pool_t *pool)
{
  svn_depth_t depth = SVN_DEPTH_INFINITY_OR_EMPTY(recursive);
  return svn_client_resolve(path, depth,
                            svn_wc_conflict_choose_merged, ctx, pool);
}