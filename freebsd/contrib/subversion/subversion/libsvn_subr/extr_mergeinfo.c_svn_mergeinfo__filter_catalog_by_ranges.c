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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_mergeinfo_t ;
typedef  int /*<<< orphan*/  svn_mergeinfo_catalog_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_mergeinfo__filter_mergeinfo_by_ranges (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_mergeinfo__filter_catalog_by_ranges(svn_mergeinfo_catalog_t *filtered_cat,
                                        svn_mergeinfo_catalog_t catalog,
                                        svn_revnum_t youngest_rev,
                                        svn_revnum_t oldest_rev,
                                        svn_boolean_t include_range,
                                        apr_pool_t *result_pool,
                                        apr_pool_t *scratch_pool)
{
  apr_hash_index_t *hi;

  *filtered_cat = apr_hash_make(result_pool);
  for (hi = apr_hash_first(scratch_pool, catalog);
       hi;
       hi = apr_hash_next(hi))
    {
      const char *path = apr_hash_this_key(hi);
      svn_mergeinfo_t mergeinfo = apr_hash_this_val(hi);
      svn_mergeinfo_t filtered_mergeinfo;

      SVN_ERR(svn_mergeinfo__filter_mergeinfo_by_ranges(&filtered_mergeinfo,
                                                        mergeinfo,
                                                        youngest_rev,
                                                        oldest_rev,
                                                        include_range,
                                                        result_pool,
                                                        scratch_pool));
      if (apr_hash_count(filtered_mergeinfo))
        svn_hash_sets(*filtered_cat,
                      apr_pstrdup(result_pool, path), filtered_mergeinfo);
    }

  return SVN_NO_ERROR;
}