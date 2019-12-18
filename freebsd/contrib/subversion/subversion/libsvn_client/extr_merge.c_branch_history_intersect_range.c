#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {int /*<<< orphan*/  tip; int /*<<< orphan*/  has_r0_history; int /*<<< orphan*/  history; } ;
typedef  TYPE_1__ branch_history_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int SVN_IS_VALID_REVNUM (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ *) ; 
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_client__pathrev_dup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_mergeinfo__filter_mergeinfo_by_ranges (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_mergeinfo_dup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
branch_history_intersect_range(branch_history_t **intersection_p,
                               const branch_history_t *branch_history,
                               svn_revnum_t oldest_rev,
                               svn_revnum_t youngest_rev,
                               apr_pool_t *result_pool,
                               apr_pool_t *scratch_pool)
{
  branch_history_t *result = apr_palloc(result_pool, sizeof(*result));

  SVN_ERR_ASSERT(SVN_IS_VALID_REVNUM(oldest_rev));
  SVN_ERR_ASSERT(SVN_IS_VALID_REVNUM(youngest_rev));
  SVN_ERR_ASSERT(oldest_rev >= 1);
  /* Allow a just-empty range (oldest = youngest + 1) but not an
   * arbitrary reverse range (such as oldest = youngest + 2). */
  SVN_ERR_ASSERT(oldest_rev <= youngest_rev + 1);

  if (oldest_rev <= youngest_rev)
    {
      SVN_ERR(svn_mergeinfo__filter_mergeinfo_by_ranges(
                &result->history, branch_history->history,
                youngest_rev, oldest_rev - 1, TRUE /* include_range */,
                result_pool, scratch_pool));
      result->history = svn_mergeinfo_dup(result->history, result_pool);
    }
  else
    {
      result->history = apr_hash_make(result_pool);
    }
  result->has_r0_history = FALSE;

  /* ### TODO: Set RESULT->tip to the tip of the intersection. */
  result->tip = svn_client__pathrev_dup(branch_history->tip, result_pool);

  *intersection_p = result;
  return SVN_NO_ERROR;
}