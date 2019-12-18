#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_8__ {scalar_t__ nelts; } ;
typedef  TYPE_1__ svn_rangelist_t ;
typedef  int /*<<< orphan*/  svn_mergeinfo_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_ssize_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this_key_len (int /*<<< orphan*/ *) ; 
 TYPE_1__* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_pstrmemdup (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_path_compare_paths (char const*,char const*) ; 
 TYPE_1__* svn_rangelist_dup (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_rangelist_inheritable2 (TYPE_1__**,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_mergeinfo_inheritable2(svn_mergeinfo_t *output,
                           svn_mergeinfo_t mergeinfo,
                           const char *path,
                           svn_revnum_t start,
                           svn_revnum_t end,
                           svn_boolean_t inheritable,
                           apr_pool_t *result_pool,
                           apr_pool_t *scratch_pool)
{
  apr_hash_index_t *hi;
  svn_mergeinfo_t inheritable_mergeinfo = apr_hash_make(result_pool);

  for (hi = apr_hash_first(scratch_pool, mergeinfo);
       hi;
       hi = apr_hash_next(hi))
    {
      const char *key = apr_hash_this_key(hi);
      apr_ssize_t keylen = apr_hash_this_key_len(hi);
      svn_rangelist_t *rangelist = apr_hash_this_val(hi);
      svn_rangelist_t *inheritable_rangelist;

      if (!path || svn_path_compare_paths(path, key) == 0)
        SVN_ERR(svn_rangelist_inheritable2(&inheritable_rangelist, rangelist,
                                           start, end, inheritable,
                                           result_pool, scratch_pool));
      else
        inheritable_rangelist = svn_rangelist_dup(rangelist, result_pool);

      /* Only add this rangelist if some ranges remain.  A rangelist with
         a path mapped to an empty rangelist is not syntactically valid */
      if (inheritable_rangelist->nelts)
        apr_hash_set(inheritable_mergeinfo,
                     apr_pstrmemdup(result_pool, key, keylen), keylen,
                     inheritable_rangelist);
    }
  *output = inheritable_mergeinfo;
  return SVN_NO_ERROR;
}