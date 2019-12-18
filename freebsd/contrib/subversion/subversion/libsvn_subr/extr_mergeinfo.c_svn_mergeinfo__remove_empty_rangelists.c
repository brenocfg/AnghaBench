#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ nelts; } ;
typedef  TYPE_1__ svn_rangelist_t ;
typedef  scalar_t__ svn_mergeinfo_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 TYPE_1__* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (scalar_t__,char const*,int /*<<< orphan*/ *) ; 

svn_boolean_t
svn_mergeinfo__remove_empty_rangelists(svn_mergeinfo_t mergeinfo,
                                       apr_pool_t *scratch_pool)
{
  apr_hash_index_t *hi;
  svn_boolean_t removed_some_ranges = FALSE;

  if (mergeinfo)
    {
      for (hi = apr_hash_first(scratch_pool, mergeinfo); hi;
           hi = apr_hash_next(hi))
        {
          const char *path = apr_hash_this_key(hi);
          svn_rangelist_t *rangelist = apr_hash_this_val(hi);

          if (rangelist->nelts == 0)
            {
              svn_hash_sets(mergeinfo, path, NULL);
              removed_some_ranges = TRUE;
            }
        }
    }
  return removed_some_ranges;
}