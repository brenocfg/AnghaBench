#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* priv; TYPE_5__* txn; TYPE_5__* bid; } ;
typedef  TYPE_2__ svn_branch__state_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;
struct TYPE_9__ {struct TYPE_9__* e_map; } ;
struct TYPE_7__ {TYPE_5__* element_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (TYPE_5__*) ; 
 int /*<<< orphan*/  branch_validate_element (TYPE_2__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_eid__hash_this_key (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
assert_branch_state_invariants(const svn_branch__state_t *branch,
                               apr_pool_t *scratch_pool)
{
  apr_hash_index_t *hi;

  assert(branch->bid);
  assert(branch->txn);
  assert(branch->priv->element_tree);
  assert(branch->priv->element_tree->e_map);

  /* Validate elements in the map */
  for (hi = apr_hash_first(scratch_pool, branch->priv->element_tree->e_map);
       hi; hi = apr_hash_next(hi))
    {
      branch_validate_element(branch, svn_eid__hash_this_key(hi),
                              apr_hash_this_val(hi));
    }
}