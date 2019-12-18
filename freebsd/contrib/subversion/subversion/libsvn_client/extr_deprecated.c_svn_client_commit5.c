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
typedef  int /*<<< orphan*/  svn_commit_callback2_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * svn_client_commit6 (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client_commit5(const apr_array_header_t *targets,
                   svn_depth_t depth,
                   svn_boolean_t keep_locks,
                   svn_boolean_t keep_changelists,
                   svn_boolean_t commit_as_operations,
                   const apr_array_header_t *changelists,
                   const apr_hash_t *revprop_table,
                   svn_commit_callback2_t commit_callback,
                   void *commit_baton,
                   svn_client_ctx_t *ctx,
                   apr_pool_t *pool)
{
  return svn_client_commit6(targets, depth, keep_locks, keep_changelists,
                            commit_as_operations,
                            FALSE,  /* include_file_externals */
                            FALSE, /* include_dir_externals */
                            changelists, revprop_table, commit_callback,
                            commit_baton, ctx, pool);
}