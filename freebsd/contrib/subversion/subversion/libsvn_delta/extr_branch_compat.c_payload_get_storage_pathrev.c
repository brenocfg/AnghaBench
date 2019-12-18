#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_pathrev_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {int /*<<< orphan*/  branch_id; } ;
struct TYPE_4__ {TYPE_2__ branch_ref; } ;
typedef  TYPE_1__ svn_element__payload_t ;
typedef  int /*<<< orphan*/  svn_branch__repos_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  storage_pathrev_from_branch_ref (int /*<<< orphan*/ *,TYPE_2__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
payload_get_storage_pathrev(svn_pathrev_t *storage_pathrev_p,
                            svn_element__payload_t *payload,
                            svn_branch__repos_t *repos,
                            apr_pool_t *result_pool)
{
  SVN_ERR_ASSERT(payload->branch_ref.branch_id /* && ... */);

  SVN_ERR(storage_pathrev_from_branch_ref(storage_pathrev_p,
                                          payload->branch_ref, repos,
                                          result_pool, result_pool));
  return SVN_NO_ERROR;
}