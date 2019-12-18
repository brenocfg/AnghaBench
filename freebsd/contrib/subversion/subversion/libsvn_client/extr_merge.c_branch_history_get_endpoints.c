#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client__pathrev_t ;
struct TYPE_4__ {int /*<<< orphan*/  history; } ;
typedef  TYPE_1__ branch_history_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * location_on_branch_at_rev (TYPE_1__ const*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_mergeinfo__get_range_endpoints (scalar_t__*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
branch_history_get_endpoints(svn_client__pathrev_t **oldest_p,
                             svn_client__pathrev_t **youngest_p,
                             const branch_history_t *branch,
                             apr_pool_t *result_pool,
                             apr_pool_t *scratch_pool)
{
  svn_revnum_t youngest_rev, oldest_rev;

  SVN_ERR(svn_mergeinfo__get_range_endpoints(
            &youngest_rev, &oldest_rev,
            branch->history, scratch_pool));
  if (oldest_p)
    *oldest_p = location_on_branch_at_rev(
                  branch, oldest_rev + 1, result_pool, scratch_pool);
  if (youngest_p)
    *youngest_p = location_on_branch_at_rev(
                    branch, youngest_rev, result_pool, scratch_pool);
  return SVN_NO_ERROR;
}