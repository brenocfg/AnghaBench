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
typedef  scalar_t__ svn_mergeinfo_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 void* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  svn_path_url_add_component2 (char const*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
mergeinfo_relpaths_to_urls(apr_hash_t **out_mergeinfo,
                           svn_mergeinfo_t mergeinfo,
                           const char *repos_root_url,
                           apr_pool_t *result_pool,
                           apr_pool_t *scratch_pool)
{
  *out_mergeinfo = NULL;
  if (mergeinfo)
    {
      apr_hash_index_t *hi;
      apr_hash_t *full_path_mergeinfo = apr_hash_make(result_pool);

      for (hi = apr_hash_first(scratch_pool, mergeinfo);
           hi; hi = apr_hash_next(hi))
        {
          const char *key = apr_hash_this_key(hi);
          void *val = apr_hash_this_val(hi);

          svn_hash_sets(full_path_mergeinfo,
                        svn_path_url_add_component2(repos_root_url, key + 1,
                                                    result_pool),
                        val);
        }
      *out_mergeinfo = full_path_mergeinfo;
    }

  return SVN_NO_ERROR;
}