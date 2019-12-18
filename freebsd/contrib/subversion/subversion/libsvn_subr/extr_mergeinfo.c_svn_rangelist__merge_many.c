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
typedef  int /*<<< orphan*/  svn_rangelist_t ;
typedef  int /*<<< orphan*/  svn_mergeinfo_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_rangelist_merge2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_rangelist__merge_many(svn_rangelist_t *merged_rangelist,
                          svn_mergeinfo_t merge_history,
                          apr_pool_t *result_pool,
                          apr_pool_t *scratch_pool)
{
  if (apr_hash_count(merge_history))
    {
      apr_pool_t *iterpool = svn_pool_create(scratch_pool);
      apr_hash_index_t *hi;

      for (hi = apr_hash_first(scratch_pool, merge_history);
           hi;
           hi = apr_hash_next(hi))
        {
          svn_rangelist_t *subtree_rangelist = apr_hash_this_val(hi);

          svn_pool_clear(iterpool);
          SVN_ERR(svn_rangelist_merge2(merged_rangelist, subtree_rangelist,
                                       result_pool, iterpool));
        }
      svn_pool_destroy(iterpool);
    }
  return SVN_NO_ERROR;
}