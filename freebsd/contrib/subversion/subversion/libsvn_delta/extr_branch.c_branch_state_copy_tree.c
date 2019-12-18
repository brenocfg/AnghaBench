#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_branch__txn_t ;
struct TYPE_9__ {int /*<<< orphan*/ * txn; } ;
typedef  TYPE_1__ svn_branch__state_t ;
struct TYPE_10__ {int /*<<< orphan*/  rev; int /*<<< orphan*/  eid; } ;
typedef  TYPE_2__ svn_branch__rev_bid_eid_t ;
typedef  int /*<<< orphan*/  svn_branch__el_rev_id_t ;
typedef  int /*<<< orphan*/  svn_branch__eid_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  branch_in_rev_or_txn (TYPE_1__**,TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  copy_subtree (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_branch__el_rev_id_create (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
branch_state_copy_tree(svn_branch__state_t *to_branch,
                       const svn_branch__rev_bid_eid_t *src_el_rev,
                       svn_branch__eid_t new_parent_eid,
                       const char *new_name,
                       apr_pool_t *scratch_pool)
{
  svn_branch__txn_t *txn = to_branch->txn;
  svn_branch__state_t *src_branch;
  svn_branch__el_rev_id_t *from_el_rev;

  SVN_ERR(branch_in_rev_or_txn(&src_branch, src_el_rev, txn, scratch_pool));
  from_el_rev = svn_branch__el_rev_id_create(src_branch, src_el_rev->eid,
                                             src_el_rev->rev, scratch_pool);
  SVN_ERR(copy_subtree(from_el_rev,
                       to_branch, new_parent_eid, new_name,
                       scratch_pool));

  return SVN_NO_ERROR;
}