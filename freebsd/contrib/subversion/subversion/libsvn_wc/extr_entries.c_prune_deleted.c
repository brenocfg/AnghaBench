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
typedef  int /*<<< orphan*/  svn_wc_entry_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 void* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,void const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  svn_wc__entry_is_hidden (scalar_t__*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static svn_error_t *
prune_deleted(apr_hash_t **entries_pruned,
              apr_hash_t *entries_all,
              apr_pool_t *result_pool,
              apr_pool_t *scratch_pool)
{
  apr_hash_index_t *hi;

  if (!entries_all)
    {
      *entries_pruned = NULL;
      return SVN_NO_ERROR;
    }

  /* I think it will be common for there to be no deleted entries, so
     it is worth checking for that case as we can optimise it. */
  for (hi = apr_hash_first(scratch_pool, entries_all);
       hi;
       hi = apr_hash_next(hi))
    {
      svn_boolean_t hidden;

      SVN_ERR(svn_wc__entry_is_hidden(&hidden,
                                      apr_hash_this_val(hi)));
      if (hidden)
        break;
    }

  if (! hi)
    {
      /* There are no deleted entries, so we can use the full hash */
      *entries_pruned = entries_all;
      return SVN_NO_ERROR;
    }

  /* Construct pruned hash without deleted entries */
  *entries_pruned = apr_hash_make(result_pool);
  for (hi = apr_hash_first(scratch_pool, entries_all);
       hi;
       hi = apr_hash_next(hi))
    {
      const void *key = apr_hash_this_key(hi);
      const svn_wc_entry_t *entry = apr_hash_this_val(hi);
      svn_boolean_t hidden;

      SVN_ERR(svn_wc__entry_is_hidden(&hidden, entry));
      if (!hidden)
        svn_hash_sets(*entries_pruned, key, entry);
    }

  return SVN_NO_ERROR;
}