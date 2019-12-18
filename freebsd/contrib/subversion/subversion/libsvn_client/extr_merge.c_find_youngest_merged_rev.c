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
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_mergeinfo_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_IS_VALID_REVNUM (scalar_t__) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_mergeinfo__get_range_endpoints (scalar_t__*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_mergeinfo_intersect2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
find_youngest_merged_rev(svn_revnum_t *youngest_merged_rev,
                         svn_mergeinfo_t target_history_as_mergeinfo,
                         svn_mergeinfo_t source_mergeinfo,
                         apr_pool_t *scratch_pool)
{
  svn_mergeinfo_t explicit_source_target_history_intersection;

  SVN_ERR(svn_mergeinfo_intersect2(
            &explicit_source_target_history_intersection,
            source_mergeinfo, target_history_as_mergeinfo, TRUE,
            scratch_pool, scratch_pool));
  if (apr_hash_count(explicit_source_target_history_intersection))
    {
      svn_revnum_t old_rev, young_rev;

      /* Keep track of the youngest revision merged from target to source. */
      SVN_ERR(svn_mergeinfo__get_range_endpoints(
                &young_rev, &old_rev,
                explicit_source_target_history_intersection, scratch_pool));
      if (!SVN_IS_VALID_REVNUM(*youngest_merged_rev)
          || (young_rev > *youngest_merged_rev))
        *youngest_merged_rev = young_rev;
    }

  return SVN_NO_ERROR;
}