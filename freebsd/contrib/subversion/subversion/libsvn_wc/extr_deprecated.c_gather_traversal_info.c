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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  scalar_t__ svn_boolean_t ;
struct svn_wc_traversal_info_t {int /*<<< orphan*/  depths; int /*<<< orphan*/  externals_new; int /*<<< orphan*/  externals_old; int /*<<< orphan*/  pool; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this_val (int /*<<< orphan*/ *) ; 
 char* svn_dirent_join (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_dirent_skip_ancestor (char const*,char const*) ; 
 int /*<<< orphan*/  svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__externals_gather_definitions (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
gather_traversal_info(svn_wc_context_t *wc_ctx,
                      const char *local_abspath,
                      const char *path,
                      svn_depth_t depth,
                      struct svn_wc_traversal_info_t *traversal_info,
                      svn_boolean_t gather_as_old,
                      svn_boolean_t gather_as_new,
                      apr_pool_t *scratch_pool)
{
  apr_hash_t *externals;
  apr_hash_t *ambient_depths;
  apr_hash_index_t *hi;

  SVN_ERR(svn_wc__externals_gather_definitions(&externals, &ambient_depths,
                                               wc_ctx, local_abspath,
                                               depth,
                                               scratch_pool, scratch_pool));

  for (hi = apr_hash_first(scratch_pool, externals);
       hi;
       hi = apr_hash_next(hi))
    {
      const char *node_abspath = apr_hash_this_key(hi);
      const char *relpath;

      relpath = svn_dirent_join(path,
                                svn_dirent_skip_ancestor(local_abspath,
                                                         node_abspath),
                                traversal_info->pool);

      if (gather_as_old)
        svn_hash_sets(traversal_info->externals_old, relpath,
                      apr_hash_this_val(hi));

      if (gather_as_new)
        svn_hash_sets(traversal_info->externals_new, relpath,
                      apr_hash_this_val(hi));

      svn_hash_sets(traversal_info->depths, relpath,
                    svn_hash_gets(ambient_depths, node_abspath));
    }

  return SVN_NO_ERROR;
}