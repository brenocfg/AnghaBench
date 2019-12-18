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
typedef  int /*<<< orphan*/  svn_mergeinfo_t ;
typedef  int /*<<< orphan*/  svn_mergeinfo_catalog_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_mergeinfo_dup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_mergeinfo_catalog_t
svn_mergeinfo_catalog_dup(svn_mergeinfo_catalog_t mergeinfo_catalog,
                          apr_pool_t *pool)
{
  svn_mergeinfo_t new_mergeinfo_catalog = apr_hash_make(pool);
  apr_hash_index_t *hi;

  for (hi = apr_hash_first(pool, mergeinfo_catalog);
       hi;
       hi = apr_hash_next(hi))
    {
      const char *key = apr_hash_this_key(hi);
      svn_mergeinfo_t val = apr_hash_this_val(hi);

      svn_hash_sets(new_mergeinfo_catalog, apr_pstrdup(pool, key),
                    svn_mergeinfo_dup(val, pool));
    }

  return new_mergeinfo_catalog;
}