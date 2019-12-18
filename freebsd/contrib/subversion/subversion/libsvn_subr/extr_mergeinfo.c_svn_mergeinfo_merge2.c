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
typedef  int /*<<< orphan*/  apr_ssize_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_hash_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_get (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this (int /*<<< orphan*/ *,void const**,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_rangelist_merge2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_mergeinfo_merge2(svn_mergeinfo_t mergeinfo,
                     svn_mergeinfo_t changes,
                     apr_pool_t *result_pool,
                     apr_pool_t *scratch_pool)
{
  apr_hash_index_t *hi;
  apr_pool_t *iterpool;

  if (!apr_hash_count(changes))
    return SVN_NO_ERROR;

  iterpool = svn_pool_create(scratch_pool);
  for (hi = apr_hash_first(scratch_pool, changes); hi; hi = apr_hash_next(hi))
    {
      const char *key;
      apr_ssize_t klen;
      svn_rangelist_t *to_insert;
      svn_rangelist_t *target;

      /* get ranges to insert and the target ranges list of that insertion */
      apr_hash_this(hi, (const void**)&key, &klen, (void*)&to_insert);
      target = apr_hash_get(mergeinfo, key, klen);

      /* if range list exists, just expand on it.
       * Otherwise, add new hash entry. */
      if (target)
        {
          SVN_ERR(svn_rangelist_merge2(target, to_insert, result_pool,
                                       iterpool));
          svn_pool_clear(iterpool);
        }
      else
        apr_hash_set(mergeinfo, key, klen, to_insert);
    }

  svn_pool_destroy(iterpool);

  return SVN_NO_ERROR;
}