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
typedef  scalar_t__ svn_mergeinfo_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_rangelist__set_inheritance (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
svn_mergeinfo__set_inheritance(svn_mergeinfo_t mergeinfo,
                               svn_boolean_t inheritable,
                               apr_pool_t *scratch_pool)
{
  if (mergeinfo)
    {
      apr_hash_index_t *hi;

      for (hi = apr_hash_first(scratch_pool, mergeinfo);
           hi;
           hi = apr_hash_next(hi))
        {
          svn_rangelist_t *rangelist = apr_hash_this_val(hi);

          if (rangelist)
            svn_rangelist__set_inheritance(rangelist, inheritable);
        }
    }
  return;
}