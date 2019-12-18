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
typedef  int /*<<< orphan*/  apr_ssize_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this_key_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_pstrmemdup (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash__make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_rangelist_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_mergeinfo_t
svn_mergeinfo_dup(svn_mergeinfo_t mergeinfo, apr_pool_t *pool)
{
  svn_mergeinfo_t new_mergeinfo = svn_hash__make(pool);
  apr_hash_index_t *hi;

  for (hi = apr_hash_first(pool, mergeinfo); hi; hi = apr_hash_next(hi))
    {
      const char *path = apr_hash_this_key(hi);
      apr_ssize_t pathlen = apr_hash_this_key_len(hi);
      svn_rangelist_t *rangelist = apr_hash_this_val(hi);

      apr_hash_set(new_mergeinfo, apr_pstrmemdup(pool, path, pathlen), pathlen,
                   svn_rangelist_dup(rangelist, pool));
    }

  return new_mergeinfo;
}