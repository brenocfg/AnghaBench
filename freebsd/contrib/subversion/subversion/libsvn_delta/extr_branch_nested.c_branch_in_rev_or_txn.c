#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {int /*<<< orphan*/  repos; } ;
typedef  TYPE_1__ svn_branch__txn_t ;
typedef  int /*<<< orphan*/  svn_branch__state_t ;
struct TYPE_7__ {int /*<<< orphan*/  bid; int /*<<< orphan*/  rev; } ;
typedef  TYPE_2__ svn_branch__rev_bid_eid_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_BRANCH__ERR ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  svn_branch__repos_get_branch_by_id (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_branch__txn_get_branch_by_id (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
branch_in_rev_or_txn(svn_branch__state_t **branch_p,
                     const svn_branch__rev_bid_eid_t *src_el_rev,
                     svn_branch__txn_t *txn,
                     apr_pool_t *result_pool)
{
  if (SVN_IS_VALID_REVNUM(src_el_rev->rev))
    {
      SVN_ERR(svn_branch__repos_get_branch_by_id(branch_p,
                                                 txn->repos,
                                                 src_el_rev->rev,
                                                 src_el_rev->bid,
                                                 result_pool));
    }
  else
    {
      *branch_p
        = svn_branch__txn_get_branch_by_id(
            txn, src_el_rev->bid, result_pool);
      if (! *branch_p)
        return svn_error_createf(SVN_BRANCH__ERR, NULL,
                                 _("Branch %s not found"),
                                 src_el_rev->bid);
    }

  return SVN_NO_ERROR;
}