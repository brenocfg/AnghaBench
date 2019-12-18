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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_rangelist__canonicalize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_mergeinfo__canonicalize_ranges(svn_mergeinfo_t mergeinfo,
                                   apr_pool_t *scratch_pool)
{
  apr_hash_index_t *hi;

  for (hi = apr_hash_first(scratch_pool, mergeinfo); hi; hi = apr_hash_next(hi))
    {
      apr_array_header_t *rl = apr_hash_this_val(hi);

      SVN_ERR(svn_rangelist__canonicalize(rl, scratch_pool));
    }

  return SVN_NO_ERROR;
}